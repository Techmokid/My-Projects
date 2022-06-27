from pynput.keyboard import Key, Listener
import os,time

blinkingTime = 5

def on_press(key):
    key = str(key)[1:2]
    if not os.path.exists(key+":/"):
        print("Could not locate drive")
    else:
        prevTime = time.time()
        while(time.time() - prevTime < blinkingTime):
            time.sleep(0.1)
            f = open(key+":/Drive Blink Test File Please Ignore","w")
            f.close()
            os.remove(key+":/Drive Blink Test File Please Ignore")
        

def on_release(key):
    if key == Key.esc:
        # Stop listener
        return False

print("Please enter drive letter: ")

# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
