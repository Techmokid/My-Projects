import json
import os
import platform
import socket
import subprocess
import sys
import smtplib
from email.message import EmailMessage

# Auto-install required packages if not already present
REQUIRED_MODULES = ["psutil", "cpuinfo"]

for module in REQUIRED_MODULES:
    try:
        __import__(module)
    except ImportError:
        subprocess.check_call([sys.executable, "-m", "pip", "install", module])

import psutil
import cpuinfo

def get_cpu_info():
    info = cpuinfo.get_cpu_info()
    return {
        "brand": info.get("brand_raw", "Unknown"),
        "arch": info.get("arch", "Unknown"),
        "bits": info.get("bits", "Unknown"),
        "count_logical": psutil.cpu_count(logical=True),
        "count_physical": psutil.cpu_count(logical=False),
        "max_frequency_mhz": psutil.cpu_freq().max if psutil.cpu_freq() else None,
    }

def get_ram_info():
    vm = psutil.virtual_memory()
    ram_info = {
        "total_gb": round(vm.total / (1024 ** 3), 2),
    }

    if platform.system() == "Windows":
        try:
            output = subprocess.check_output(
                ["wmic", "memorychip", "get", "Speed"], text=True)
            speeds = [int(s) for s in output.split() if s.isdigit()]
            ram_info["per_module_speed_mhz"] = speeds
        except Exception as e:
            ram_info["per_module_speed_mhz"] = str(e)

    elif platform.system() == "Linux":
        try:
            output = subprocess.check_output(
                ["sudo", "dmidecode", "-t", "memory"], text=True)
            speeds = []
            for line in output.splitlines():
                if "Speed:" in line and "Configured" not in line:
                    try:
                        speeds.append(int(line.strip().split()[1]))
                    except:
                        continue
            ram_info["per_module_speed_mhz"] = speeds
        except Exception as e:
            ram_info["per_module_speed_mhz"] = str(e)

    return ram_info

def get_disk_info():
    disks = []
    partitions = psutil.disk_partitions(all=False)
    for p in partitions:
        try:
            usage = psutil.disk_usage(p.mountpoint)
            disk = {
                "device": p.device,
                "mountpoint": p.mountpoint,
                "fstype": p.fstype,
                "total_gb": round(usage.total / (1024 ** 3), 2)
            }
            disks.append(disk)
        except:
            continue
    return disks

def get_gpu_info():
    gpus = []
    if platform.system() == "Windows":
        try:
            output = subprocess.check_output(
                ['wmic', 'path', 'win32_VideoController', 'get', 'name'], text=True)
            lines = [line.strip() for line in output.strip().split("\n") if line.strip()]
            gpus = lines[1:]  # Skip header
        except Exception as e:
            gpus = [str(e)]

    elif platform.system() == "Linux":
        try:
            output = subprocess.check_output(['lspci'], text=True)
            for line in output.splitlines():
                if "VGA" in line or "3D controller" in line:
                    gpus.append(line.strip())
        except Exception as e:
            gpus = [str(e)]

    return gpus

def get_network_info():
    interfaces = psutil.net_if_addrs()
    net_info = {}

    for iface, addrs in interfaces.items():
        net_info[iface] = {}
        for addr in addrs:
            if addr.family == socket.AF_INET:
                net_info[iface]["IPv4"] = addr.address
            elif addr.family == socket.AF_INET6:
                net_info[iface]["IPv6"] = addr.address

    return net_info

def get_system_info():
    return {
        "os": platform.system(),
        "os_version": platform.version(),
        "architecture": platform.machine(),
        "hostname": platform.node(),
        "platform": platform.platform(),
        "kernel": platform.release(),
    }

def wmic_query(prop, category):
    try:
        output = subprocess.check_output(
            ["wmic", category, "get", prop], stderr=subprocess.DEVNULL, text=True
        ).splitlines()
        values = [line.strip() for line in output if line.strip() and prop not in line]
        return values[0] if values else "Unavailable"
    except Exception:
        return "Unavailable"

def get_motherboard_info():
    return {
        "manufacturer": wmic_query("Manufacturer", "baseboard"),
        "product": wmic_query("Product", "baseboard"),
        "serial": wmic_query("SerialNumber", "baseboard")
    }

def get_bios_info():
    return {
        "vendor": wmic_query("Manufacturer", "bios"),
        "version": wmic_query("SMBIOSBIOSVersion", "bios"),
        "release_date": wmic_query("ReleaseDate", "bios")
    }

def send_email_with_attachment(to_email, subject, body, filename):
    from_email = "aj2000wa@gmail.com"
    password = "wwfm einp lhtm rnby"

    if not from_email or not password:
        print("Missing email credentials. Set EMAIL_ADDRESS and EMAIL_PASSWORD env variables.")
        return

    msg = EmailMessage()
    msg["Subject"] = subject
    msg["From"] = from_email
    msg["To"] = to_email
    msg.set_content(body)

    # Attach the file
    with open(filename, "rb") as f:
        file_data = f.read()
        msg.add_attachment(file_data, maintype="application", subtype="json", filename=os.path.basename(filename))

    try:
        # SMTP server info (Gmail example)
        with smtplib.SMTP("smtp.gmail.com", 587) as smtp:
            smtp.starttls()
            smtp.login(from_email, password)
            smtp.send_message(msg)
        print("Email sent successfully.")
    except Exception as e:
        print("Failed to send email:", e)

def main():
    hardware_info = {
        "system": get_system_info(),
        "cpu": get_cpu_info(),
        "ram": get_ram_info(),
        "disks": get_disk_info(),
        "gpu": get_gpu_info(),
        "network": get_network_info(),
        "motherboard": get_motherboard_info(),
        "bios": get_bios_info()
    }

    with open("hardware_info.json", "w") as f:
        json.dump(hardware_info, f, indent=4)

    print("Hardware information saved to hardware_info.json")
    # Send the file via email
    send_email_with_attachment(
        to_email="aj2000wa@hotmail.com",
        subject="Hardware Info Report",
        body="Attached is the automatically generated hardware_info.json file.",
        filename="hardware_info.json"
    )

if __name__ == "__main__":
    main()
