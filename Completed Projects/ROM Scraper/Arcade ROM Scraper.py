import requests,time,urllib

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

input("ready?")
for i in range(1,402):
    print("Now scouring page:",i)
    #print("Site to download from: \"https://romhustler.org/roms/index/page:" + str(i) + "\"")
    rawSiteData = splitTextToLines(requests.get("https://romhustler.org/roms/index/page:" + str(i)).text)
    scrapedSiteData = getLineOfValue(rawSiteData,"<div class=\"roms-listing w-console\"")
    rowList = getValues(getListSubstring(rawSiteData,scrapedSiteData,len(rawSiteData) - 1),"<div class=\"row")
    
    for rowSegment in rowList:
        state = ""
        for line in splitTextToLines(rowSegment):
            #Get the class type
            if ("<div class=\"row  extend\">" in line):
                state = "extended row"
            if ("<div class=\"row \">" in line):
                state = "standard row"

        #If we have the class type, then get the download link
        if (state == "extended row"):
            pass
        if (state == "standard row"):
            for line in splitTextToLines(rowSegment):
                if (("href=\"" in line) and ("/rom/" in line)):
                    startIndex = line.index("<a href=\"")+len("<a href=\"")
                    url = "https://romhustler.org" + line[startIndex : line.index("\">",startIndex)]
                    
                    #We now have the download url.
                    siteData_2 = splitTextToLines(requests.get(url).text)
                    scrapedSiteData_2 = getLineOfValue(siteData_2,"<div class=\"overview info download_list")
                    rowList_2 = getListSubstring(siteData_2,scrapedSiteData_2,len(siteData_2) - 1)

                    running_2 = True
                    for i in rowList_2:
                        if (("href=\"" in i) and running_2):
                            running_2 = False
                            url_2 = "https://romhustler.org"
                            startIndex = i.index("<a href=\"") + len("<a href=\"")
                            url_2 += i[startIndex : i.index("\"",startIndex+1)]
                            if ("/download/" in url_2):
                                #We now have the download url.
                                siteData_3 = splitTextToLines(requests.get(url_2).text)
                                print(url_2)
                                for i in siteData_3:
                                    if ("class=\"downloadLink\"" in i):
                                        print(i)
                                input()
                    
        if ((state != "") and (line != "")):
            print(rowSegment)























































