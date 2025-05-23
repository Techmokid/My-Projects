import keyboard,time,mouse

def leftClickSpam(t):
    mouse.click('left')
    time.sleep(t)
def rightClickSpam(t):
    mouse.click('right')
    time.sleep(t)
def keySpam(key,t):
    keyboard.press(key)
    time.sleep(t)
    keyboard.release(key)
    time.sleep(t)

running = False
while (True):
    while(running):
        keySpam("space",0.005)
        #rightClickSpam(0.005)
        if keyboard.is_pressed('F6'):
            running = False
            print("Off")
    if keyboard.is_pressed('F7'):
        print("RUNNING")
        running = True
