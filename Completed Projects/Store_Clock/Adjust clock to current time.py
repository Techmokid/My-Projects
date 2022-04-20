from datetime import datetime
import serial,time

port = input("Please enter the com-port number that the arduino is on: ")
ser = None
try:
    ser = serial.Serial("COM" + port)
except:
    try:
        ser = serial.Serial(port)
    except:
        print("Error, could not find COM port. Press enter to quit")
        input()
        quit()
        
now = datetime.now()
current_time = now.strftime("%H:%M:%S")
msgB = current_time.encode('utf-8')

print("Writing time to arduino...")
time.sleep(5)
ser.write(msgB)
ser.close()

print("Completed! Please press enter to close")
input()
