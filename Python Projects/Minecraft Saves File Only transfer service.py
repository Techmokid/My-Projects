import os,shutil,time,filecmp

check_If_Files_Are_The_Same = False
print("Minecraft School File Transfer Service")
print("This Program will move across all files for minecraft")
path = ""
print("\nPlease input drive letter")
drive = input()

def checkFiles(path,drivePath):
    if(filecmp.cmp(path,drivePath)):
        print("Files are already complete")
        time.sleep(2)
        quit()
    return

def user():
    print("\nPlease type your username exactly as you would when logging in")
    userName = input()
    print("\nThankyou\n\n\n")
    path = "\\\\E4020S01sv001.blue.schools.internal\\fsE4020S01-StudentProfiles$\\" + userName
    try:
        os.listdir(path)
        path = "\\\\E4020S01sv001.blue.schools.internal\\fsE4020S01-StudentProfiles$\\" + userName + "\\Application Data\\.minecraft"
        return path
    except:
        try:
            path = "C:\\Users\\" + userName
            os.listdir(path)
            path = "C:\\Users\\" + userName + "\\AppData\\Roaming\\.minecraft\\saves"
            return path
        except:
            print("Wrong username. Please enter again")
            user()

path = user()
if (check_If_Files_Are_The_Same == True):
    drivePath = drive + ":\\M.C Backup Files\\.minecraft\\saves"
    checkFiles(path,drivePath)

try:
    os.listdir(path)
    print("ERROR: File found. Process stopped to prevent file damage")
    time.sleep(1)
except:
    print("Process in progress...")

if (check_If_Files_Are_The_Same == False):
    drive = drive + ":\\M.C Backup Files\\.minecraft"
shutil.copytree(drive, path)
print("Process complete")
time.sleep(2)
quit()
