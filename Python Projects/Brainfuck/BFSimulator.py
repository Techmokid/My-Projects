import time,os

#public variables
pathToBrainfuckCode = "C:/Users/aj200/AppData/Local/Programs/Python/Python38/My Python Scripts/Brainfuck/Compiled Brainfuck Code.txt"

#private variables
codeToRun = ""
moving = 0
currentCell = 0
currentCommand = 0
cells = []

def Start():
    cells.append(0)
    
    global pathToBrainfuckCode
    f = open(pathToBrainfuckCode.replace("\\","/"),'r')
    data = f.read()
    f.close()
    
    data = data.replace("+","")
    data = data.replace("-","")
    data = data.replace("<","")
    data = data.replace(">","")
    data = data.replace(",","")
    data = data.replace(".","")
    data = data.replace("[","")
    data = data.replace("]","")
    data = data.replace("\n","")
    data = data.replace("\t","")
    data = data.replace(" ","")
    
    if (len(data) > 0):
        print("Invalid symbols detected! Printing command-cleared file dump: " + data + "\n\n\n")
    
    #Finally load the code into a variable
    global codeToRun
    f = open(pathToBrainfuckCode.replace("\\","/"),'r')
    codeToRun = f.read()
    f.close()
    
    codeToRun = codeToRun.replace("\n","")
    codeToRun = codeToRun.replace("\t","")
    codeToRun = codeToRun.replace(" ","")
    
    #Check file for malformation of loop commands
    if (codeToRun.count('[') != codeToRun.count(']')):
        print("File Malformed! Number Of Loop Starts Not Equal To Number Of Loop Ends!!!")
        time.sleep(5)
        os.exit()
    
    #Print out data about the code
    print("BrainFuck Runtime Environment (BFRE) created by Andrey John Rumming:")
    print(" - Number Of Additions:      \t" + str(codeToRun.count('+')))
    print(" - Number Of Subtractions:   \t" + str(codeToRun.count('-')))
    print(" - Number Of Left Movements: \t" + str(codeToRun.count('<')))
    print(" - Number Of Right Movements:\t" + str(codeToRun.count('>')))
    print(" - Number Of Loops:          \t" + str(codeToRun.count('[')))
    print(" - Number Of Screen Prints:  \t" + str(codeToRun.count('.')))
    print(" - Number Of User Inputs:    \t" + str(codeToRun.count(',')))
    print("--------------------------------------------")

def Update():
    global cells,currentCell,currentCommand
    
    temp = GetNextCommand()
    if (temp != ""):
        if (temp == "+"):
            cells[currentCell] = cells[currentCell] + 1
        elif (temp == "-"):
            cells[currentCell] = cells[currentCell] - 1
        elif (temp == "<"):
            currentCell -= 1
        elif (temp == ">"):
            currentCell += 1
            try:
                cells[currentCell] = cells[currentCell]
            except:
                cells.append(0)
        elif (temp == "."):
            print(chr(cells[currentCell]),end="")
        elif (temp == ","):
            GetUserInput()
        elif (temp == "]"):
            if (cells[currentCell] != 0):
                FindLastLoopStart()
        elif (temp == "["):
            if (cells[currentCell] == 0):
                SkipLoop()

def GetNextCommand():
    global currentCommand,codeToRun
    currentCommand += 1
    try:
        return str(codeToRun[currentCommand - 1])
    except:
        return ""

def FindLastLoopStart():
    global currentCommand
    numberOfLoopsFound = 0
    while True:
        currentCommand -= 2
        commandInQuestion = GetNextCommand()
        if ((commandInQuestion == "[") and (numberOfLoopsFound == 0)):
            break
        if (commandInQuestion == "["):
            numberOfLoopsFound -= 1
        if (commandInQuestion == "]"):
            numberOfLoopsFound += 1

def SkipLoop():
    global currentCommand
    numberOfLoopsFound = 0
    while True:
        commandInQuestion = GetNextCommand()
        if ((commandInQuestion == "]") and (numberOfLoopsFound == 0)):
            break
        if (commandInQuestion == "["):
            numberOfLoopsFound += 1
        if (commandInQuestion == "]"):
            numberOfLoopsFound -= 1

def GetUserInput():
    try:
        cells[currentCell] = ord(input("\t\tPlease Enter Data (1 = row, 2 = column): "))
    except:
        GetUserInput()

Start()
while True:
    Update()
