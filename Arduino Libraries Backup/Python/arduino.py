import serial,time

ser = ""
globalPort = "COM3"

def setPort(portName):
    global globalPort
    globalPort = portName

def begin(baudrate):
    global globalPort,ser
    
    ser = serial.Serial(globalPort,baudrate)
    time.sleep(1)

def write(letterToSend):
    ser.write(bytes(letterToSend, 'utf-8'))

def writeLine(letterToSend):
    ser.write(bytes(letterToSend + "\n", 'utf-8'))

def readChar():
    return ser.read().decode("utf-8")

def readLine():
    result = ""
    
    while True:
        temp = ser.read().decode("utf-8")
        
        if (temp == '\n'):
            break
        result += temp
    
    return result
