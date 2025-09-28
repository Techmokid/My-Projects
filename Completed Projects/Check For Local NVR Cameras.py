import subprocess
import sys
import socket
import ipaddress

# Function to install required libraries using pip
def install(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

# Install necessary libraries
try:
    import scapy
except ImportError:
    print("scapy not found, installing...")
    install("scapy")

from scapy.all import ARP, Ether, srp

try:
    from onvif import ONVIFCamera
except ImportError:
    print("onvif-zeep not found, installing...")
    install("onvif-zeep")

try:
    import requests
except ImportError:
    print("requests not found, installing...")
    install("requests")

# Define common ONVIF and RTSP ports
ONVIF_PORT = 80
RTSP_PORT = 554

def scan_local_network(ip_range):
    """
    Scans the local network for active devices using ARP.
    """
    print(f"Scanning the network {ip_range} for devices...")
    # Create ARP packet
    arp_request = ARP(pdst=ip_range)
    ether = Ether(dst="ff:ff:ff:ff:ff:ff")
    packet = ether / arp_request

    # Send the packet and capture responses
    result = srp(packet, timeout=2, verbose=0)[0]

    devices = []
    for sent, received in result:
        devices.append({'ip': received.psrc, 'mac': received.hwsrc})
    
    return devices

def check_rtsp_and_onvif(ip):
    """
    Checks if the given IP has both RTSP and ONVIF capabilities.
    """
    rtsp_found = False
    onvif_found = False

    # Check RTSP port
    try:
        with socket.create_connection((ip, RTSP_PORT), timeout=2):
            rtsp_found = True
    except (socket.timeout, socket.error):
        pass

    # Check ONVIF port
    try:
        with socket.create_connection((ip, ONVIF_PORT), timeout=2):
            onvif_found = True
    except (socket.timeout, socket.error):
        pass

    return rtsp_found and onvif_found

def get_ip_range(ip):
    """
    Takes an IP address (e.g., '192.168.55.222') and returns the network range (e.g., '192.168.55.0/24').
    """
    # Convert IP address to an IP network
    network = ipaddress.IPv4Network(f"{ip}/24", strict=False)
    return str(network.network_address) + "/24"

def run_command(command):
    """Run a shell command and print its output."""
    try:
        subprocess.run(command, check=True, shell=True, text=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {e}")

def update_system():
    """Update and upgrade the system."""
    print("Updating system packages...")
    run_command("sudo apt update && sudo apt full-upgrade -y")

def remove_unnecessary_packages():
    """Remove unnecessary packages."""
    print("Removing unnecessary packages...")
    run_command("sudo apt autoremove -y")

def install_docker():
    """Check if Docker is installed; if not, install it."""
    print("Checking if Docker is installed...")
    result = subprocess.run("docker --version", shell=True, text=True, capture_output=True)
    
    if result.returncode == 0:
        print("Docker is already installed.")
    else:
        print("Docker is not installed. Installing Docker...")
        run_command("curl -fsSL https://get.docker.com -o get-docker.sh")
        run_command("sudo sh get-docker.sh")
        run_command("rm get-docker.sh")  # Clean up the installer script
        run_command("sudo usermod -aG docker $USER")
        print("Docker installation complete. Please log out and log back in for changes to take effect.")

def scan_for_all_cameras(ip_range):
    devices = scan_local_network(ip_range)
    print(f"Found {len(devices)} networked devices on the local subnet")
    print("Checking all local networked devices for camera I/O streams...")
    
    for device in devices:
        ip = device['ip']
        if check_rtsp_and_onvif(ip):
            print(f"Discovered Camera: {ip}, MAC: {device['mac']}")

if __name__ == "__main__":
    update_system()
    remove_unnecessary_packages()
    install_docker()
    print("Setup is complete!\n\n\n")

    hostname = socket.gethostname()
    device_ip = socket.gethostbyname(hostname)
    device_ip = "192.168.0.222"
    print(f"My Local IP Address: {device_ip}")
    
    ip_range = get_ip_range(device_ip)
    scan_for_all_cameras(ip_range)

    setup_motioneye()






















