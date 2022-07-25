import mouse,keyboard,time

running = False
while (True):
    while(running):
        mouse.click('right')
        time.sleep(0.005)
        if keyboard.is_pressed('i'):
            running = False
            print("Off")
    if keyboard.is_pressed('o'):
        print("RUNNING")
        running = True
