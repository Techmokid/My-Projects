import subprocess
import os
import shutil

def handle_remove_error(func, path, exc_info):
    print(f"Error removing {path}. Retrying...")
    os.chmod(path, 0o777)  # Change the permissions to writable
    try:
        func(path)  # Retry the original operation
    except Exception as e:
        print(f"Failed to remove {path}: {e}")

def decompile_apk(source_apk, dest_dir):
    if os.path.exists(dest_dir):
        print("Removing old directory...")
        shutil.rmtree(dest_dir, onerror=handle_remove_error)
        print("Removed old directory")
        print()
    
    try:
        # Construct the apktool command
        command = f'apktool d "{source_apk}" -o "{dest_dir}"'
        
        # Run the command and wait for it to complete
        print(f"Decompiling in progress: {command}")
        #process = subprocess.run(command, shell=True, check=True)
        process = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        print(f"Decompilation completed. Output saved to: {dest_dir}")

    except subprocess.CalledProcessError as e:
        print(f"Error during decompilation: {e}")

def list_internal_files(directory):
    file_paths = []
    for root, _, files in os.walk(directory):
        for file in files:
            file_paths.append(os.path.join(root, file))
    return file_paths

# Example Usage
source_apk_path = r"C:\Users\aj200\Downloads\com.candywriter.bitlife_154_apps.evozi.com.apk"
decompiled_dir = r"C:\Users\aj200\Downloads\BitLife_DECOMPILED"

# Step 1: Decompile the APK
#decompile_apk(source_apk_path, decompiled_dir)

# Step 2: List all internal files
all_files = list_internal_files(decompiled_dir)

# Print the file paths
print("Now listing all file directories. 1 directory = 1 file:")
#for file in all_files:
#    print(file)
print(all_files)
