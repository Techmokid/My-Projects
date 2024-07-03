import os
import subprocess
import sys

path = "systemInfo/"

def upgrade_pip():
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade", "pip"])
    except subprocess.CalledProcessError:
        print("Error upgrading pip")

    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade", "setuptools", "wheel"])
    except subprocess.CalledProcessError:
        print("Error upgrading setuptools")

print("Upgrading pip")
upgrade_pip()
print("Pip upgraded")

print("Updating and checking install of required libraries")
os.system(f"{sys.executable} -m pip install psutil GPUtil pandas xlrd openpyxl py-cpuinfo platform")
import re
import cpuinfo
import psutil
import GPUtil
import pandas as pd
import platform

print("Checking path")
if not os.path.exists(path):
    os.makedirs(path)

print()
print()
print()
print()
print()

def get_ram_details():
    if sys.platform.startswith('linux'):
        try:
            result = subprocess.run(['sudo', 'dmidecode', '-t', 'memory'], capture_output=True, text=True)
            return result.stdout if result.returncode == 0 else "Failed to get RAM details"
        except Exception as e:
            return str(e)
    else:
        return "RAM details retrieval is not supported on Windows."

def find_next_free_number(directory):
    pattern = re.compile(r'^(\d+)\.xlsx$')
    used_numbers = []
    
    for filename in os.listdir(directory):
        match = pattern.match(filename)
        if match:
            used_numbers.append(int(match.group(1)))
    
    if not used_numbers:
        return 1
    
    used_numbers.sort()
    for i in range(1, used_numbers[-1] + 2):
        if i not in used_numbers:
            return i

def gather_info():
    cpu_raw_info = cpuinfo.get_cpu_info()
    cpu_info = {
        "Physical cores": psutil.cpu_count(logical=False),
        "Total cores": psutil.cpu_count(logical=True),
        "Max Frequency (GHz)": psutil.cpu_freq().max / 1000,
        "Current Frequency (GHz)": psutil.cpu_freq().current / 1000,
        "Total CPU Usage (%)": psutil.cpu_percent(interval=1),
        "CPU Brand": cpu_raw_info['brand_raw'],
        "Arch": cpu_raw_info['arch'],
        "Bits": cpu_raw_info['bits'],
        "Count": cpu_raw_info['count']
    }

    svmem = psutil.virtual_memory()
    mem_info = {
        "Total (GB)": svmem.total / 1024 / 1024 / 1024,
        "Available (GB)": svmem.available / 1024 / 1024 / 1024,
        "Used (GB)": svmem.used / 1024 / 1024 / 1024,
        "Percentage (%)": svmem.percent
    }

    gpu_info = []
    gpus = GPUtil.getGPUs()
    for gpu in gpus:
        gpu_info.append({
            "GPU ID": gpu.id,
            "GPU Name": gpu.name,
            "Load (%)": gpu.load,
            "Free Memory (GB)": gpu.memoryFree / 1024,
            "Used Memory (GB)": gpu.memoryUsed / 1024,
            "Total Memory (GB)": gpu.memoryTotal / 1024,
            "Temperature (C)": gpu.temperature
        })

    os_info = {
        "OS": platform.system(),
        "Release": platform.release(),
        "Version": platform.version(),
        "Architecture": platform.machine()
    }
    
    df_cpu = pd.DataFrame([cpu_info])
    df_mem = pd.DataFrame([mem_info])
    df_gpu = pd.DataFrame(gpu_info)
    df_os = pd.DataFrame([os_info])
    
    with pd.ExcelWriter(os.path.join(path, f"{find_next_free_number(path)}.xlsx")) as writer:
        df_cpu.to_excel(writer, sheet_name='CPU Info')
        df_mem.to_excel(writer, sheet_name='Memory Info')
        df_gpu.to_excel(writer, sheet_name='GPU Info')
        df_os.to_excel(writer, sheet_name='OS Info')

print("Gathering info")
gather_info()
print("Gather successful")

def shutdown_system(doShutdown):
    if not doShutdown:
        print("Shutdown disabled")
        return
    
    if sys.platform.startswith('linux'):
        try:
            subprocess.run(["shutdown", "-h", "now"], check=True)
        except:
            try:
                os.system("shutdown -h now")
            except:
                print("Could not shut down")
    elif sys.platform.startswith('win'):
        try:
            subprocess.run(["shutdown", "/s", "/t", "0"], check=True)
            return
        except:
            try:
                os.system("shutdown /s /t 0")
                return
            except:
                print("Could not shut down")

print("Shutting down system")
shutdown_system(False)
