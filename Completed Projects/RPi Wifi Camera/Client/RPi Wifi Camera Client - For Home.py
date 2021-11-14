from ftplib import FTP
import time

ftp = FTP('')

print("We have connected!")

def uploadFile(filepath,filename):
 ftp.storbinary('STOR '+filename, open(filepath, 'rb'))
 ftp.quit()

def downloadFile(filepath,filename):
 localfile = open(filepath, 'wb')
 ftp.retrbinary('RETR ' + filename, localfile.write, 1024)
 ftp.quit()
 localfile.close()

directoryList = []
def storeNewDirectories(x):
    directoryList.append(x)

#uploadFile("C:/Users/aj200/Desktop/Er.png","Er.png")
#downloadFile("C:/Users/aj200/Desktop/Er2.png","Er.png")

destructionList = []
def destroyFile(IP,filename):
    try:
        ftp.connect('192.168.1.' + IP,1026)
        ftp.login()
        destruct_name = "SYSTEM_FILES_SET_TO_DESTRUCTION.txt"
        downloadFile("Z:/" + IP + destruct_name,destruct_name)
        
        f = open("Z:/" + destruct_name,"a")
        f.write(filename+"\n")
        f.close()

        ftp.connect('192.168.1.' + IP,1026)
        ftp.login()
        uploadFile("Z:/" + destruct_name,destruct_name)
    except:
        print("Error destroying file: " + filename)

index = 0
IP_Addresses = ["11","21"]
while(True):
    IP = IP_Addresses[index]
    index += 1
    if (index == len(IP_Addresses)):
        index = 0

    try:
        ftp.connect('192.168.1.' + IP,1026)
        ftp.login()
        ftp.retrlines('NLST',storeNewDirectories)
        ftp.quit()
        
        for i in directoryList:
            if ((i[:-5] + ".IP-Access-list") in directoryList):
                print("IP:" + IP + "\t\tDownloading Video File: " + i)
                ftp.connect('192.168.1.' + IP,1026)
                ftp.login()
                downloadFile("Z:/New Recordings/" + i,i)
                destroyFile(IP,i)
            if (".volt" in i):
                print("IP:" + IP + "\t\tDownloading Voltage Data: " + i)
                ftp.connect('192.168.1.' + IP,1026)
                ftp.login()
                downloadFile("Z:/New Recordings/" + i,i)
                destroyFile(IP,i)
    except:
        print("ERROR: Could not communicate with 192.168.1." + IP)
    
    directoryList = []
    time.sleep(5)
