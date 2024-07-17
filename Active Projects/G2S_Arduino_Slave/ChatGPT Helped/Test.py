print("Script Start")
print("Importing Arduino Communications")

from ArduinoCommunicationsInterface import Arduino

print("Starting arduino communications")
arduino = Arduino(port="COM4", baudrate=115200)

print("Arduino running. Awaiting wakeup response")

arduino.read_serial()

for i in arduino.buffer:
    if i.split(":")[0] == "AWAKE":
        print("Arduino awake and ready")
print(arduino.buffer)
