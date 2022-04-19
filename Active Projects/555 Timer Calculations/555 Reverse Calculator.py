import os,math

userH = abs(float(input("What is the requested high time (seconds): ")))
userL = abs(float(input("What is the requested low time (seconds):  ")))

f = open(os.getcwd() + "/Precalculated Output With Diode.txt",'r+')
lines = f.readlines()
f.close()

# 0=R1,1=R2,2=C,3=T,4=H,5=L,6=F,7=D
#------------------------
def T(C,R1,R2):
    C = uF_to_F(C)
    return 0.693 * C * (R1 + 2*R2)
def H(C,R1,R2):
    C = uF_to_F(C)
    return 0.693 * C * (R1 + R2)
def L(C,R2):
    C = uF_to_F(C)
    return 0.693 * C * R2
def F(C,R1,R2):
    C = uF_to_F(C)
    return 1/T(C,R1,R2)
def D(R1,R2):
    return 100 * (R1 + R2) / (R1 + 2*R2)
def uF_to_F(C):
    return C / 1_000_000
#------------------------
def dist(x,y):
    x = float(x)
    y = float(y)
    return abs(x-y)
def expDist(x,y):
    x = float(x)
    y = float(y)
    return math.pow(dist(x,y),5)
def percDist(x,y):
    x = float(x)
    y = float(y)
    if (x < y):
        return abs(y/x)
    else:
        return abs(x/y)
def expPercDist(x,y):
    x = float(x)
    y = float(y)
    return math.pow(percDist(x,y),5)
#------------------------

# 

bestIndex = 0
for i in range(0,len(lines)):
    bestData = lines[bestIndex].split(',')
    currentData = lines[i].split(',')

    bestClosenessH = expPercDist(bestData[4],userH)
    bestClosenessL = expPercDist(bestData[5],userL)
    currentClosenessH = expPercDist(currentData[4],userH)
    currentClosenessL = expPercDist(currentData[5],userL)
    if (math.pow(currentClosenessL,2) + math.pow(currentClosenessH,2) < math.pow(bestClosenessL,2) + math.pow(bestClosenessH,2)):
        bestIndex = i



best = lines[bestIndex].split(',')
print("R1: " + best[0])
print("R2: " + best[1])
print("C:  " + best[2])
print("T: " + best[3])
print("H: " + best[4])
print("L: " + best[5])
print("F: " + best[6])
print("D: " + best[7])
