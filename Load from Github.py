import os,shutil

baseDir = os.getcwd()
Arduino_folder = "C:/Users/aj200/Documents/Arduino"
ESP8266_libraries_folder = "C:/Users/aj200/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/libraries"
Python_Projects_Folder = "C:/Users/aj200/AppData/Local/Programs/Python/Python38/My Python Scripts"

Github_Arduino_Folder = baseDir + "/Arduino Folder"
Github_ESP8266_Libraries_Folder = baseDir + "/ESP8266 Libraries"
Github_Python_Projects_Folder = baseDir + "/Python Projects"

def DeleteFolder(directory):
    if (os.path.exists(directory)):
        print("Deleting: " + directory)
        shutil.rmtree(directory)

DeleteFolder(Arduino_folder)
DeleteFolder(ESP8266_libraries_folder)
DeleteFolder(Python_Projects_Folder)

print("Copying Arduino Projects Folder")
shutil.copytree(Github_Arduino_Folder,Arduino_folder)
print("Copying ESP8266 Libraries Folder")
#shutil.copytree(Github_ESP8266_Libraries_Folder,ESP8266_libraries_folder)
print("Copying Python Projects Folder")
shutil.copytree(Github_Python_Projects_Folder,Python_Projects_Folder)
print("Done!")
