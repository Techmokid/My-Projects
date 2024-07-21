import time
import random
import socket
import psutil
import Colors
from ArduinoInstance import get_arduino_instance
from Button import *
from DrawFunctions import *
from DrawImages import *

print("Arduino communications opening...")
arduino = get_arduino_instance()
print("Arduino communications open. Waiting for wakeup signal")

arduino.read_serial()
for i in arduino.buffer:
    if i.split(":")[0] == "AWAKE":
        print("Arduino awake and ready")
arduino.buffer = []
print("Arduino awake")

buttonsHandler = Buttons()

def check_network_connection():
    network_connection = 0  # Assume no connection initially

    local_connected = any(snic.family == socket.AF_INET and not snic.address.startswith("127.") 
                          for adapter in psutil.net_if_addrs().values() 
                          for snic in adapter)

    if not local_connected:
        return network_connection

    network_connection = 1  # Local network connected, but no internet confirmed yet

    try:
        host = socket.gethostbyname("www.google.com")
        s = socket.create_connection((host, 80), 2)
        s.close()
        network_connection = 2  # Internet access confirmed
    except:
        pass
    return network_connection

def getTouchSpot():
    x, y, touched = arduino.read_touch_input()
    arduino.clear_buffer()
    if touched is not None:
        return x,y,touched    # If touched is true, we are pressing and holding. If touched is false, then this is the exact frame we let go of the button on the touchscreen
    return -1,-1,False        # If we return this -1,-1,False, this is telling us there is no touch data, and hence we haven't touched the screen for more than a few frames

def drawMainMenu():
    clearScreen()
    drawTopBar()
    buttonsHandler.add_button(5, 50, 95, 170,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Build",
                           None, lambda: DrawMainMenuBuild())
    buttonsHandler.add_button(110, 50, 95, 170,
                            Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Preheat",
                           None, lambda: DrawMainMenuPreheat())
    buttonsHandler.add_button(215, 50, 95, 170,
                          Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Tools",
                           None, lambda: DrawMainMenuTools())



setNetworkStatus(check_network_connection())

drawMainMenu()
while True:
    buttonsHandler.process(getTouchSpot())
