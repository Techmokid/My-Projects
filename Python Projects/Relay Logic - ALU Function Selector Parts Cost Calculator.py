import time

costOfRelaysEach = 5
costOfDiodesEach = 0.32
numberOfBinaryDigits = 8

def numberToBinary(x):
    sentence = ""
    
    if (x-128 >= 0):
        x -= 128
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-64 >= 0):
        x -= 64
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-32 >= 0):
        x -= 32
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-16 >= 0):
        x -= 16
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-8 >= 0):
        x -= 8
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-4 >= 0):
        x -= 4
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-2 >= 0):
        x -= 2
        sentence += "1"
    else:
        sentence += "0"
    
    if (x-1 >= 0):
        x -= 1
        sentence += "1"
    else:
        sentence += "0"
    
    return sentence

i = 0
numberOf0s = 0
numberOf1s = 0

while (i < pow(2,numberOfBinaryDigits)):
    numberOf0s += numberToBinary(i).count("0")
    numberOf1s += numberToBinary(i).count("1") + 1
    i += 1

print("Number Of Relays: " + str(numberOf1s) + "\tNumber Of Diodes: " + str(numberOf0s))
print("Cost Of Relays: $" + str(round(numberOf1s*costOfRelaysEach,2)) + "\tCost Of Diodes: $" + str(round(numberOf0s*costOfDiodesEach,2)))
print("Total Cost Of Parts: $" + str(round(numberOf1s*costOfRelaysEach + numberOf0s*costOfDiodesEach,2)))
time.sleep(5)
