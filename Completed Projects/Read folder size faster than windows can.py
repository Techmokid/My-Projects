import os

directory = "F:/"

def get_dir_size(path='.'):
    total = 0
    try:
        with os.scandir(path) as it:
            for entry in it:
                if entry.is_file():
                    total += entry.stat().st_size
                elif entry.is_dir():
                    total += get_dir_size(entry.path)
    except:
        #print("Error reading from: " + path)
        return -1
    return total

def formatStr(x):
    if (x < 1000):
        return str(x) + " B"
    elif (x < 1000000):
        return str(round(x/1000,1)) + " KB"
    elif (x < 1000000000):
        return str(round(x/1000000,1)) + " MB"
    elif (x < 1000000000000):
        return str(round(x/1000000000,1)) + " GB"
    else:
        return str(round(x/1000000000000,1)) + " TB"
    
print("Scanning directory...")

results = []
foldersTotalSize = 0
for i in next(os.walk(directory))[1]:
    folderSize = get_dir_size(directory + i)
    if not (folderSize == -1):
        foldersTotalSize += folderSize
    else:
        folderSize = 0
        
    spacer = " "*(40 - len(i))

    results.append([i,folderSize])
    #print("Folder:" + i + spacer + "Size On Disk: " + formatStr(folderSize))
print("Total files size: " + str(foldersTotalSize/1000000000) + "GB")

finalResults = []
while (len(results) > 0):
    largestIndex = 0
    for i in range(0,len(results)):
        if (results[i][1] > results[largestIndex][1]):
            largestIndex = i
    finalResults.append(results[largestIndex])
    results.pop(largestIndex)

for i in finalResults:
    spacer = " "*(40 - len(i[0]))
    print("Folder:" + i[0] + spacer + "Size On Disk: " + formatStr(i[1]))
