import psutil
import time
import os
import shutil

excluded_drives = {'C:', 'D:', 'F:'}
newFirmwarePath = "C:/Users/Techmo/Downloads/GT4286 157-AN06-20240507"

def get_usb_drives():
    drives = [disk.device for disk in psutil.disk_partitions() if 'removable' in disk.opts]
    return set(drives)

def delete_files_in_drive(drive):
    failedFiles = []
    failedDirectories = []
    for root, dirs, files in os.walk(drive, topdown=False):
        for name in files:
            try:
                os.remove(os.path.join(root, name))
            except PermissionError as e:
                print(f"Cannot delete {os.path.join(root, name)}: {e}")
                failedFiles.append(os.path.join(root, name))
        for name in dirs:
            try:
                shutil.rmtree(os.path.join(root, name))
            except PermissionError as e:
                print(f"Cannot delete directory {os.path.join(root, name)}: {e}")
                failedDirectories.append(os.path.join(root, name))
    print(f"All accessible files deleted on {drive}")

    time.sleep(2)
    print("Attempting to wipe failed files")
    failuresDir = []
    failuresFile = []
    for i in failedFiles:
        try:
            os.remove(i)
        except PermissionError as e:
            print(f"Cannot delete {i}: {e}")
            failuresFile.append(i)
    for i in failedDirectories:
        try:
            shutil.rmtree(i)
        except PermissionError as e:
            print(f"Cannot delete {i}: {e}")
            failuresDir.append(i)

    if len(failuresFile) > 0:
        print("Please delete card contents manually")
        for i in failuresFile:
            while os.path.exists(i):
                continue
    if len(failuresDir) > 0:
        for i in failuresDir:
            while os.path.exists(i):
                continue

def copy_files_to_drive(src, dest):
    print("Copying files")

    totalIndex = len(os.listdir(src))
    index = 0
    index2 = 0
    for item in os.listdir(src):
        if (index / totalIndex > 0.25) and (index2 == 0):
            print("25%")
            index2 += 1
        if (index / totalIndex > 0.50) and (index2 == 1):
            print("50%")
            index2 += 1
        if (index / totalIndex > 0.75) and (index2 == 2):
            print("75%")
            index2 += 1
            
        s = os.path.join(src, item)
        d = os.path.join(dest, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, dirs_exist_ok=True)  # Change here to use dirs_exist_ok
        else:
            shutil.copy2(s, d)
        index += 1
    print("File copy process complete")

def main():
    print("Monitoring USB drives...")
    connected_drives = get_usb_drives()

    while True:
        current_drives = get_usb_drives()
        new_drives = current_drives - connected_drives

        for drive in new_drives:
            if drive not in excluded_drives:
                print(f"New USB drive connected: {drive}")
                delete_files_in_drive(drive)
                copy_files_to_drive(newFirmwarePath,drive)
            print()
            print()

        connected_drives = current_drives
        time.sleep(1)

if __name__ == '__main__':
    main()
