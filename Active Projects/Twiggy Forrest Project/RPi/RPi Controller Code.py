from multiprocessing import Process,Manager,Value
import requests,json,os,time,hashlib,hmac,serial,sys,pyttsx3
import RPi.GPIO as GPIO

onlineLEDPin = 5            #Done
warningPin = 6              #Done
motor_pin_A = 13
motor_pin_B = 19
SENSOR_PIN = 26             #Done
GPS_pin = 18                #Done
useCurrentSensorPin = 17    #Done
localIPPin = 27             #Done
resetIDPin = 22             #Done

URL = "http://www.techmo.unity.chickenkiller.com"
URL_Local = "http://192.168.1.15:666/index2.php"
filepath = "/Client Data/"

if not os.path.exists(filepath):
    os.makedirs(filepath)
engine = pyttsx3.init()
engine.setProperty('rate',140)
print("Waking up")
engine.say("This unit is waking up. Please stand by")
engine.runAndWait()

def printAndSay(x):
    print(x)
    engine.say(x)
    engine.runAndWait()

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(onlineLEDPin, GPIO.OUT)
GPIO.setup(warningPin, GPIO.OUT)
GPIO.setup(motor_pin_A, GPIO.OUT)
GPIO.setup(motor_pin_B, GPIO.OUT)
GPIO.setup(GPS_pin, GPIO.OUT)
GPIO.setup(SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(useCurrentSensorPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(localIPPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(resetIDPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.output(GPS_pin, 1)
GPIO.output(onlineLEDPin, 1)

usingCurrentSensor = not GPIO.input(useCurrentSensorPin)
localizeIP = GPIO.input(localIPPin)
resetID = not GPIO.input(resetIDPin)

print('Current settings are set as such')
engine.say('Current settings are set as such')
engine.runAndWait()

if (usingCurrentSensor):
    print("Current sensor enabled")
    engine.say('Current sensor is enabled')
else:
    print("Current sensor disabled")
    engine.say('Current sensor is disabled')
engine.runAndWait()

if (localizeIP):
    URL = URL_Local
    print("Set IP to local host")
    engine.say('Set IP to local host')
else:
    print("Set IP to global URL")
    engine.say('Set IP to global URL')
engine.runAndWait()

print("Checking network status")
engine.say("Checking network status")
engine.runAndWait()

while(1):
    try:
        requests.head("http://www.google.com",timeout=5)
        break
    except:
        print("Error, no internet connection. Trying again")
        engine.say("Error, no internet connection. Trying again")
        engine.runAndWait()
        time.sleep(5)
print("Found internet connection. Attempting to contact server")
engine.say("Found internet connection. Attempting to contact server")
engine.runAndWait()

while(1):
    try:
        requests.head(URL,timeout=5)
        break
    except:
        print("Error talking to server. Perhaps using localhost on global connection or vice versa? Trying again")
        engine.say("Error talking to server. Perhaps using localhost on global connection or vice versa? Trying again")
        engine.runAndWait()
        time.sleep(5)
    
print("Server connection established")
engine.say("Server connection established")
engine.runAndWait()

ID_Filepath = filepath + "ID.txt"
EncryptionKey_Filepath = filepath + "key.txt"

#Legacy code for debugging
#with open("/home/pbody/Desktop/out.txt","w") as f:
#    f.write("Filepath: " + filepath + "\nID path: " + ID_Filepath + "\nEncryption path: " + EncryptionKey_Filepath)

if (resetID):
    engine.say('Resetting ID and security key files')
    print("Resetting ID and security key files")
    if(os.path.exists(ID_Filepath)):
        os.unlink(ID_Filepath)
        print("Removed ID file")
    if(os.path.exists(EncryptionKey_Filepath)):
        os.unlink(EncryptionKey_Filepath)
        print("Removed encryption key file")
    print("Removed ID files")
    time.sleep(5)
else:
    engine.say('Attempting to use pre-existing ID')
    print("Attempting to use pre-existing ID")
engine.runAndWait()

#For processes interface
manager = Manager()
sharedData = manager.list()
sharedData.append("Warming Up GPS")    # Current Status
sharedData.append("STP")        # RunMode
sharedData.append("-1")         # ID
sharedData.append(None)         # Temp variable for server response
sharedData.append([])           # Amp reading average readings list
sharedData.append(False)        # RunMode Antilock variable (W.I.P)
sharedData.append("")           # Encryption Key

#For GPS interface
sharedData.append("$GPGGA,")    # 7

engine.say("Waiting for serial communications from GPS...")
engine.runAndWait()

ser = serial.Serial("/dev/ttyS0",baudrate=9600)
time.sleep(5)

runningWithoutGPS = False
attemptsCount = 0
while(attemptsCount <= 4):
    isReady = True
    try:
        if(ser.inWaiting() < 1):
            printAndSay("No data from GPS module. Trying again...")
            time.sleep(5)
            isReady = False
        elif(sharedData[7] not in ser.readline()):
            printAndSay("GPS module returned invalid or corrupt data. Trying again...")
            time.sleep(5)
            isReady = False
    except:
        printAndSay("GPS module returned invalid bytes. Trying again...")
        time.sleep(5)
        isReady = False
    if (isReady):
        break
    
    attemptsCount += 1
    if (attemptsCount > 4):
        printAndSay("Maximum number of GPS module communication attempts reached. GPS module unresponsive or damaged. Continueing without GPS sensor")
        runningWithoutGPS = True

if (runningWithoutGPS):
    print("Serial connection to GPS module failed")
    engine.say("Serial connection to GPS module failed")
    engine.runAndWait()
else:
    print("Serial connection to GPS module established")
    engine.say("Serial connection to GPS module established")
    engine.runAndWait()

sharedData.append(None)              #Open port with baud rate
sharedData.append(0)
sharedData.append(0)
sharedData.append(0)
sharedData.append("000000") # 12

#GPS stuff
def convert_to_degrees(raw_value):
    decimal_value = raw_value/100.00
    degrees = int(decimal_value)
    mm_mmmm = (decimal_value - int(decimal_value))/0.6
    position = degrees + mm_mmmm
    position = "%.4f" %(position)
    return position

def getGPSData():
    received_data = (str)(ser.readline())
    GPGGA_data_available = received_data.find(sharedData[7])
    
    if (GPGGA_data_available>0):
        nmea_time = []
        nmea_latitude = []
        nmea_longitude = []
        sharedData[12] = sharedData[9][0]                    #extract time from GPGGA string
        nmea_latitude = sharedData[9][1]                #extract latitude from GPGGA string
        nmea_longitude = sharedData[9][3]               #extract longitude from GPGGA string
        
        #print("NMEA Time: ", nmea_time,'\n')
        #print ("NMEA Latitude:", nmea_latitude,"NMEA Longitude:", nmea_longitude,'\n')
        
        lat = float(nmea_latitude)                  #convert string into float for calculation
        longi = float(nmea_longitude)               #convertr string into float for calculation
        sharedData[10] = convert_to_degrees(lat)
        sharedData[11] = convert_to_degrees(longi)
    return [sharedData[10], sharedData[11], sharedData[12][:2] + ":" + sharedData[12][2:4] + ":" + sharedData[12][4:6]]

#For web server
def encryptData(data,key):
    return hmac.new(bytes(key , 'utf-8'), msg = bytes(data , 'utf-8'), digestmod = hashlib.sha256).hexdigest()

def getResponseContent(x,startVal,endVal):
    x = x[x.find(startVal) + len(startVal) + 1:x.rfind(endVal)]
    return x

def getDateTime():
    serverResponse = requests.get(url=URL,headers={'Getserverdatetime':'1'})
    if (serverResponse.ok == False):
        raise Exception("Error when getting server response LOL")
    tmp = str(serverResponse.content)
    return tmp[tmp.find("<body>") + 8:tmp.rfind("</body>")]

def setServerValue(val, key):
    currentDateTime = getDateTime()
    serverResponse = requests.get(url=URL,headers={'Setvalue':val,'Key':key,'Id':sharedData[2],'Encryptedkey':encryptData(val+key+sharedData[2]+currentDateTime,sharedData[6]),'Datetime':currentDateTime})
    if (serverResponse.ok == False):
        raise Exception("Error when getting server response LOL")

def getServerTime():
    serverResponse = requests.get(url=URL,headers={'Getserverdatetime':'1'})
    if (serverResponse.ok == False):
        raise Exception("Error when getting server time LOL")
    tmp = str(serverResponse.content)
    return tmp[tmp.find("<body>") + 8:tmp.rfind("</body>")]

def initialize():
    if ((os.path.exists(ID_Filepath) == False) or (os.stat(ID_Filepath).st_size == 0)):
        if (sharedData[2] == "-1"):
            sharedData[3] = requests.get(url=URL,headers={'Newid':'1'})
            print("[WEB] Status:  " + str(sharedData[3].status_code))
            engine.say("No client ID detected. Retrieving new data")
            engine.runAndWait()
        else:
            print("[WEB] Retrying with ID: " + str(sharedData[2]))
        if (sharedData[3].ok):
            if (sharedData[2] == "-1"):
                JSONData = json.loads(getResponseContent(sharedData[3].text,"<body>","</body>"))
                newID = JSONData["ID"]
                print("[WEB] Retreived new ID: " + str(newID))

                sharedData[2] = str(newID)
                sharedData[6] = str(JSONData["EncryptionKey"])
                
                engine.say("Successfully retrieved new ID and key. Now sending data akno ledgements back to server")
                engine.runAndWait()
            GPSData = getGPSData()
            
            print("[WEB] Sending server current status")
            if (GPSData[0] != 0 and GPSData[1] != 0):
                setServerValue(str(GPSData[0]),"GPSLastLat")
                setServerValue(str(GPSData[1]),"GPSLastLong")
                setServerValue(str(GPSData[2]),"GPSLastTime")
            setServerValue(getServerTime(),"ServerLastTime")
            if (runningWithoutGPS):
                setServerValue("False","Using GPS")
            else:
                setServerValue("True","Using GPS")
            #setServerValue(str(GPSData[3]),"Temp")
            setServerValue("Warming Up GPS","Status")
            setServerValue("STP","RunMode")

            engine.say("Server akno ledged. Finishing up initilization")
            engine.runAndWait()
            print("[WEB] Finishing up init")
            with open(EncryptionKey_Filepath,"w+") as f:
                f.write(str(sharedData[6]))
            with open(ID_Filepath,"w+") as f:
                f.write(str(newID))
        else:
            print("[WEB] ERROR: Could not get new ID from server. " + str(sharedData[3].status_code) + " status returned!")
            engine.say("Could not get new ID from server, as the server returned an error status")
            engine.runAndWait()
    else:
        engine.say("Potentially detected client ID")
        engine.runAndWait()
        try:
            with open(EncryptionKey_Filepath,"r") as f:
                sharedData[6] = f.read()
            with open(ID_Filepath,"r") as f:
                sharedData[2] = f.read()

            if (len(sharedData[2]) > 0):
                print("[WEB] Starting Unit ID: " + sharedData[2])
                engine.say("Confirmed client ID")
                engine.runAndWait()
            else:
                print("ID file exists but is empty. Recreating file....")
                engine.say("ID file exists, but is empty. Removing files and refreshing ID")
                engine.runAndWait()
                
                if (os.path.exists(EncryptionKey_Filepath)):
                    os.remove(EncryptionKey_Filepath)
                if (os.path.exists(ID_Filepath)):
                    os.remove(ID_Filepath)
        except:
            print("Error reading from ID file. Recreating...")
            engine.say("Error while reading from ID file. Removing files and refreshing client details")
            engine.runAndWait()
            if (os.path.exists(EncryptionKey_Filepath)):
                os.remove(EncryptionKey_Filepath)
            if (os.path.exists(ID_Filepath)):
                os.remove(ID_Filepath)

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
            engine.say("Error occurred while initializing reads as such")
            engine.runAndWait()
            engine.say(e)
            engine.runAndWait()
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
    piPWM.stop()

def doWebInterface():
    while(1):
        time.sleep(5)
        try:
            GPSData = getGPSData()
            setServerValue(sharedData[0],"Status")
            if (GPSData[0] != 0 and GPSData[1] != 0):
                setServerValue(str(GPSData[0]),"GPSLastLat")
                setServerValue(str(GPSData[1]),"GPSLastLong")
                #setServerValue(str(GPSData[2]),"GPSLastTime")
                sharedData[0] = "Online"
            setServerValue(getServerTime(),"ServerLastTime")
                
            if (runningWithoutGPS):
                setServerValue("False","Using GPS")
            else:
                setServerValue("True","Using GPS")
                
            if (sharedData[5] == True):
                setServerValue("RUN","RunMode")
                sharedData[5] = False
            
            sharedData[3] = requests.get(url=URL,headers={'Getinfoonid':sharedData[2]})
            if (sharedData[3].ok):
                servData = json.loads(getResponseContent(sharedData[3].text,"<body>","</body>"))
                if (servData["RunMode"] == "RUN" and sharedData[1] == "STP"):
                    print("[WEB] Startup detected. Running warning tone")
                    sharedData[0] = "Starting Motor"
                    doWarning(5)
                    sharedData[0] = "Running"
                    print("[WEB] RUN condition passed to motor controller")
                if (sharedData[0] != "ERROR"):
                    sharedData[1] = servData["RunMode"]
                else:
                    sharedData[1] = "STP"
                    setServerValue("STP","RunMode")
                    sharedData[0] = "ERROR"
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
    print("Initializing")
    forceInit()
    print("[WEB] Initialized with ID: " + sharedData[2])
    engine.say("Initialized with ID of " + str(sharedData[2]))
    engine.runAndWait()

    print("Initialization complete. TTS going silent")
    engine.say("Initialization complete. TTS going silent")
    engine.runAndWait()
    engine.stop()
    
    p2 = Process(target=doMotorInterface)
    p2.start()
    #p2.join()
    
    doWebInterface()
