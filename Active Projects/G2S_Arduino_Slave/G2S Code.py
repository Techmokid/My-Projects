import ArduinoCommunicationsInterface.py as ACI

import time
import random
import math
import psutil
import socket

# Set up the serial connection
  # wait for the serial connection to initialize

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



def drawTopBar():
    network_connection = check_network_connection()
    drawRect(0, 0, 320, 30, [30, 30, 30], True)
    drawRect(0, 30, 320, 210, [0, 0, 0], True)
    drawRotatedRect(16, 16, 13, 13, 45, [200, 200, 200], True)
    drawTriangle(17, 5, 17, 26, 27, 15, [100, 100, 100], True)
    drawRect(12, 13, 5, 6, [120, 0, 120], True)
    drawRect(17, 13, 5, 6, [0, 200, 120], True)
    drawText(45, 8, 2, header_title, colors["WHITE"])
    drawRect(289, 5, 25, 20, [120, 120, 120], True)
    drawRect(291, 7, 21, 15, colors["BLACK"], True)
    if network_connection == 0:
        drawRotatedRect(301, 14, 2, 30, 55, colors["RED"], True)
        drawRotatedRect(301, 14, 2, 30, -55, colors["RED"], True)
    elif network_connection == 1:
        drawText(296, 8, 2, "?", colors["ORANGE"])
    elif network_connection == 2:
        drawRotatedRect(305, 14, 2, 15, 55, colors["GREEN"], True)
        drawRotatedRect(298, 17, 2, 5, -55, colors["GREEN"], True)

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
    touch_input = read_touch_input()
    if touch_input:
        touch_x, touch_y = touch_input
        for button in buttons:
            if button.is_touched(touch_x, touch_y):
                print(f"Button {button.text} touched!")
                # Add specific action for each button if needed
    read_serial()
    time.sleep(0.1)

ser.close()  # Make sure to close the serial port on termination
