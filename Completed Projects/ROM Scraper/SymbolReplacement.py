def replaceCharAtIndex(inputString,index,replacementChar):
    return inputString[:index] + replacementChar + inputString[1+index:]

def countCharInString(inputString,char):
    result = 0
    for i in inputString:
        if (i == char):
            result += 1
    return result

def getIndexReplacement(inputString,index,replacementKeys):
    result = []
    for replacementChar in replacementKeys:
        result.append(inputString[:index] + replacementChar + inputString[1+index:])
    return result

def replaceAllOfSymbol(inputString,key,replacementKeys):
    if (key not in inputString):
        return [inputString]
    
    looper = 0
    symbolIndexes = []
    for i in inputString:
        if (i == key):
            symbolIndexes.append(looper)
        looper += 1
    
    result = []
    for index in symbolIndexes:
        try:
            for i in getIndexReplacement(inputString,index,replacementKeys):
                result.append(i)
        except:
            pass
    

    result2 = []
    if (key in result[0]):
        for i in result:
            for x in replaceAllOfSymbol(i,key,replacementKeys):
                result2.append(x)
        return result2
    return result
