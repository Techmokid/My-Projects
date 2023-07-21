import keyboard,time,mouse

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
        keySpam("shift",0.05)
        #rightClickSpam(0.01)
        if keyboard.is_pressed('F6'):
            running = False
            print("Off")
    if keyboard.is_pressed('F7'):
        print("RUNNING")
        running = True
