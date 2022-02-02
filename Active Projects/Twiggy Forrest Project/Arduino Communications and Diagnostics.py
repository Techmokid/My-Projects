import serial

arduino = serial.Serial("COM7",baudrate=115200,timeout=2)

print("[Python Msg]: Retrieving data from arduino...")

resultToFile = ""
running = True
foundStart = False
while(running):
    tmp = str(arduino.readline())[2:-1] + "\n"
    tmp = tmp.replace("\\r\\n","")
    tmp = tmp.replace("\\r","\n")
    print(tmp) 

    endCondition = ("Starting Modem..." in tmp)
    endCondition = endCondition or ("Started successfully with assigned ID:" in tmp)
    endCondition = endCondition or ("[Arduino User Code]: Error getting response from server for ID" in tmp)
    if (endCondition):
        foundStart = not foundStart
        if (foundStart == False):
            running = False
    
    resultToFile += tmp
arduino.close()

print("[Python Msg]: All Arduino data collected")
print("[Python Msg]: Saving data to file")
f = open("C:/Users/aj200/Documents/GitHub/My-Projects/Active Projects/Twiggy Forrest Project/SIM7000_Main/Raw Arduino Output.txt","w+")
f.write(resultToFile)
f.close()

print("[Python Msg]: Purging sensitive information from file data")
resultToFile.replace("techmo.unity.chickenkiller.com","MY_SERVER_IP_ADDRESS_HERE")
resultToFile.replace("163.47.56.221","MY_REDIRECTED_SERVER_IP_ADDRESS_HERE")

print("[Python Msg]: Saving safe data to public-safe file")
f = open("C:/Users/aj200/Documents/GitHub/My-Projects/Active Projects/Twiggy Forrest Project/SIM7000_Main/Public-safe Arduino Output.txt","w+")
f.write(resultToFile)
f.close()

print("[Python Msg]: Completed all tasks!")
while(True):
    pass
