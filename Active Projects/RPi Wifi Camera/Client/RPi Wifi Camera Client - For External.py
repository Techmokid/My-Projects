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
def destroyFile(filename):
    ftp.connect('192.168.1.11',1026)
    ftp.login()
    destruct_name = "SYSTEM_FILES_SET_TO_DESTRUCTION.txt"
    downloadFile("Z:/" + destruct_name,destruct_name)
    
    f = open("Z:/" + destruct_name,"a")
    f.write(filename+"\n")
    f.close()

    ftp.connect('163.47.56.221',1026)
    ftp.login()
    uploadFile("Z:/" + destruct_name,destruct_name)

prevDirectoryList = []
while(True):
    ftp.connect('192.168.1.11',1026)
    ftp.login()
    ftp.retrlines('NLST',storeNewDirectories)
    ftp.quit()
    
    #We want to filter out results we have already seen
    #for i in directoryList:
    #    if (i in prevDirectoryList):
    #        directoryList.remove(i)
    
    #Now we want to remove from the previous list if it wasn't detected this time
    #for i in prevDirectoryList:
    #    if (i not in directoryList):
    #        #print("Removing: " + i)
    #        prevDirectoryList.remove(i)
    
    for i in directoryList:
        if (i not in prevDirectoryList):
            if ((i + ".IP-Access-list") in directoryList):
                print("Downloading New Directory: " + i)
                ftp.connect('163.47.56.221',1026)
                ftp.login()
                downloadFile("Z:/New Recordings/" + i,i)
                destroyFile(i)
    
    #for i in directoryList:
    #    prevDirectoryList.append(i)
    directoryList = []
    time.sleep(30)
