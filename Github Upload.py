import os,shutil

normal_libraries_folders = ["C:/Users/aj200/Documents/Arduino"]
ESP8266_libraries_folders = ["C:/Users/aj200/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/"]

result = ""
for i in ESP8266_libraries_folders:
    if (os.path.exists(i)):
        i += os.listdir(i)[0]
        result = i
if (result == ""):
    raise Exception("Could not find ESP8266 directory")
ESP8266_libraries_folder = result + "/libraries"

result = ""
for i in normal_libraries_folders:
    if (os.path.exists(i)):
        result = i
if (result == ""):
    raise Exception("Could not find Arduino directory")
normal_libraries_folder = result + "/libraries"

if (os.path.exists(ESP8266_libraries_folder)):
    shutil.rmtree(ESP8266_libraries_folder)

if (os.path.exists(normal_libraries_folder)):
    shutil.rmtree(normal_libraries_folder)
    
print(ESP8266_libraries_folder)
print(normal_libraries_folder)

