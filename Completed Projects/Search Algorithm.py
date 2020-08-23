import os,time,shutil
from tkinter import *

class searchAlgorithm():
    def setValues(self, searchKey, filepath, strictSearch, multiLevelSearch, ignoreCase, includeFolders, includeFiles, maxResults):
        self.searchKey = searchKey
        self.filepath = filepath
        
        #Search options
        self.strictSearch = strictSearch
        self.multiLevelSearch = multiLevelSearch
        self.ignoreCase = ignoreCase

        self.includeFolders = includeFolders
        self.includeFiles = includeFiles
        self.maxResults = maxResults

    def printList(self,x):
        numberOfResults = 0
        for i in x:
            if (numberOfResults < self.maxResults):
                print(i)
            numberOfResults += 1

    def getAllSegmentsOfString(self,x):
        segmentList = []
        currentPointer = 0
        secondaryPointer = 0
        while (currentPointer < len(x)):
            if (currentPointer != secondaryPointer):
                segmentList.append(x[currentPointer:secondaryPointer])
            
            secondaryPointer += 1
            if (secondaryPointer > len(x)):
                currentPointer += 1
                secondaryPointer = currentPointer

        return segmentList

    def countStringMatches(self,string,key):
        if (key in string):
            #return pow(len(key)*string.count(key),2)
            return len(key)*string.count(key)*1000

        hasValue = False
        for i in string:
            for x in key:
                if (x == i):
                    hasValue = True
        if not hasValue:
            return 0
        
        #Here we have to return the number of matches of substrings by moving a pointer around
        longestString = 0
        for i in self.getAllSegmentsOfString(key):
            isKeyInString = (i in string)
            if (self.ignoreCase):
                isKeyInString = (i.lower() in string.lower())
            if (isKeyInString and (len(i) > longestString)):
                longestString = len(i)
        return longestString

    def search(self, searchKey, filepath, strictSearch, multiLevelSearch, ignoreCase, includeFolders, includeFiles, maxResults):
        if (filepath == ""):
            filepath = os.getcwd()
        
        self.setValues(searchKey, filepath, strictSearch, multiLevelSearch, ignoreCase, includeFolders, includeFiles, maxResults)
        
        #This onwards is the search algorithm
        result = []
        if (self.strictSearch):
            if (self.multiLevelSearch):
                for subdir, dirs, files in os.walk(self.filepath):
                    if (self.includeFiles):
                        for file in files:
                            if (self.ignoreCase):
                                if (self.searchKey.lower() in file.lower()):
                                    result.append(subdir + "/" + file)
                            else:
                                if (self.searchKey in file):
                                    result.append(subdir + "/" + file)
                    if (self.includeFolders):
                        for folder in dirs:
                            if (self.ignoreCase):
                                if (self.searchKey.lower() in folder.lower()):
                                    result.append(subdir + "/" + file + "/")
                            else:
                                if (self.searchKey in folder):
                                    result.append(subdir + "/" + file + "/")
            else:
                for file in os.listdir(self.filepath):
                    if (self.searchKey in file):
                        if (self.includeFiles and os.path.isfile(self.filepath + "/" + file)):
                            result.append(self.filepath + "/" + file + "/")
                        if (self.includeFolders and os.path.isdir(self.filepath + "/" + file)):
                            result.append(self.filepath + "/" + file + "/")
            
            #Here we have the list of all found results. Now we just have to sort by relevancy
            #Is any of the items the same name the user was looking for after removing the filetype?
            for i in result:
                if (len(i.split('.')) > 1):
                    for x in i.split('.'):
                        if (x == self.searchKey):
                            result.insert(0, result.pop(result.index(i)))
            #Is any of the items literally the EXACT name the user was asking for?
            for i in result:
                if (i == self.searchKey):
                    result.insert(0, result.pop(result.index(i)))
        else:
            #Strict search is off. Different rules apply and hence the result list is handled differently
            #Instead, we wanna add ALL directories and files
            if (self.multiLevelSearch):
                for subdir, dirs, files in os.walk(self.filepath):
                    if (self.includeFiles):
                        for file in files:
                            result.append(subdir + "/" + file)
                    if (self.includeFolders):
                        for folder in dirs:
                            result.append(subdir + "/" + file)
            else:
                for i in os.listdir(self.filepath):
                    if (self.includeFiles and (os.path.isfile(i))):
                        result.append(i)
                    if (self.includeFolders and (os.path.isdir(i))):
                        result.append(i)
            
            #Now sort them by how close they are to the original search
            #The best way of doing this may just be to count the max number of letters in a row
            # that match the search key
            matchCounter = []
            for i in result:
                matchCounter.append(self.countStringMatches(i,self.searchKey))

            #Here we still have to sort the list. We have the occurances list, and the main list
            #Just write a custom function that sorts list A by the values in list B, and you are done!
            endResult = []
            
            tempResult = result.copy()
            tempMatchCounter = matchCounter.copy()
            while(len(tempResult) != 0):
                currentLargestIndex = 0
                
                loops = 0
                for i in tempMatchCounter:
                    if (tempMatchCounter[loops] > tempMatchCounter[currentLargestIndex]):
                        currentLargestIndex = loops
                    loops += 1
                endResult.append(tempResult[currentLargestIndex])
                
                tempResult.pop(currentLargestIndex)
                tempMatchCounter.pop(currentLargestIndex)
            result = endResult.copy()
        self.printList(result)

for i in range(0, 5):
    print()

def quitProgram():
    for i in range(0, 5):
        print()
    quit()
#Here is the actual commandline handler and script
maxResults = 20
strictSearch = False
multiLevelSearch = True
ignoreCase = True
folders = False
files = True

if (len(sys.argv) == 1):
    print("ERROR: Python file requires search key")
    quitProgram()

def checkMultipleValues(val,listToCheck):
    for i in val:
        if (i == val):
            return True
    return False

def booleanConvert(val):
    val = val.lower()
    if (checkMultipleValues(val,["t","true","yes","1","+"])):
        return True
    if (checkMultipleValues(val,["f","false","no","0","-"])):
        return False
    print("ERROR: Invalid switch input: " + str(val))
    print("Accepted Answers:")
    print(" - 't'            - 'f'")
    print(" - 'true'         - 'false'")
    print(" - 'yes'          - 'no'")
    print(" - '1'            - '0'")
    print(" - '+'            - '-'")
    quitProgram()

if (sys.argv[1] == "help"):
    if (len(sys.argv) == 2):
        print("Commandline Switches:")
        print(" - strictSearch:     DEFAULT=" + str(bool(strictSearch)) + "\tDo you want to ignore all files/folders that don't contain the search phrase?")
        print(" - multiLevelSearch: DEFAULT=" + str(bool(multiLevelSearch)) + "\tIf this is set to False, the search will only check the root folder. No subdirectories will be checked")
        print(" - ignoreCase:       DEFAULT=" + str(bool(ignoreCase)) + "\tDo you want to ignore the capitalisation of file names?")
        print(" - includeFolders:   DEFAULT=" + str(bool(folders)) + "\tDo you want to include folders in your search results?")
        print(" - includeFiles:     DEFAULT=" + str(bool(files)) + "\tDo you want to include files in your search results?")
        print(" - maxResults:       DEFAULT=" + str(int(maxResults)) + "\t\tHow many results maximum do you want returned?")
        print()
        print("Example usage:")
        print("'python \"" + os.path.basename(__file__) + "\" exampleFolder.txt strictSearch=True includeFolders=True'")
    else:
        print("ERROR: Too many arguments! Just type 'python \"" + os.path.basename(__file__) + "\" help' for information")
    quitProgram()

key = sys.argv[1]
for i in range(2, len(sys.argv)):
    arg = sys.argv[i]
    
    argResult = arg[arg.find("=")+1:]
    if (arg.startswith("strictSearch=")):
        strictSearch = booleanConvert(argResult)
    elif (arg.startswith("multiLevelSearch=")):
        multiLevelSearch = booleanConvert(argResult)
    elif (arg.startswith("ignoreCase=")):
        ignoreCase = booleanConvert(argResult)
    elif (arg.startswith("includeFolders=")):
        includeFolders = booleanConvert(argResult)
    elif (arg.startswith("includeFiles=")):
        includeFiles = booleanConvert(argResult)
    elif (arg.startswith("maxResults=")):
        maxResults = int(argResult)
    else:
        print("ERROR: Variable not recognised - '" + str(arg) + "'")
        print("Type 'python \"" + os.path.basename(__file__) + "\" help' for information")
        quitProgram()


sa = searchAlgorithm()
sa.search(key, "", strictSearch, multiLevelSearch, ignoreCase, folders, files, maxResults)



















