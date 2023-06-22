import keyboard,time,mouse

running = False
while (True):
    while(running):
        mouse.click('right')
        #keyboard.press("q")
        time.sleep(0.01)
        if keyboard.is_pressed('F6'):
            running = False
            print("Off")
    if keyboard.is_pressed('F7'):
        print("RUNNING")
        running = True
