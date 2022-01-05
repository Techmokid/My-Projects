import serial

SerArd = serial.Serial("COM3",9600)
SerAnd = serial.Serial("COM1",9600)

while(True):
    data = SerArd.readline()
    SerAnd.writeline(data)
