import requests,time,os,zipfile,urllib,re
from SymbolReplacement import *

#https://raspberrytips.com/download-retropie-roms/#Where_to_download_Retropie_ROMs
#https://raspberrytips.com/add-games-raspberry-pi/

#print("Site to download from: \"https://cvaddict.com/list.php\"")
#print("Site to download from: \"https://coolrom.com.au/roms/\"")
#print("Site to download from: \"https://www.freeroms.com/\"")

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
        if (key in i):
            running = True
        if (("<div" in i) and (running == True)):
            divs += 1
        if ((divs > 0) and (endPoint in i)):
            divs -= 1
            if (divs == 0):
                running = False
                results.append(myString)
                myString = ""
        if (divs > 0):
            myString += i + "\n"
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

def download_url(url, save_path):
    with urllib.request.urlopen(url) as dl_file:
        with open(save_path, 'wb') as out_file:
            out_file.write(dl_file.read())

def HasInternetConnection():
    try:
        urllib.request.urlopen('http://google.com') #Python 3.x
        return True
    except:
        return False

#input("ready?")

rawSiteData_1 = splitTextToLines(requests.get("https://www.freeroms.com/").text)
scrapedSiteData_1 = getLineOfValue(rawSiteData_1,"<div class=\"online-td")

temp_1 = getListSubstring(rawSiteData_1,scrapedSiteData_1,len(rawSiteData_1) - 1)
rowList_1 = getValues(temp_1,"<div class=\"online-td")

for line_1 in rowList_1:
    if ("href=\"" in line_1):
        startIndex_1 = line_1.index("<a href=\"")+len("<a href=\"")
        url_1 = "https://www.freeroms.com" + line_1[startIndex_1 : line_1.index("\">",startIndex_1)]
        
        #Next pattern
        rawSiteData_2 = splitTextToLines(requests.get(url_1, timeout=10).text)
        scrapedSiteData_2 = getLineOfValue(rawSiteData_2,"<div class=\"page\"")
        try:
            temp_2 = getListSubstring(rawSiteData_2,scrapedSiteData_2,len(rawSiteData_2) - 1)
        except:
            print("ERROR:",url_1)
            continue
        
        baseSaveDirectory = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/ROM Scraper/Scraped ROMs"
        baseSaveDirectory += line_1[startIndex_1 : line_1.index("\">",startIndex_1)].split(".")[0]
        if (os.path.exists(baseSaveDirectory) == False):
            os.mkdir(baseSaveDirectory)
        for line_2 in getListToString(temp_2,"/div")[1:]:
            #We are looking for "<div class=\"system-rom-tr\">"
            startIndex_2 = line_2.index("<a href=\"")+len("<a href=\"")
            url_2 = "https://www.freeroms.com" + line_2[startIndex_2 : line_2.index("\">",startIndex_2)]
            
            #Next pattern
            rawSiteData_3 = splitTextToLines(requests.get(url_2, timeout=10).text)
            scrapedSiteData_3 = getLineOfValue(rawSiteData_3,"<div class=\"system-rom-tr\"")
            temp_3 = getListSubstring(rawSiteData_3,scrapedSiteData_3,len(rawSiteData_3) - 1)

            for rom in getValues(temp_3,"<div class=\"system-rom-tr\">"):
                #For each rom we have access to
                title = ""
                url_3 = ""
                lines = splitTextToLines(rom)
                for line_3 in lines:
                    if ("<span itemprop=\"name\">" in line_3):
                        startIndex_3 = line_3.index("<span itemprop=\"name\">")+len("<span itemprop=\"name\">")
                        title = line_3[startIndex_3 : line_3.index("</span>",startIndex_3)]
                    if (("<a href=\"" in line_3) and (url_3 == "")):
                        startIndex_3 = line_3.index("<a href=\"")+len("<a href=\"")
                        url_3 = line_3[startIndex_3 : line_3.index("\"",startIndex_3)]
                
                
                temp_5 = baseSaveDirectory[:baseSaveDirectory.rfind("/")]
                ZIPDirectory = (temp_5[:temp_5.rfind("/")] + "/Zip Downloads/"+ title.replace(" ","_") + ".zip")
                if (os.path.exists(ZIPDirectory) == False):
                    print("Zip being created:",ZIPDirectory)
                    temp_4 = url_2.split("/")[3].split(".")[0].split("_")
                    endSegment = temp_4[len(temp_4)-1] + "/"
                    
                    startSegment = ""
                    del temp_4[-1]
                    for x in temp_4:
                        startSegment += x + "_"
                    startSegment = startSegment[:-1] + "/"
                    
                    url_3 = ("http://download.freeroms.com/" + startSegment + endSegment + title + ".zip").lower()

                    while(HasInternetConnection() == False):
                        print("No internet connection! Retrying in 5 minutes...")
                        time.sleep(60*5)
                    try:
                        download_url(url_3, ZIPDirectory)
                        with zipfile.ZipFile(ZIPDirectory, 'r') as zip_ref:
                            zip_ref.extractall(baseSaveDirectory)
                    except:
                        succeeded = False
                        for i in replaceAllOfSymbol(url_3," ",["|","","-","_"]):
                            if (succeeded == False):
                                try:
                                    download_url(i.replace("|","%20"), ZIPDirectory)
                                    with zipfile.ZipFile(ZIPDirectory, 'r') as zip_ref:
                                        zip_ref.extractall(baseSaveDirectory)
                                    succeeded = True
                                except:
                                    pass
                        if (succeeded == False):
                            print("Failed to Download:",url_3)
                            try:
                                os.remove(ZIPDirectory)
                            except:
                                pass
                else:
                    print("File already exists:",title)






















































