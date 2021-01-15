#https://coronavirus.jhu.edu/map.html?fbclid=IwAR3iMsAKkkl_0p3y4ohwSt2ChUFUEdBUu_Dfn7O_kpKA3itNuOsVOx9vduM
#https://hgis.uw.edu/virus/?fbclid=IwAR2UdNKgxeBKRNoAK5G59kuEGkQgo73-dFkDH_r7pO6h1AntQBSd4rUYJaw
#https://www.worldometers.info/coronavirus/?fbclid=IwAR1QqQBkcGY3I2r0f4lHSQibBXZDJWaQtP6yQhPVuHn-fJo1JiedXEDDDVM

import requests,time,os,urllib,shutil,openpyxl
from datetime import datetime, timedelta

directoryToExcelDoc2 = ""

def splitTextToLines(text):
    result = [""]
    pos = 0
    for i in text:
        if (i != '\n'):
            result[pos] += i
        else:
            result.append("")
            pos += 1
    return result

def getValues(valIn,key,endPoint="</div"):
    divs = 0
    running = False
    myString = ""
    results = []
    for i in valIn:
        if(key in i):
            running = True
        if (("<div" in i) and (running)):
            divs += 1
        if ((divs > 0) and (endPoint in i)):
            divs -= 1
            if (divs == 0):
                running = False
                result.append(myString)
                myString = ""
        if (divs > 0):
            myString += i + '\n'
    return results

def getLineOfValue(data,key):
    looper = 0
    for i in data:
        if (key in i):
            return looper
        looper += 1

def getListSubstring(data,start,end):
    looper = 0
    result = []
    for i in data:
        if ((looper > start) and (looper < end)):
            result.append(i)
        looper += 1
    return result

def getListToString(lst,key):
    result = []
    for i in lst:
        if (key in i):
            return result
        result.append(i)
    return None

def download_url(url, save_Path):
    with urllib.request.urlopen(url) as dl_file:
        with open(save_path, 'wb') as out_file:
            out_file.write(dl_file.read())

def HasInternetConnection():
    try:
        urllib.request.urlopen('http://google.com')
        return True
    except:
        return False

while(HasInternetConnection() == False):
    print("Waiting for internet connection...")
    time.sleep(10)

def printList(text):
    for i in text:
        print("----------------------------------------------------------------------")
        time.sleep(1)
        print(i)
        input()

def getValueFromList(data,startPoint,key,endPoint):
    result = []
    currentList = ""
    running = 0
    for line in data:
        #print("Running:",running,"\t\tLine:",line)
        #time.sleep(0.5)
        if (startPoint in line):
            running += 1
        if (running != 0):
            currentList += line + "\n"
        if (endPoint in line):
            running -= 1
            if (running == 0):
                if (key in currentList):
                    result.append(currentList)
                currentList = ""
    return result

def reformatData(rawData):
    worldDataList = []
    
    for countryData in rawData:
        countryDataList = []
        lineType = 0
        for line in splitTextToLines(countryData):
            if ("text-align:right" in line):
                value = line[line.find(">")+1:-5]
                lineType += 1
                
                if ((lineType > 0) and (lineType < 13)):
                    countryDataList.append(value)
                elif (lineType == 13):
                    temp2 = value[value.find(">") + 1:]
                    countryDataList.append(temp2[:temp2.find("<")])
                    
                    temp = value[value.find("\"")+1:]
                    CountryDirectory = temp[:temp.find("\"")]
                    RawCountryName = CountryDirectory[CountryDirectory[:-1].rfind("/") + 1:-1]
                    PureCountryName = RawCountryName.split("-")[0]
                    countryDataList.append("Country Name: \t\t" + PureCountryName)
        worldDataList.append(countryDataList)
    return worldDataList

#Run data collection services
print("[Data Collection]:   Collecting data from \"World O Meters\"...")
rawSiteData_1 = splitTextToLines(requests.get("https://www.worldometers.info/coronavirus/?fbclid=IwAR1QqQBkcGY3I2r0f4lHSQibBXZDJWaQtP6yQhPVuHn-fJo1JiedXEDDDVM").text)
scrapedSiteData_1 = getLineOfValue(rawSiteData_1,"<table id=\"main_table_countries_today\"")

print("[Data Collection]:   Sorting data by country...")
temp_1 = getListSubstring(rawSiteData_1,scrapedSiteData_1,len(rawSiteData_1) - 1)
dataList = getValueFromList(temp_1,"<tr","style=\"font-weight:","</tr>")

print("[Data Collection]:   Reformatting data...")
worldDataList = reformatData(dataList)

#Create the required database
print("[Database Creation]: Creating required files...")
path = os.getcwd() + "/Retrieved Data/"
if (os.path.exists(path)):
    while(True):
        try:
            shutil.rmtree(path)
            break
        except:
            print("Cannot access required folder. Make sure nothing is using the following folder:")
            print(" - " + path)
            print("\nRetrying in 30 seconds...\n\n")
            time.sleep(30)

os.mkdir(path)

print("[Database Creation]: Saving raw data to file...")

book = openpyxl.Workbook()
sheet = book.active
sheet.title = "Worldwide Active Cases"

activeCaseCount = 0
for countryDataList in worldDataList:
    temp = ""
    for i in countryDataList[6]:
        if (i.isdigit()):
            temp += i
    if (len(temp) != 0):
        activeCaseCount += int(temp)

#sheet["A6"] = "COUNTRIES:"
#sheet["B6"] = "ACTIVE CASES:"
#sheet["C6"] = "WAS:"
#sheet["D6"] = "INCREASE/DECREASE:"
#sheet["E6"] = "PERCENTAGE:"
#sheet["F6"] = "TOTAL CASES:"
#sheet["G6"] = "RECOVERED:"
#sheet["H6"] = "DIED:"
#sheet["I6"] = "OUTCOMES:"
#sheet["J6"] = "OUTCOME PERCENTAGE:"

def strToInt(inputVal):
    if (isinstance(inputVal, int)):
        return inputVal
    
    result = ""
    for i in inputVal:
        
        if (i.isdigit()):
            result += i
    
    if (len(result) > 0):
        return int(result)
    return 0

wb2 = openpyxl.load_workbook(directoryToExcelDoc2)
ws2 = wb2["Worldwide Active Cases"]

for i in range (1, ws2.max_row + 1): 
    for j in range (1, ws2.max_column + 1): 
        # reading cell value from source excel file 
        c = ws2.cell(row = i, column = j) 
  
        # writing the read value to destination excel file 
        sheet.cell(row = i, column = j).value = c.value

for countryDataList in worldDataList:
    currentLine = 5
    for line in range(7,sheet.max_row):
        if (sheet["A" + str(line)].lower() == countryDataList[12].lower()):
            currentLine = line
    if (currentLine == 5):
        print("LINE ERROR!!! Could not find:",countryDataList[12])
    
    sheet["A" + str(currentLine)] = countryDataList[12]
    sheet["B" + str(currentLine)] = countryDataList[6]
    sheet["C" + str(currentLine)] = "15"      #------------------------------------------------------------------------------------------------------
    sheet["D" + str(currentLine)] = strToInt(sheet["B" + str(currentLine)].value) - strToInt(sheet["C" + str(currentLine)].value)
    sheet["E" + str(currentLine)] = strToInt(sheet["D" + str(currentLine)].value) / strToInt(sheet["C" + str(currentLine)].value)
    sheet["F" + str(currentLine)] = countryDataList[0]
    sheet["G" + str(currentLine)] = countryDataList[4]
    sheet["H" + str(currentLine)] = countryDataList[2]
    sheet["I" + str(currentLine)] = strToInt(sheet["G" + str(currentLine)].value) + strToInt(sheet["H" + str(currentLine)].value)
    sheet["J" + str(currentLine)] = 100 * strToInt(sheet["I" + str(currentLine)].value) / strToInt(sheet["F" + str(currentLine)].value)
    
    fillRowWithBorder(sheet,currentLine)
    fillRowWithColour(sheet,currentLine)
    
    if (sheet["E" + str(currentLine)].value > 70):
        sheet["A" + str(currentLine)].fill = openpyxl.styles.PatternFill(fgColor="CC0000", fill_type = "solid")
    if (sheet["E" + str(currentLine)].value < -30):
        sheet["A" + str(currentLine)].fill = openpyxl.styles.PatternFill(fgColor="34A853", fill_type = "solid")
    
    if (sheet["B" + str(currentLine)].value == 0):
        fillRowWithColour(sheet,currentLine,"GREEN")
    elif ((strToInt(sheet["B" + str(currentLine)].value) > 0) and (strToInt(sheet["C" + str(currentLine)].value) == 0)):
        fillRowWithColour(sheet,currentLine,"RED")
    else:
        fillRowWithColour(sheet,currentLine)
    
    sheet["E" + str(currentLine)] = str(sheet["E" + str(currentLine)].value) + "%"
    currentLine += 1

#Now we have got most of the data, we create the tracking sheet
#To do this, we simply make a copy of the sheet from the previously made tracking file and add our values to it

pastDataSheet = book.create_sheet("Past Worldwide Graphs")
ws2 = wb2["Past Worldwide Graphs"]

for i in range (1, ws2.max_row + 1): 
    for j in range (1, ws2.max_column + 1): 
        # reading cell value from source excel file 
        c = ws2.cell(row = i, column = j) 
  
        # writing the read value to destination excel file 
        pastDataSheet.cell(row = i, column = j).value = c.value

running = True
line = 0
for i in range(7,ws2.max_row):
    if ((len(pastDataSheet.value) < 2) and running):
        running = False
        line = i

temp = datetime.today().strftime("%d")
if (temp[-1] == "1"):
    temp += "st"
elif (temp[-1] == "2"):
    temp += "nd"
elif (temp[-1] == "3"):
    temp += "rd"
else:
    temp += "th"
sheet["A" + str(line)] = temp + "of" + datetime.today().strftime("%B")

book.save(path + "worldometers_data.xlsx")
print("ERROR: INCOMPLETE SECTION DETECTED! HIT ENTER TO END SCRIPT")
input()





































