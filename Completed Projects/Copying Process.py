import os,time,shutil

src = "F:/"
dst = "Z:/test/"

def writeError(error):
    with open('errors.txt','a+') as errorFile:
        errorFile.write(error + "\n")

if (os.path.exists('errors.txt')):
    os.remove('errors.txt')

print("Creating needed directories. This may take a few minutes...")
loops = 0
for subdir, dirs, files in os.walk(src):
    for file in dirs:
        a = (subdir + "/" + file).replace('//','/').replace('\\','/')
        test = a[3:]
        if ('/' in test):
            test = test[:test.index('/')]
        
        if (("Windows" in test) or ("$Recycle.Bin" in test)):
            asdggffgsafgagsa = 0
        else:
            filepath = (dst + subdir[3:] + "/" + file).replace('//','/').replace('\\','/')
            if (os.path.isdir(filepath) == False):
                os.makedirs(filepath)
            loops += 1
            if (loops % 1000 == 0):
                print("Watchdog returns current directory: " + (subdir + "/" + file).replace('//','/').replace('\\','/'))

print("Directories created!")
print("\nNow copying files. This is the part that usually takes the longest...")
loops = 0
for subdir, dirs, files in os.walk(src):
    for file in files:
        srcfilepath = (subdir + "/" + file).replace('//','/').replace('\\','/')
        dstfilepath = (dst + subdir[3:] + "/" + file).replace('//','/').replace('\\','/')
        try:
            if (os.path.isfile(filepath) == False):
                shutil.copy(srcfilepath,dstfilepath)
        except:
            writeError("Could not copy file: \"" + srcfilepath + "\" to location \"" + dstfilepath + "\"")
        loops += 1
        if (loops % 10 == 0):
            print("Watchdog returns current directory: " + srcfilepath)

print("Finished copying all files!")
input("Hit enter to finish")
