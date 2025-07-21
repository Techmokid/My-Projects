import pygame
import threading
from pynput.keyboard import Key
from pynput.keyboard import Controller as KeyboardController
from pynput.mouse import Controller as MouseController, Button as MouseButton
import time

# Initialize pygame and joystick
pygame.init()
pygame.joystick.init()
mouse = MouseController()
keyboard = KeyboardController()
joystick = pygame.joystick.Joystick(0)
joystick.init()

print(f"Joystick detected: {joystick.get_name()}")

# Config
PWM_PERIOD = 0.05  # 50ms loop
DEADZONE = 0.1     # Minimum input threshold
FULL_PRESS_THRESHOLD = 0.95  # Threshold to just hold key instead of PWM

# Map joystick buttons to mouse actions
BUTTON_MAPPINGS = {
    0: lambda: mouse.press(MouseButton.left),       # Button 1 (Fire primary weapon)
    1: lambda: keyboard.press(Key.tab),             # Button 2 (Change target)
    2: lambda: mouse.scroll(0, 1),                  # Button 3 (Change secondary weapon up)
    3: lambda: mouse.press(MouseButton.right),      # Button 4 (Fire secondary weapon)
    4: lambda: mouse.scroll(0, -1),                 # Button 5 (Change secondary weapon down)
    5: lambda: keyboard.press('g'),                 # Button 6 (Fire flares)
    6: lambda: keyboard.press('f'),                 # Button 7 (Highlight target)
    7: lambda: keyboard.press('v'),                 # Button 8 (Change camera mode)
    8: lambda: keyboard.press('z'),                 # Button 9 (Autopilot autolevel aircraft)
    9: lambda: keyboard.press('r'),                 # Button 10 (Switch radar map)
    10: lambda: keyboard.press(Key.enter),          # Button 11 (Enter)
    11: lambda: keyboard.press(Key.f1),             # Button 12 (F1)
}

BUTTON_RELEASES = {
    0: lambda: mouse.release(MouseButton.left),
    1: lambda: keyboard.release(Key.tab),
    #2: lambda: ,
    3: lambda: mouse.release(MouseButton.right),
    #4: lambda: ,
    5: lambda: keyboard.release('g'),
    6: lambda: keyboard.release('f'),
    7: lambda: keyboard.release('v'),
    8: lambda: keyboard.release('z'),
    9: lambda: keyboard.release('r'),
    10: lambda: keyboard.release(Key.enter),
    11: lambda: keyboard.release(Key.f1),
}

button_states = {}

# Axis map
AXES = {
    0: ('a', 'd'),  # X-axis
    1: ('1', '3'),  # Y-axis
    2: ('q', 'e'),  # Z twist
    3: ('w', 's'),  # Throttle
}

# Track which keys are held so we don't overpress
held_keys = set()
lock = threading.Lock()

def keyboardSingle(key):
    keyboard.press(key)
    time.sleep(0.05)
    keyboard.release(key)

def button_worker():
    global button_states
    while True:
        pygame.event.pump()
        for btn_index in BUTTON_MAPPINGS.keys():
            is_pressed = joystick.get_button(btn_index)

            if is_pressed and not button_states.get(btn_index, False):
                BUTTON_MAPPINGS[btn_index]()
                button_states[btn_index] = True

            elif not is_pressed and button_states.get(btn_index, False):
                if btn_index in BUTTON_RELEASES:
                    BUTTON_RELEASES[btn_index]()
                button_states[btn_index] = False

        time.sleep(0.01)  # Fast polling for responsiveness
        
def axis_worker(axis_index, key_neg, key_pos):
    global held_keys
    while True:
        pygame.event.pump()
        val = joystick.get_axis(axis_index)

        # Normalize throttle (axis 3)
        #if axis_index == 3:
        #    val = -(val - 1) / 2  # Map [-1,1] to [0,1]

        if abs(val) < DEADZONE:
            # Release both keys if inside deadzone
            with lock:
                if key_neg in held_keys:
                    keyboard.release(key_neg)
                    held_keys.remove(key_neg)
                if key_pos in held_keys:
                    keyboard.release(key_pos)
                    held_keys.remove(key_pos)
            time.sleep(PWM_PERIOD)
            continue

        key = key_pos if val > 0 else key_neg
        duty_cycle = min(abs(val), 1.0)

        with lock:
            # Release the opposite key if it's being held
            opposite = key_neg if key == key_pos else key_pos
            if opposite in held_keys:
                keyboard.release(opposite)
                held_keys.remove(opposite)

        # Hold key fully if axis is near maximum
        if duty_cycle >= FULL_PRESS_THRESHOLD:
            with lock:
                if key not in held_keys:
                    keyboard.press(key)
                    held_keys.add(key)
            time.sleep(PWM_PERIOD)
            continue

        # PWM-style key tap
        on_time = PWM_PERIOD * duty_cycle
        off_time = PWM_PERIOD - on_time

        with lock:
            keyboard.press(key)
            held_keys.add(key)
        time.sleep(on_time)
        with lock:
            keyboard.release(key)
            held_keys.remove(key)
        time.sleep(off_time)

def hat_worker():
    prev_x = 0
    prev_y = 0
    while True:
        pygame.event.pump()
        hat_x, hat_y = joystick.get_hat(0)

        # Handle Up
        if hat_y == 1 and prev_y != 1:
            keyboard.press(Key.up)
        elif hat_y != 1 and prev_y == 1:
            keyboard.release(Key.up)

        # Handle Down
        if hat_y == -1 and prev_y != -1:
            keyboard.press(Key.down)
        elif hat_y != -1 and prev_y == -1:
            keyboard.release(Key.down)

        # Handle Right
        if hat_x == 1 and prev_x != 1:
            keyboard.press(Key.right)
        elif hat_x != 1 and prev_x == 1:
            keyboard.release(Key.right)

        # Handle Left
        if hat_x == -1 and prev_x != -1:
            keyboard.press(Key.left)
        elif hat_x != -1 and prev_x == -1:
            keyboard.release(Key.left)

        prev_x = hat_x
        prev_y = hat_y
        time.sleep(0.01)


# Start threads
threads = []
print("\nStarting PWM Axis Threads:")
for axis_index, (key_neg, key_pos) in AXES.items():
    t = threading.Thread(target=axis_worker, args=(axis_index, key_neg, key_pos), daemon=True)
    t.start()
    threads.append(t)
    print(f" - Started Joystick Axis: {axis_index} using keys {key_neg}:{key_pos}")

t = threading.Thread(target=button_worker, daemon=True)
t.start()
threads.append(t)
print("Started Buttons Handler")

t = threading.Thread(target=hat_worker, daemon=True)
t.start()
threads.append(t)
print("Started POV Hat Handler")

print("\nAll threads started successfully. Press Ctrl+C to exit.")

try:
    while True:
        time.sleep(1)  # Main thread idles
except KeyboardInterrupt:
    print("Exiting...")
    pygame.quit()
