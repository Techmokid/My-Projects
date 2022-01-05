import os
from pprint import pprint

print("Please type directory")
filePath = "E:"
answer = ""

while (True):
    answer = input("Data: ")
    if (answer == "C:/"):
        filePath = "C:/"
        answer = ""
    if (answer == "E:/"):
        filePath = "E:/"
        answer = ""
    if (answer == "D:/"):
        filePath = "D:/"
        answer = ""
    if (answer == "F:/"):
        filePath = "F:/"
        answer = ""
    if (answer == "d"):
        answer = input("Please state file to delete\n\t")
        try:
            os.remove(filePath + answer)
            print("File Successfully Deleted!")
        except:
            print("Could Not Delete File")
    if (answer == "c"):
        answer = input("Please state file name to create\n\t")
        f = open(filePath + answer,'w')
        print("Type data to enter.\nType FILE COMPLETE in all caps to save file and end program")
        DATA = ""
        while (True):
            answer = input()
            if (answer == "FILE COMPLETE"):
                f.write(DATA)
                f.close()
                quit()
            DATA = answer + "\n"
    print("\n\n\n" + filePath + answer + "\n")
    try:
        pprint(os.listdir(filePath + answer))
        filePath = filePath + answer
    except:
        print("Could not list directory. Attempting to open file...")
        try:
            os.startfile(filePath + answer)
            print("File Successfully Opened!")
        except:
            print("FILE I/O ERROR")
    
