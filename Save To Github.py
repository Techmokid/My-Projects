import os,shutil

baseDir = os.getcwd()
Arduino_folder = "C:/Users/aj200/Documents/Arduino"
ESP8266_libraries_folder = "C:/Users/aj200/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/libraries"
Python_Projects_Folder = "C:/Users/aj200/AppData/Local/Programs/Python/Python38/My Python Scripts"
Minecraft_Folder = "C:/Users/aj200/AppData/Roaming/.minecraft/saves"

Github_Arduino_Folder = baseDir + "/Arduino Folder"
Github_ESP8266_Libraries_Folder = baseDir + "/ESP8266 Libraries"
Github_Python_Projects_Folder = baseDir + "/Python Projects"
Github_Minecraft_Folder = baseDir + "/Minecraft Saves"

def DeleteFolder(directory):
    if (os.path.exists(directory)):
        print("Deleting: " + directory)
        shutil.rmtree(directory)

DeleteFolder(Github_Arduino_Folder)
DeleteFolder(Github_ESP8266_Libraries_Folder)
DeleteFolder(Github_Python_Projects_Folder)
DeleteFolder(Github_Minecraft_Folder)

#Now we have all the required info. Just copy across
print("Copying Arduino Projects Folder")
shutil.copytree(Arduino_folder,Github_Arduino_Folder)
print("Copying ESP8266 Libraries Folder")
#shutil.copytree(ESP8266_libraries_folder,Github_ESP8266_Libraries_Folder)
print("Copying Python Projects Folder")
shutil.copytree(Python_Projects_Folder,Github_Python_Projects_Folder)
print("Copying Minecraft Saves Folder")
#shutil.copytree(Minecraft_Folder,Github_Minecraft_Folder)
print("Done!")
