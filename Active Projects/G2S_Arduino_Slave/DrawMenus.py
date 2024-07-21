def drawHeadTempAdjustDigitPad():
    global buttonsHandler, preheatMenuExtruderTemp
    buttonsHandler.clear_buttons()
    
    clearScreen()
    drawTopBar()

    drawText(85, 60, 2, "Extruder Temp", Colors.colors["WHITE"])
    tripletDigit = "0"*(3-len(str(preheatMenuExtruderTemp))) + str(preheatMenuExtruderTemp)
    #drawRect(20, 50, 280, 170, [200, 200, 200], True)
    buttonsHandler.add_button(35, 100, 50, 50, 20, 18,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "-",
                           None,
                           None)
    buttonsHandler.add_button(89, 100, 45, 50, 18, 18,
                           [100,100,150], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           tripletDigit[0],
                           None,
                           None)
    buttonsHandler.add_button(138, 100, 45, 50, 18, 18,
                           [100,100,150], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           tripletDigit[1],
                           None,
                           None)
    buttonsHandler.add_button(187, 100, 45, 50, 18, 18,
                           [100,100,150], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           tripletDigit[2],
                           None,
                           None)
    buttonsHandler.add_button(236, 100, 50, 50, 20, 18,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "+",
                           None,
                           None)

    # Nagivation buttons
    buttonsHandler.add_button(0, 200, 160, 40, 50, 12,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Accept",
                           None,
                           None)
    buttonsHandler.add_button(160, 200, 160, 40, 50, 12,
                           Colors.colors["CYAN"], Colors.colors["WHITE"],
                           Colors.colors["LIME"], Colors.colors["WHITE"],
                           "Cancel",
                           lambda: drawPreheatMenu(),
                           None)

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


    
preheatMenuBedTemp = 65
preheatMenuExtruderTemp = 215
def drawPreheatMenu():
    global buttonsHandler, preheatMenuBedTemp, preheatMenuExtruderTemp
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
