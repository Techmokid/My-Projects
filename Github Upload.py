import os,shutil

baseDir = os.getcwd()
Arduino_folder = "C:/Users/aj200/Documents/Arduino"
ESP8266_libraries_folder = "C:/Users/aj200/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/libraries"
Unity3D_Projects_Folder = "C:/Users/aj200/Documents/Unity Projects"
Python_Projects_Folder = "C:/Users/aj200/AppData/Local/Programs/Python/Python38/My Python Scripts"

Github_Arduino_Folder = baseDir + "/Arduino Folder"
Github_ESP8266_Libraries_Folder = baseDir + "/ESP8266 Libraries"
Github_Unity3D_Projects_Folder = baseDir + "/Unity3D Projects"
Github_Python_Projects_Folder = baseDir + "/Python Projects"

def StartFolder(directory):
    if (os.path.exists(directory)):
        print("Deleting: " + directory)
        shutil.rmtree(directory)
    #os.mkdir(directory)

StartFolder(Github_Arduino_Folder)
StartFolder(Github_ESP8266_Libraries_Folder)
StartFolder(Github_Unity3D_Projects_Folder)
StartFolder(Github_Python_Projects_Folder)

#Now we have all the required info. Just copy across
print("Copying Arduino Projects Folder")
shutil.copytree(Arduino_folder,Github_Arduino_Folder)
print("Copying ESP8266 Libraries Folder")
#shutil.copytree(ESP8266_libraries_folder,Github_ESP8266_Libraries_Folder)
print("Copying Unity3D Projects Folder")
shutil.copytree(Unity3D_Projects_Folder,Github_Unity3D_Projects_Folder)
print("Copying Python Projects Folder")
shutil.copytree(Python_Projects_Folder,Github_Python_Projects_Folder)
print("Done!")
