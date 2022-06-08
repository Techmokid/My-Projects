import os

userPathOverride = False
YenkaPath = "C:/Users/aj200/Downloads/Neuron.yka"
DestPath = "C:/Users/aj200/Documents/"

if (userPathOverride):
    YenkaPath = input("Please enter the directory of the yenka file to convert: ")

    looping = True
    while(looping):
        looping = False
        if(not os.path.exists(YenkaPath)):
            looping = True
            print("ERROR: File does not exist")
        elif(YenkaPath[-4:] != ".yka"):
            looping = True
            print("ERROR: Please enter a valid yenka file")
        print()
        YenkaPath = input("Please enter the directory of the yenka file to convert: ")
    
    DestPath = input("Please enter the directory of the resulting folder: ")
    looping = True
    while(looping):
        looping = False
        if(not os.path.exists(DestPath)):
            looping = True
            print("ERROR: Folder does not exist")
        print()
        YenkaPath = input("Please enter the directory of the resulting folder: ")
outputPath = os.path.join(DestPath,"Yenka Converter")

#-------------------------------------------------------------

print()
print("Input directory: " + YenkaPath)
print("Output directory: " + outputPath)

f = open(YenkaPath,"rb")
byte = f.read(1)
while byte:
    print(byte)
    byte = f.read(1)
f.close()

print(yenkaFileContents)
