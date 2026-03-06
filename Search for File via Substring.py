import os,math

DoPercentageCounter = False
search_directory = r"C:/Users"
keyword = "Adafruit_NeoPixel"








print("Searching in directory: " + search_directory)
fileCount = 0
for root, dirs, files in os.walk(search_directory):
    for file in files:
        fileCount += 1
        

previousPerc = 0
currentCount = 1
print("Scanning " + str(fileCount) + " files...")
for root, dirs, files in os.walk(search_directory):
    if ((math.floor(100*currentCount/fileCount) != previousPerc) and DoPercentageCounter):
        previousPerc = math.floor(100*currentCount/fileCount)
        print(str(previousPerc) + "%")
    
    for file in files:
        filepath = os.path.join(root, file)
        currentCount += 1
        if not file.endswith(".ino"):
            continue
        
        try:
            with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                if keyword in f.read():
                    print("FOUND: " + filepath)
        except Exception:
            pass
print("100%"*DoPercentageCounter)
print("\n"*5)
print("Scan completed!")
input()
input()
input()
input()
input()
