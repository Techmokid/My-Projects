from datetime import datetime
import serial

ser = serial.Serial("COM4")

now = datetime.now()
current_time = now.strftime("%H:%M:%S")
msgB = current_time.encode('utf-8')

ser.write(msgB)
ser.close()
