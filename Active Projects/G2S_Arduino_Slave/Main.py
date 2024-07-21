import time
import random
import Colors
from ArduinoInstance import get_arduino_instance
from Button import *
from DrawFunctions import *
from DrawImages import *

print("Arduino communications opening...")
arduino = get_arduino_instance()
print("Arduino communications open. Waiting for wakeup signal")

searchingForAwakeSignal = True
while searchingForAwakeSignal:
    arduino.read_serial()
    
    for i in arduino.buffer:
        if i.split(":")[0] == "AWAKE":
            searchingForAwakeSignal = False
            print("Arduino awake and ready")
        else:
            print(i)
    arduino.buffer = []

    if searchingForAwakeSignal:
        time.sleep(0.5)
        print("Error talking to arduino. Buffer contents: ")
        print(arduino.buffer)
        print()
print("Arduino awake")

buttonsHandler = Buttons()

def getTouchSpot():
    x, y, touched = arduino.read_touch_input()
    arduino.clear_buffer()
    if touched is not None:
        return x,y,touched    # If touched is true, we are pressing and holding. If touched is false, then this is the exact frame we let go of the button on the touchscreen
    return -1,-1,False        # If we return this -1,-1,False, this is telling us there is no touch data, and hence we haven't touched the screen for more than a few frames

def drawMainMenu():
    global buttonsHandler
    buttonsHandler.clear_buttons()
    
    clearScreen()
    drawTopBar()
    buttonsHandler.add_button(5, 50, 95, 170, 18, 135,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Build",
                           None,
                           lambda backgroundColor: DrawMainMenuBuild(backgroundColor))
    buttonsHandler.add_button(110, 50, 95, 170, 5, 135,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Preheat",
                           lambda: drawPreheatMenu(),
                           lambda backgroundColor: DrawMainMenuPreheat(backgroundColor))
    buttonsHandler.add_button(215, 50, 95, 170, 18, 135,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Tools",
                           None,
                           lambda backgroundColor: DrawMainMenuTools(backgroundColor))

preheatMenuBedTemp = 8
preheatMenuExtruderTemp = 210
def drawPreheatMenu():
    global buttonsHandler
    buttonsHandler.clear_buttons()
    
    clearScreen()
    drawTopBar()

    # Draw extruder
    drawText(20,60, 2, "Extruder: ", [255, 255, 255])
    buttonsHandler.add_radio_button(130, 50, 80, 40,
                                    Colors.colors["LIME"], Colors.colors["RED"],
                                    None)
    buttonsHandler.add_button(225, 50, 80, 40, 10, 12,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           str(preheatMenuExtruderTemp) + " "*(4-len(str(preheatMenuExtruderTemp))) + "C",
                           None,
                           None)

    # Draw bed    
    drawText(20,140, 2, "Bed: ", [255, 255, 255])
    buttonsHandler.add_radio_button(130, 130, 80, 40,
                                    Colors.colors["LIME"], Colors.colors["RED"],
                                    None)
    buttonsHandler.add_button(225, 130, 80, 40, 10, 12,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           str(preheatMenuBedTemp) + " "*(4-len(str(preheatMenuBedTemp))) + "C",
                           None,
                           None)

    # Draw navigation buttons
    buttonsHandler.add_button(0, 200, 160, 40, 50, 12,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Start",
                           None,
                           None)
    buttonsHandler.add_button(160, 200, 160, 40, 50, 12,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Back",
                           lambda: drawMainMenu(),
                           None)

#time.sleep(3)
drawMainMenu()
while True:
    drawTopBar_InternetConnectivity(force=False)
    buttonsHandler.process(getTouchSpot())
