import time,math

primeList = []

def isPrimeInternal(x):
    global primeList
    
    #Deal with the basics first
    if ((x == 1) or (x == 2) or (x == 3) or (x == 5)):
        return True
    
    stringX = str(x)
    
    # Is the number even?
    if (int(stringX[-1]) % 2 == 0):
        return False
    if (stringX[-1] == "5"):
        return False
    
    # Does the digits add up to a number divisible by 3?
    thirdDivCheck = 0
    for i in stringX:
        thirdDivCheck += int(i)
    if (thirdDivCheck % 3 == 0):
        return False

    if (len(primeList) > 0):
        index = 0
        looperVar = math.floor(math.sqrt(x))
        while (primeList[index] <= looperVar):
            if (x % primeList[index] == 0):
                return False
            index += 1
            if (index == len(primeList)):
                break
    primeList.append(x)
    return True

def isPrime(x):
    global primeList

    #Deal with the basics first
    if ((x == 1) or (x == 2) or (x == 3) or (x == 5)):
        return True
    
    stringX = str(x)
    
    # Is the number even?
    if (int(stringX[-1]) % 2 == 0):
        return False
    if (stringX[-1] == "5"):
        return False
    
    # Does the digits add up to a number divisible by 3?
    thirdDivCheck = 0
    for i in stringX:
        thirdDivCheck += int(i)
    if (thirdDivCheck % 3 == 0):
        return False
    
    primeList = []
    for i in range(0,x - 1):
        isPrimeInternal(x)
    return isPrimeInternal(x)


print(isPrime(999997))
