import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(7,GPIO.OUT)
GPIO.setup(11,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)

timeUntilNextLED = 0.2

for x in range(0,7):
    GPIO.output(7,True)
    print("Pin 7 On")
    time.sleep(timeUntilNextLED)
    GPIO.output(7,False)
    print("Pin 7 Off")
    GPIO.output(11,True)
    print("Pin 11 On")
    time.sleep(timeUntilNextLED)
    GPIO.output(11,False)
    print("Pin 11 Off")
    GPIO.output(13,True)
    print("Pin 13 On")
    time.sleep(timeUntilNextLED)
    GPIO.output(13,False)
    print("Pin 13 Off")

GPIO.cleanup()
