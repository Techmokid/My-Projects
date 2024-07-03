NumberSymbol        = "⠼"
CapitalLetterSymbol = "⠠"
ASCIIList           = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" + ".,?!:;-/<>()" + "1234567890"
BrailleList         = "⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚⠅⠇⠍⠝⠕⠏⠟⠗⠎⠞⠥⠧⠺⠭⠽⠵" + "⠲⠂⠦⠖⠒⠆⠤⠌⠪⠕⠣⠜" + "⠁⠃⠉⠙⠑⠋⠛⠓⠊⠚"

def convertStoB(x):
    result = ""
    for i in x:
        if (i == " ") or (i == None) or (i == chr(10240)):
            result += " "
            continue

        if i.isupper():
            result += CapitalLetterSymbol
        if i.isnumeric():
            result += NumberSymbol
        i = i.upper()

        index = ASCIIList.find(i)
        if index == -1:
            result += "_"
        else:
            result += BrailleList[index]
    return result

def convertBtoS(x):
    result = ""
    nextCharCapital = False
    nextCharNumeric = False
    for i in x:
        if (i == " ") or (i == None) or (i == chr(10240)):
            result += " "
            continue
        if i == CapitalLetterSymbol:
            nextCharCapital = True
            continue
        if i == NumberSymbol:
            nextCharNumeric = True
            continue

        index = BrailleList.find(i)
        if index == -1:
            result += "_"
        else:
            asciiChar = ASCIIList[index]
            if nextCharCapital:
                result += asciiChar
            elif nextCharNumeric:
                result += ASCIIList[index + 48 - 10]
            else:
                result += asciiChar.lower()

        nextCharCapital = False
        nextCharNumeric = False
    return result

def doConversionTest():
    print("Running diagnostics test")

    # Test for ASCII to Braille and back
    print("\nChecking if all elements in ASCIIList have Braille equivalents")
    orig = ASCIIList
    print("ASCII in:  " + orig)
    convertedOnce = convertStoB(orig)
    print("Converted: " + convertedOnce)
    convertedBack = convertBtoS(convertedOnce)
    print("Returned:  " + convertedBack)
    
    if orig == convertedBack:
        print("Test results: Success")
    else:
        print("Test results: Failed")

    # Test for Braille to ASCII and back
    print("\nChecking if all elements in BrailleList have ASCII equivalents")
    orig = BrailleList
    print("ASCII in:  " + orig)
    convertedOnce = convertBtoS(orig)
    print("Converted: " + convertedOnce)
    convertedBack = convertStoB(convertedOnce)
    print("Returned:  " + convertedBack)
    
    if orig == convertedBack:
        print("Test results: Success")
    else:
        print("Test results: Failed")

doConversionTest()
