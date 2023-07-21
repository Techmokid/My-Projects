import pyautogui,time,os,keyboard

fc = '''
import time,machine,math

x_pin = machine.DAC(machine.Pin(25))
y_pin = machine.DAC(machine.Pin(26))

#x_current = 0
#y_current = 0
#
#def X_To_Volts(x_pos):
#    return max(min(3.3,x_pos*3.3),0)
#
#def Y_To_Volts(y_pos):
#    return max(min(3.3,y_pos*3.3),0)
#
#def MoveToPos(x_pos,y_pos,t):
#    global x_current,y_current
#    
#    if (t == 0):
#        x_current = x_pos
#        y_current = y_pos
#    x_inc = (x_pos - x_current)/t
#    y_inc = (y_pos - y_current)/t
#    for i in range(0,t):
#        x_pin.write(math.floor(255 * X_To_Volts(x_current)))
#        y_pin.write(math.floor(255 * Y_To_Volts(y_current)))
#        x_current += x_inc
#        y_current += y_inc
#    x_pin.write(math.floor(255 * X_To_Volts(x_pos)))
#    y_pin.write(math.floor(255 * Y_To_Volts(y_pos)))

startTime = time.time()

t = 0
while(True):
    x = round(75*math.sin(t)+127 + 30*math.sin(t/1000))
    y = round(75*math.cos(t)+127 + 30*math.cos(t/1000))
    x_pin.write(x)
    y_pin.write(y)
    
    t += 2
'''

tmp = fc.split('\n')
fc = []

for i in tmp:
    fc.append(i + "\n")

finalResult = []
for i,x in enumerate(fc):
    if (x != ""):
        if ((x != '\n') and (x[0] != "#")):
            finalResult.append(x)
        if ((i > 0) and (fc[i-1][0] == ' ') and (fc[i][0] != ' ')):
            finalResult.append('\n\n')

msg = ""
for i in finalResult:
    msg += i

print(msg)
print()
print("--------------------------------------------------------------------------------------------------")
print()

print("Script formatted and ready to run. Please hit the F4 key when ready to type in the script to repl")
os.system('start cmd /K rshell -p COM11 -b 115200 repl')

keyboard.wait('F12')

pyautogui.write(msg + "\n")
