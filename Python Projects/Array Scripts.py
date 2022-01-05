import math,time

def FindLargestInArray(arr):
    arr_size = len(arr)
    first = -2147483648
    for i in range(arr_size):
        if (arr[i] > first):
            first = arr[i]
    return first

def FindSmallestInArray(arr):
    first = 2147483648
    arr_size = len(arr)
    for i in range(arr_size):
        if (arr[i] < first):
            first = arr[i]
    return first

def ClosestToZero(arr):
    #Please note that because of the way this works, it will only put out the absolute value, meaning the solution is ALWAYS POSITIVE, even if the input is negative!
    arr_size = len(arr)
    for i in range(arr_size):
        arr[i] = Absolute(arr[i])
    result = FindSmallestInArray(arr)
    return result

def Absolute(value):
    value = math.sqrt(math.pow(value,2))
    return value

def ArrayRange(arr):
    maximum = FindLargestInArray(arr)
    minimum = FindSmallestInArray(arr)
    Arr_Range = maximum - minimum
    return Arr_Range
    
def ArrayAverage(arr):
    arr_size = len(arr)
    totalSum = 0
    for i in range(arr_size):
        totalSum += arr[i]
    Arr_Average = totalSum / arr_size
    return Arr_Average

def ArrayMedian(arr):
    arr.sort()
    arr_size = len(arr)
    position = 0
    position = int(arr_size/2)
    #Swap the commented and uncommented lines if you want to return an array with both values instead of a single averaged float/int
    if (arr_size % 2 == 0):
        #result = [arr[position-1],arr[position]]
        result = (arr[position-1] + arr[position])/2
    else:
        #result = [arr[position]]
        result = arr[position]
    return result

def ArrayVariance(arr):
    arr_size = len(arr)
    Muo_Squared = math.pow(ArrayAverage(arr),2)
    E_Of_X_Squared = 0
    
    for i in range(arr_size):
        E_Of_X_Squared += math.pow(arr[i],2)
    E_Of_X_Squared = E_Of_X_Squared/arr_size
    result = E_Of_X_Squared - Muo_Squared
    return result

def ArrayStandardDeviation(arr):
    result = math.sqrt(ArrayVariance(arr))
    return result

def IsWithinRangeOfValue(x,value,distance):
    if (x < value + distance):
        if (x > value - distance):
            return True
        return False
    return False

def IsWithinRange(x,minimum,maximum):
    if (x < maximum):
        if (x > minimum):
            return True
        return False
    return False

def IsArrayContentsWithinRange(arr,accuracy):
    arr_size = len(arr)
    result = True
    
    for a in range(arr_size):
        for b in range(arr_size):
            if(Absolute(arr[a]-arr[b])>accuracy):
                result = False
    return result

arrayList = [4,9,1,12,6,40,-15,-16,31,-29,36,10,-22,18,5,-1];
print("Largest in Array: " + str(FindLargestInArray(arrayList)))
print("Smallest in Array: " + str(FindSmallestInArray(arrayList)))
print("Closest Value to 0 in Array: " + str(ClosestToZero(arrayList)))
print("Range of Array: " + str(ArrayRange(arrayList)))
print("Array Average: " + str(ArrayAverage(arrayList)))
print("Array Median: " + str(ArrayMedian(arrayList)))
print("Array Var(x): " + str(ArrayVariance(arrayList)))
print("Array SD(x): " + str(ArrayStandardDeviation(arrayList)))
print()
print("Is 4 within a distance of 2 from 5: " + str(IsWithinRangeOfValue(4,5,2)))
print("Is 2 within a distance of 2 from 5: " + str(IsWithinRangeOfValue(2,5,2)))
print("Is 17 within 14 and 18: " + str(IsWithinRange(17,14,18)))
print("Is 11 within 14 and 18: " + str(IsWithinRange(11,14,18)))

#The following is an attempt at a sunlight seeker by taking the inputs from something. In this case, an array pretending to be an Arduino with its sensors in a 2x2 square arrangement
#AB
#CD
#The array follows the pattern [A,B,C,D]

Sensors = []
print("\n\n")

def ActualScript():
    global Sensors
    #WARNING: The script will do whatever it can to find the optimal solution. If the script is freaking out and not working properly, set the accuracy to something much higher
    accuracy = 1
    Discrepancies = True
    
    while(Discrepancies):
        print()
        Discrepancies = False
        Sensors = FakeArduinoComms("r")
        Calculated_Sensors_Solution = Sensors
        
        #Vertical Discrepancies
        if(IsWithinRangeOfValue(Sensors[0]+Sensors[1],Sensors[2]+Sensors[3],accuracy)==False):
            Discrepancies = True
            print("Vertical Discrepency Detected. Calculating Solution...")
            if (Sensors[0]+Sensors[1]>Sensors[2]+Sensors[3]):
                print("Calculated Solution: Move Up")
                Calculated_Sensors_Solution[0] += 1
                Calculated_Sensors_Solution[1] += 1
                Calculated_Sensors_Solution[2] -= 1
                Calculated_Sensors_Solution[3] -= 1
            else:
                print("Calculated Solution: Move Down")
                Calculated_Sensors_Solution[0] -= 1
                Calculated_Sensors_Solution[1] -= 1
                Calculated_Sensors_Solution[2] += 1
                Calculated_Sensors_Solution[3] += 1

        #Horizontal Discrepancies
        if(IsWithinRangeOfValue(Sensors[0]+Sensors[2],Sensors[1]+Sensors[3],accuracy)==False):
            Discrepancies = True
            print("Horizontal Discrepency Detected. Calculating Solution...")
            if (Sensors[0]+Sensors[2]>Sensors[1]+Sensors[3]):
                print("Calculated Solution: Move Right")
                Calculated_Sensors_Solution[0] -= 1
                Calculated_Sensors_Solution[1] += 1
                Calculated_Sensors_Solution[2] -= 1
                Calculated_Sensors_Solution[3] += 1
            else:
                print("Calculated Solution: Move Left")
                Calculated_Sensors_Solution[0] += 1
                Calculated_Sensors_Solution[1] -= 1
                Calculated_Sensors_Solution[2] += 1
                Calculated_Sensors_Solution[3] -= 1

        FakeArduinoComms("w",data=Calculated_Sensors_Solution)
        time.sleep(0.5)
    print("Optimal Solution Found. Sleeping...")
    time.sleep(10)
    print("Sleep Timer Finished. Checking for any new Discrepancies...")

def FakeArduinoComms(command,data=[]):
    global PretendArduinoSensorData
    
    if (command == "r"):
        print("Data Received")
        return PretendArduinoSensorData
    if (command == "w"):
        print("Data Sent")
        PretendArduinoSensorData = data
        print("Sensors should next read: " + str(Sensors[0]) + "," + str(Sensors[1]) + "," + str(Sensors[2]) + "," + str(Sensors[3]))
        return
    else:
        return

PretendArduinoSensorData = [6,80,6,80]
while(True):
    ActualScript()
