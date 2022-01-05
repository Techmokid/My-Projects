import sys,os
from datetime import datetime
from xlrd import open_workbook
from xlwt import Workbook
from xlutils.copy import copy

filename = "Logged Discord Data.xls"

def findIndexPos(book,subserver):
    if (subserver in getSheetNames(book)):
        return getSheetNames(book).index(subserver)
    return -1

def getSheetNames(book):
    result = []
    try:
        i = 0
        while True:
            result += [book.sheet_by_index(i).name]
            i += 1
    except:
        pass
    return result

def CorrectColumbWidths(filename):
    return

def main():
    global filename
    
    arguments = sys.argv
    if (len(sys.argv)-1 != 3):
        print("ERROR: Wrong number of arguments")
        print("Required:")
        print("\t-subserver Name")
        print("\t-User Name")
        print("\t-Message")
        return
    
    subserver = arguments[1]
    user = arguments[2]
    msg = arguments[3]
    date = datetime.date(datetime.now())
    time = datetime.time(datetime.now())
    
    print("Server: Automatically Set To Official Nionic Discord")
    print("Subserver: \t" + str(subserver))
    print("User:   \t" + str(user))
    print("Message:\t" + str(msg))
    print("Date:   \t" + str(date))
    print("Time:   \t" + str(time))
    
    #Actually save data to excel
    ReadableBook = open_workbook(filename)
    WritableBook = copy(ReadableBook)
    
    #Scan for subserver name
    if(findIndexPos(ReadableBook,subserver) == -1):
        WritableSheet = WritableBook.add_sheet(subserver)
        WritableSheet.row(0).write(0,'Username')
        WritableSheet.row(0).write(1,'Date')
        WritableSheet.row(0).write(2,'Time')
        WritableSheet.row(0).write(3,'Message')
        WritableSheet.row(2).write(0,str(user))
        WritableSheet.row(2).write(1,str(date))
        WritableSheet.row(2).write(2,str(time))
        WritableSheet.row(2).write(3,str(msg))
        WritableBook.save(filename)
        CorrectColumbWidths(filename)
        return
    
    #subserver Found!
    ReadableSheet = ReadableBook.sheet_by_index(findIndexPos(ReadableBook,subserver))
    WritableSheet = WritableBook.get_sheet(findIndexPos(ReadableBook,subserver))
    
    StillSearching = True
    i = 1
    try:
        while (StillSearching):
            i += 1
            if(str(ReadableSheet.cell(i,0).value) == ""):
                StillSearching = False
    except:
        pass
    
    WritableSheet.row(i).write(0,str(user))
    WritableSheet.row(i).write(1,str(date))
    WritableSheet.row(i).write(2,str(time))
    WritableSheet.row(i).write(3,str(msg))
    WritableBook.save(filename)
    CorrectColumbWidths(filename)

main()
