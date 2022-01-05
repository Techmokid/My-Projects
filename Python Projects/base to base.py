import matplotlib.pyplot as plt
import math,time

def ToBinary(x,lockToBits=0):
    x = int(x)
    b = 0
    sentence = ""
    
    if (lockToBits != 0):
        b = lockToBits
        if (x == 0):
            i = 0
            sentence = ""
            while (i < lockToBits):
                i += 1
                sentence += "0"
            return sentence
        while (x >= pow(2,lockToBits)):
            x = x - pow(2,lockToBits)
    else:
        if (x == 0):
            return "0"
        b = math.ceil(math.log(x,2))
    
    while (b > -1):
        if (x - pow(2,b) > -1):
            x = x - pow(2,b)
            sentence += "1"
        else:
            sentence += "0"
        b -= 1
    
    if (sentence[0] == '1'):
        return str(sentence)
    sentence = sentence[1:]
    return str(sentence)

def FromBinary(x):
    x = str(x)
    y = len(x)
    result = 0
    
    for i in x:
        if (i == "1"):
            result += pow(2,y - 1)
        y -= 1
    return str(result)

def ReverseBinary(x):
    x = str(x)
    length = len(x)
    result = ""
    
    i = 0
    while (i < length):
        result += x[-1:]
        x = x[:-1]
        i += 1
    
    return str(result)

i = 0
a = []
while (i < 1000000):
    a.append(i - int(FromBinary(ReverseBinary(ToBinary(i)))))
    i += 1
plt.plot(a)
plt.show()
