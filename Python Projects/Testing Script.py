import math
import time

nextSquare = 1
currentValue = 0
piConstant = math.pow(math.pi,2) / 6

def calculate(nextSquare,currentValue,piConstant):
    while(True):
        currentValue += 1 / math.pow(nextSquare,2)
        nextSquare += 1
        value = piConstant - currentValue
        print (value)

calculate(nextSquare,currentValue,piConstant)
