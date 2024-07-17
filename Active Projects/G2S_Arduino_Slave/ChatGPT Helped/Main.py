import time
import random
import socket
import psutil
from ArduinoCommunicationsInterface import Arduino
from Button import Button
from DrawFunctions import clearScreen, drawRect, drawRotatedRect, drawText, drawTopBar

arduino = Arduino(port="COM4", baudrate=115200)

header_titles = ["Fleshforge","Fleshfart","Florshfert","Flashfert","Flashnt","Fleshnt","Blinkforge", "Crafty Cortex", "Pixel Pioneer", "GizmoGrafter", "Pi-lot Print", "Arpino Gizmo"]
header_title = random.choice(header_titles)

colors = {
    "WHITE": [255, 255, 255],
    "CYAN": [0, 150, 255],
    "BLACK": [0, 0, 0],
    "RED": [255, 0, 0],
    "GREEN": [0, 255, 0],
    "BLUE": [0, 0, 255],
    "LIME": [0, 200, 0],
    "LIGHT_GREY": [180, 180, 180],
    "ORANGE": [255, 180, 0],
    "BRONZE": [176, 120, 100],
    "SILVER": [180, 180, 180]
}

# Misc functions
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

def drawMainMenu():
    clearScreen()
    drawTopBar()
    build_button = Button(5, 50, 95, 170, colors["CYAN"], "Build", colors["WHITE"])
    preheat_button = Button(110, 50, 95, 170, colors["CYAN"], "Preheat", colors["WHITE"])
    tools_button = Button(215, 50, 95, 170, colors["CYAN"], "Tools", colors["WHITE"])
    buttons = [build_button, preheat_button, tools_button]

    for button in buttons:
        button.draw()

    return buttons

# Script
buttons = drawMainMenu()

while True:
    touch_input = arduino.read_touch_input()
    if touch_input:
        touch_x, touch_y = touch_input
        for button in buttons:
            if button.is_touched(touch_x, touch_y):
                print(f"Button {button.text} touched!")
                # Add specific action for each button if needed
    arduino.read_serial()
    time.sleep(0.1)

arduino.close()  # Make sure to close the serial port on termination
