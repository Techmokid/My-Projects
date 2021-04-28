import os,time

src = ""
dst = "F:/SaveData"
while (True):
    while(os.path.isfile(dst + "/saveLock.loc")):
        time.sleep(1)
    f = open(dst + "/loadLock.loc",'w+')
    f.close()
    os.system()
    os.remove(dst + "/loadLock.loc")
    time.sleep(15)
