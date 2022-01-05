# This is a potential Brainfuck Compiler from a rough version of C to Brainfuck
# Brainfuck is meant to operate on a tape (Turing complete style)

# "+" means to increment the current value on the tape by 1
# "-" means to decrement the current value on the tape by 1
# "<" means to move the tape to the left
# ">" means to move the tape to the right
# "." means to print the value in memory
# "," means to take input as a byte from user
# "[" means to run the code until the corresponding "]" only if the value in memory is not zero
# "]" means to go back to the corresponding "[" only if the value in memory is not zero
# E.g. [some code] is the same as "while (memorySpace != 0) { some code }"

# Mempos 0-1 is for basic calculations
# Mempos 2 is for calculation output
# Mempos 3 is for data copying operations
# Mempos 4 is for letter declaration
# Mempos 5+ is for the user to mess with.

# While using the system cells will not halt or crash the program, it will lead to undesired results
# For best experience, please do not use the first 5 memory cells.
# The program will automatically skip to line 6 without user intervention
# Automatically starts the code with ">>>>>" to skip system cells

scriptOutput = ""
positionCounter = 0
gosubMemory1 = 0
gosubMemory2 = 0

def clearDataInCell():
    #Until it is equal to zero, minus one
    global scriptOutput
    scriptOutput += "[-]"
    return

def moveToRight():
    #Simply move to the right
    global scriptOutput,positionCounter
    scriptOutput += ">"
    positionCounter += 1
    return

for i in range(5):
    moveToRight()

def moveToLeft():
    #Simply move to the left
    global scriptOutput,positionCounter
    scriptOutput += "<"
    positionCounter -= 1
    return

def setDataInCell(value):
    #Set the value in the cell to zero, then add the required amount
    clearDataInCell()
    addToCell(value)
    return

def addToCell(value=1):
    #Add a certain value to the cell
    global scriptOutput
    for i in range(value):
        scriptOutput += "+"
    return
        
def subtractFromCell(value=1):
    #Subtract a certain value from the cell
    global scriptOutput
    for i in range(value):
        scriptOutput += "-"
    return

def printCurrentValue():
    #Print whatever value is on screen right now
    global scriptOutput
    scriptOutput += "."
    return

def printLetter(letterToPrint):
    #Ah, a complex one. Print a letter
    global gosubMemory1
    
    #Go to the system memory for letter memory
    gotoMemPos(4)
    
    #Set the data to the required letter value
    setDataInCell(ord(letterToPrint))
    printCurrentValue()
    return

def printSentence(sentenceToPrint):
    for i in sentenceToPrint:
        printLetter(i)

def takeUserInput():
    global scriptOutput
    scriptOutput += ","
    return

def saveScriptToFile():
    global scriptOutput
    with open("Compiled Brainfuck Code.txt",'w+') as f:
        f.write(scriptOutput)
    return

def gotoMemPos(position):
    global scriptOutput,gosubMemory1
    spacesToMove = abs(positionCounter - position)
    if (spacesToMove == 0):
        return
    
    gosubMemory1 = positionCounter
    
    right = True if (positionCounter - position < 0) else False
    
    for i in range(spacesToMove):
        if (right):
            moveToRight()
        else:
            moveToLeft()
    return

def savePosition(position=positionCounter):
    global gosubMemory2
    gosubMemory2 = position
    return

def loadPosition():
    gotoMemPos(gosubMemory2)
    return

def startWhileNotZero():
    global scriptOutput
    scriptOutput += "["
    return

def endWhileNotZero():
    global scriptOutput
    scriptOutput += "]"
    return

def copyCellToMemory(startPos,endPos,returnToStartAfterCompletion=False):
    systemCopyMemoryCell = 3
    
    startWhileNotZero()
    gotoMemPos(endPos)
    addToCell()
    gotoMemPos(systemCopyMemoryCell)
    addToCell()
    gotoMemPos(startPos)
    subtractFromCell()
    endWhileNotZero()
    
    startWhileNotZero()
    gotoMemPos(startPos)
    addToCell()
    gotoMemPos(systemCopyMemoryCell)
    subtractFromCell()
    endWhileNotZero()
    
    if(returnToStartAfterCompletion):
        gotoMemPos(startPos)
    else:
        gotoMemPos(endPos)
    return

def compareIsEqualToValue(value):
    global positionCounter,scriptOutput
    
    #First, clear mempos 0, 1, and 2
    savePosition(positionCounter)
    gotoMemPos(2)
    clearDataInCell()
    gotoMemPos(1)
    clearDataInCell()
    gotoMemPos(0)
    clearDataInCell()
    loadPosition()
    
    #Load values into system memory
    copyCellToMemory(positionCounter,0)
    gotoMemPos(1)
    setDataInCell(value)
    gotoMemPos(0)
    
    #Now that we have them loaded in, let's check if they are equal. First make mempos 0 equal to 0
    startWhileNotZero()
    subtractFromCell()
    gotoMemPos(1)
    subtractFromCell()
    gotoMemPos(0)
    endWhileNotZero()
    
    #Now simply check to see if mempos 1 contains the number 0 and put the result in mempos 2.
    scriptOutput += ">>+<<[>-<-]>[>-]"
    positionCounter = 2
    loadPosition()

def compareIsNotEqualToValue(value):
    global positionCounter,scriptOutput
    
    #First, clear mempos 0, 1, and 2
    savePosition(positionCounter)
    gotoMemPos(2)
    clearDataInCell()
    gotoMemPos(1)
    clearDataInCell()
    gotoMemPos(0)
    clearDataInCell()
    loadPosition()
    
    #Load values into system memory
    copyCellToMemory(positionCounter,0)
    gotoMemPos(1)
    setDataInCell(value)
    gotoMemPos(0)
    
    #Now that we have them loaded in, let's check if they are equal. First make mempos 0 equal to 0
    startWhileNotZero()
    subtractFromCell()
    gotoMemPos(1)
    subtractFromCell()
    gotoMemPos(0)
    endWhileNotZero()
    
    #Now simply check to see if mempos 1 contains the number 0 and put the result in mempos 2.
    scriptOutput += "[>-<-]>[>+]"
    positionCounter = 2
    loadPosition()

def printSentence(string):
    for i in string:
        printLetter(i)

printSentence('It sure is!')
saveScriptToFile()


































































