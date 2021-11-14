import os,time

src = "/home/pi/Desktop/Recordings/SYSTEM_FILES_SET_TO_DESTRUCTION.txt"

while(True):
    fileContents = []
    while(True):
        try:
            f = open(src,'r')
            fileContents = f.readlines()
            f.close()
            break
        except:
            print("Error")
            pass
    
    f = open(src,'w+')
    f.write('')
    f.close()
    
    for i in fileContents:
        #print('/home/pi/Desktop/Recordings/' + i)
        if (os.path.exists('/home/pi/Desktop/Recordings/' + i[:-1])):
            print("removed path: " + i[:-1])
            os.remove('/home/pi/Desktop/Recordings/' + i[:-1])
            os.remove('/home/pi/Desktop/Recordings/' + i[:-1] + ".IP-Access-list")
    time.sleep(5)