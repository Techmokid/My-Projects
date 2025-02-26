import psutil
import time
import shutil
import subprocess
import os

UF2_FILE_DIR = r"C:\Users\aj200\Downloads\RPI_PICO-20241129-v1.24.1.uf2"
print("UF2 File Path:", UF2_FILE_DIR)

def list_pico_devices():
    """Uses mpremote to list available devices and checks for a Pico."""
    try:
        result = subprocess.run(["mpremote", "connect", "list"], capture_output=True, text=True)
        devices = result.stdout.strip().split("\n")
        
        if devices:
            print("Detected devices:")
            for device in devices:
                print(f"- {device}")
            return True
        else:
            print("No Pico devices detected.")
            return False
    except Exception as e:
        print(f"Error listing devices: {e}")
        return False

def get_mounted_drives():
    """Returns a set of currently mounted drive letters (Windows) or mount points (Linux/Mac)."""
    return {disk.device for disk in psutil.disk_partitions()}

def monitor_new_drives():
    """Monitors and handles new drive detection and flashing."""
    print("Detecting mounted drives...")
    initial_drives = get_mounted_drives()
    print("Currently mounted drives:", initial_drives)

    while True:
        time.sleep(1)  # Check every second
        current_drives = get_mounted_drives()
        new_drives = current_drives - initial_drives  # Find newly added drives

        if new_drives:
            for drive in new_drives:
                print(f"New drive detected: {drive}")
                
                # Check if the drive corresponds to a Pico in boot mode
                #if os.path.exists(os.path.join(drive, "RPI-RP2")):
                if os.path.exists(drive):
                    print("Pico in boot mode detected. Uploading firmware...")
                    try:
                        # Copy the UF2 file to the new drive (upload the firmware)
                        shutil.copyfile(UF2_FILE_DIR, os.path.join(drive, "firmware.uf2"))
                        time.sleep(1)  # Wait for the firmware upload to complete

                        # After uploading, check if the device is now accessible via mpremote
                        if list_pico_devices():
                            print("Uploaded new firmware!")
                            print("DONE!!! DONE!!! DONE!!!\n\n\n")
                        else:
                            print("Failed to connect to the Pico after flashing.")
                    except Exception as e:
                        print(f"Error flashing Pico: {e}")
                else:
                    print("This is not a Pico in boot mode.")
        
        initial_drives = current_drives  # Update the drive list

# Run the monitor function
monitor_new_drives()
