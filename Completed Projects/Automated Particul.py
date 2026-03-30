import time,pyautogui

pyautogui.FAILSAFE = True   # move mouse to top-left to abort
pyautogui.PAUSE = 0.1       # small delay after each action

def spawnSand(timeDelay):
    pyautogui.moveTo(1950, 600, duration=0.2) 
    pyautogui.mouseDown(button='left')
    time.sleep(timeDelay)
    pyautogui.mouseUp(button='left')

def saveGame():
    pyautogui.moveTo(3600, 75, duration=0.2) 
    pyautogui.click(button='left')
    pyautogui.moveTo(1900, 1000, duration=0.2) #Save button
    pyautogui.click(button='left')

    pyautogui.moveTo(1900, 900, duration=0.2) #Continue button
    pyautogui.click(button='left')

def upgradeExtractor():
    pyautogui.moveTo(200, 250, duration=0.2)
    pyautogui.click(button='left')

def sellSand():
    pyautogui.moveTo(380, 100, duration=0.2)
    for i in range(100):
        pyautogui.click(button='left')

def sellIron():
    pyautogui.moveTo(550, 100, duration=0.2)
    for i in range(75):
        pyautogui.click(button='left')

def sellCopper():
    pyautogui.moveTo(725, 100, duration=0.2)
    for i in range(50):
        pyautogui.click(button='left')

def sellSilver():
    pyautogui.moveTo(895, 100, duration=0.2)
    for i in range(50):
        pyautogui.click(button='left')
        
def doSlotMachine():
    pyautogui.moveTo(200, 675, duration=0.2)
    pyautogui.click(button='left')

def doPriceWheel():
    pyautogui.moveTo(3550, 1650, duration=0.2)
    pyautogui.click(button='left')

try:
    pyautogui.moveTo(3300, 20, duration=0.2)
    pyautogui.click(button='left')
    while True:
        spawnSand(60)
        sellSand()
        sellIron()
        sellCopper()
        sellSilver()
        upgradeExtractor()
        doPriceWheel()
        doSlotMachine()

        spawnSand(60)
        sellSand()
        sellIron()
        sellCopper()
        sellSilver()
        upgradeExtractor()
        doSlotMachine()
        doPriceWheel()
        saveGame()
except KeyboardInterrupt:
    print("Stopped.")
