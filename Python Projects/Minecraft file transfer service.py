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
            path = "C:\\Users\\" + userName + "\\AppData\\Roaming\\.minecraft"
            return path
        except:
            print("Wrong username. Please enter again")
            user()

path = user()
if (check_If_Files_Are_The_Same == True):
    drivePath = drive + ":\\M.C Backup Files\\.minecraft"
    checkFiles(path,drivePath)

try:
    os.listdir(path)
    print("ERROR: File found. Process stopped to prevent unnecessary file modifications")
    time.sleep(1)
    try:
        print("Attempting to delete file...")
        shutil.rmtree(path,ignore_errors=False,onerror=None)
        print("File deletion successful!")
        print("Now moving files...")
        print("Process in progress...")
    except:
        print("ERROR: Could not delete file. This program will now end")
        time.sleep(2)
        quit()
except:
    print("Passing Directory Copy Command to Shutil")
    print("Process in progress...")

if (check_If_Files_Are_The_Same == False):
    drive = drive + ":\\M.C Backup Files\\.minecraft"
shutil.copytree(drive, path)
print("Copy Process complete!\n\n\nYou can now play Minecraft.\nUnless told otherwise, please set your Minecraft Version to 1.11.2 or lower")
print("The reason for this is because Minecraft versions above 1.11.2 have not yet been downloaded into the copy directory")
time.sleep(2)
quit()
