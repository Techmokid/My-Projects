from multiprocessing import Process,Manager,Value
import requests,json,os,time
import RPi.GPIO as GPIO

# https://www.w3schools.com/python/ref_requests_response.asp

#URL = "http://www.techmo.unity.chickenkiller.com"
URL = "http://192.168.1.15:8080/index2.php"
filepath = "/home/pi/Desktop/"
ID_Filepath = filepath + "ID.txt"
Status_Down_Filepath = filepath + "Status.down"
Status_Up_Filepath = filepath + "Status.up"
usingCurrentSensor = False

warningPin = 13
motor_pin_A = 6
motor_pin_B = 19
SENSOR_PIN = 26

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(warningPin, GPIO.OUT)
GPIO.setup(motor_pin_A, GPIO.OUT)
GPIO.setup(motor_pin_B, GPIO.OUT)
GPIO.setup(SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

#For processes interface
manager = Manager()
sharedData = manager.list()
sharedData.append("Offline")    # Current Status
sharedData.append("STP")        # RunMode
sharedData.append("-1")         # ID
sharedData.append(None)         # Temp variable for server response
sharedData.append([])           # Amp reading average readings list
sharedData.append(False)        # RunMode Antilock variable (W.I.P)

#For web server
def getResponseContent(x,startVal,endVal):
    x = x[x.find(startVal) + len(startVal) + 1:x.rfind(endVal)]
    return x

def getGPSData():
    return [0,0,0] # [GPS Latitute, GPS Longitude, GPS Time]

def setServerValue(val, key):
    serverResponse = requests.get(url=URL,headers={'Setvalue':val,'Key':key,'Id':sharedData[2]})
    if (serverResponse.ok == False):
        raise Exception("Error when getting server response LOL")

def initialize():
    if ((os.path.exists(ID_Filepath) == False) or (os.stat(ID_Filepath).st_size == 0)):
        if (sharedData[2] == "-1"):
            sharedData[3] = requests.get(url=URL,headers={'Newid':'1'})
            print("[WEB] Status:  " + str(sharedData[3].status_code))
        else:
            print("[WEB] Retrying with ID: " + str(sharedData[2]))
        if (sharedData[3].ok):
            if (sharedData[2] == "-1"):
                newID = json.loads(getResponseContent(sharedData[3].text,"<body>","</body>"))["ID"]
                print("[WEB] Retreived new ID: " + str(newID))

                sharedData[2] = str(newID)
            GPSData = getGPSData()

            print("[WEB] Sending server current status")
            setServerValue(str(GPSData[0]),"GPSLastLat")
            setServerValue(str(GPSData[1]),"GPSLastLong")
            setServerValue(str(GPSData[2]),"GPSLastTime")
            #setServerValue(str(GPSData[3]),"Temp")
            setServerValue("Online","Status")
            setServerValue("STP","RunMode")

            print("[WEB] Finishing up init")
            f = open(ID_Filepath,'w+')
            f.write(str(newID))
            f.close()
        else:
            print("[WEB] ERROR: Could not get new ID from server. " + str(sharedData[3].status_code) + " status returned!")
    else:
        f = open(ID_Filepath,"r")
        sharedData[2] = f.read()
        f.close()
        
        print("[WEB] Starting Unit ID: " + sharedData[2])

    if (sharedData[2] == "-1"):
        raise Exception("[WEB] ERROR: Failed to initialize correctly")

def forceInit():
    while(1):
        try:
            initialize()
            break
        except Exception as e:
            print(e)
            print("[WEB] Encountered a problem. Retrying in 5 seconds...")
            time.sleep(5)

def doWarning(x):
    piPWM = GPIO.PWM(warningPin, 880)
    piPWM.start(0)
    for i in range(0,x):
        print("Did a thing")
        for duty in range(0,101,1):
            piPWM.ChangeDutyCycle(duty) #provide duty cycle in the range 0-100
            time.sleep(0.001)
        time.sleep(0.5)
        
        for duty in range(100,-1,-1):
            piPWM.ChangeDutyCycle(duty)
            time.sleep(0.001)
        time.sleep(0.5)
    piPWM.stop()

def doWebInterface():
    forceInit()
    print("[WEB] Initialized with ID: " + sharedData[2])
    
    while(1):
        time.sleep(5)
        try:
            GPSData = getGPSData()
            setServerValue(str(GPSData[0]),"GPSLastLat")
            setServerValue(str(GPSData[1]),"GPSLastLong")
            setServerValue(str(GPSData[2]),"GPSLastTime")
            setServerValue(sharedData[0],"Status")
            if (sharedData[5] == True):
                setServerValue("RUN","RunMode")
                sharedData[5] = False
            
            sharedData[3] = requests.get(url=URL,headers={'Getinfoonid':sharedData[2]})
            if (sharedData[3].ok):
                servData = json.loads(getResponseContent(sharedData[3].text,"<body>","</body>"))
                if (servData["RunMode"] == "RUN" and sharedData[1] == "STP"):
                    print("[WEB] Startup detected. Running warning tone")
                    doWarning(5)
                    print("[WEB] RUN condition passed to motor controller")
                if (sharedData[0] != "ERROR"):
                    sharedData[1] = servData["RunMode"]
                else:
                    sharedData[1] = "STP"
                    setServerValue("STP","RunMode")
                    setServerValue("ERROR","Status")
                print("[WEB] Run state: " + str(sharedData[1]))
            else:
                print("[WEB] Error retreiving data from server")
        except Exception as e:
            print("[WEB] Server not found error")
            print("[WEB] Error was: " + str(e))
            print()

#For motor interface
def clamp(x,A,B):
    if (A > B):
        return max(min(x,A),B)
    return max(min(x,B),A)

def setSpeed(x):
    x = clamp(x,1,-1)
    if (x == 0):
        GPIO.output(motor_pin_A, 0)
        GPIO.output(motor_pin_B, 0)
    if (x > 0):
        GPIO.output(motor_pin_B, 0)
        time.sleep(0.01)
        GPIO.PWM(motor_pin_A, x)
    if (x < 0):
        GPIO.output(motor_pin_A, 0)
        time.sleep(0.01)
        GPIO.PWM(motor_pin_B, -x)
    if (x == 1):
        GPIO.output(motor_pin_B, 0)
        time.sleep(0.01)
        GPIO.output(motor_pin_A, 1)
    if (x == 1):
        GPIO.output(motor_pin_A, 0)
        time.sleep(0.01)
        GPIO.output(motor_pin_B, 1)
    time.sleep(0.01)

def readRawCurrent():
    global SENSOR_PIN
    raise Exception("This function has not been implimented yet")

def readAverageCurrent():
    outputCurrent = readRawCurrent()
    sharedData[4].append(outputCurrent)

    averageCurrent = 0
    if (len(sharedData[4]) > 10):
        sharedData[4].pop(0)
        total = 0
        for i in range(0,len(sharedData[4])):
            total += sharedData[4][i]
        averageCurrent = total / len(sharedData[4])
    return averageCurrent

def tryToUnclog(tries):
    doWarning(10)
    
    print("Attempting unclog")
    setSpeed(0)
    if (tries == 0):
        return False

    time.sleep(1.5)
    print("Reversing")
    setSpeed(-1)
    time.sleep(10)
    print("Stopping")
    setSpeed(0)
    time.sleep(2)
    if (usingCurrentSensor == False):
        print("Cleared")
        setSpeed(1)
        sharedData[5] = True
        return True
    for i in range(0,10):
        readAverageCurrent()
    
    setSpeed(1)
    time.sleep(1.5)
    start = time.time()
    while(time.time() - start < 8):
        time.sleep(0.2)
        if (readAverageCurrent() > MAX_CURRENT):
            return tryToUnclog(tries - 1)
    return True
    
def runMotorSafely():
    if (usingCurrentSensor == False):
        setSpeed(1)
        return
    if (readAverageCurrent() > MAX_CURRENT):
        sharedData[0] = "UNCLOGGING"
        while (tryToUnclog(5) == False):
            sharedData[0] = "ERROR"
            time.sleep(60*30)
            doWarning(10)
        sharedData[0] = "RUNNING"
    else:
        setSpeed(1)

def doMotorInterface():
    tmpTime = time.time()
    while(1):
        if (time.time() - tmpTime > 2):
            print("[MTR] " + sharedData[1])
            tmpTime = time.time()
        if (sharedData[1] == "RUN" or sharedData[5] == True):
            runMotorSafely()
            sharedData[0] = "RUNNING"
        if (sharedData[1] == "RST" and sharedData[5] == False):
            sharedData[0] = "UNCLOGGING"
            tryToUnclog(1)
            sharedData[0] = "RUNNING"
            sharedData[1] == "RUN"

if __name__ == '__main__':
    p1 = Process(target=doWebInterface)
    p2 = Process(target=doMotorInterface)
    p1.start()
    p2.start()
    p1.join()
    p2.join()
    
    while(1):
        continue
