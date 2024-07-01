import subprocess
import time
import requests
import platform

def scan_wifi_ubuntu():
    result = subprocess.run(['nmcli', 'dev', 'wifi'], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

def connect_to_wifi_ubuntu(ssid):
    # Disconnect any active connections
    subprocess.run(['nmcli', 'con', 'down', 'id', ssid], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    # Connect to the Wi-Fi network
    subprocess.run(['nmcli', 'dev', 'wifi', 'connect', ssid], stdout=subprocess.PIPE)

def is_connected_ubuntu(ssid):
    result = subprocess.run(['nmcli', '-t', '-f', 'active,ssid', 'dev', 'wifi'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    lines = output.strip().split('\n')
    for line in lines:
        active, network_ssid = line.split(':')
        if active == 'yes' and network_ssid == ssid:
            return True
    return False

def scan_wifi_windows():
    result = subprocess.run(['netsh', 'wlan', 'show', 'networks'], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

def connect_to_wifi_windows(ssid):
    # Create a profile XML file for the Wi-Fi network
    profile = f"""
    <WLANProfile xmlns="http://www.microsoft.com/networking/WLAN/profile/v1">
        <name>{ssid}</name>
        <SSIDConfig>
            <SSID>
                <name>{ssid}</name>
            </SSID>
        </SSIDConfig>
        <connectionType>ESS</connectionType>
        <connectionMode>auto</connectionMode>
        <MSM>
            <security>
                <authEncryption>
                    <authentication>open</authentication>
                    <encryption>none</encryption>
                </authEncryption>
            </security>
        </MSM>
    </WLANProfile>
    """
    with open(f"{ssid}.xml", "w") as file:
        file.write(profile)
    
    # Add the profile to the system
    subprocess.run(['netsh', 'wlan', 'add', 'profile', f'filename={ssid}.xml'], stdout=subprocess.PIPE)
    # Connect to the Wi-Fi network
    subprocess.run(['netsh', 'wlan', 'connect', ssid], stdout=subprocess.PIPE)

def is_connected_windows(ssid):
    result = subprocess.run(['netsh', 'wlan', 'show', 'interfaces'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    return ssid in output

def check_internet_connectivity():
    return True

def get_redirect_url():
    try:
        response = requests.get("http://www.google.com", allow_redirects=False, timeout=5)
        if response.status_code == 302:
            return response.headers["Location"]
    except requests.ConnectionError:
        pass
    return None

# Login credentials
payload = {
    'username': '6992@jeg.systems',  # replace with your actual username
    'password': 'ocean-desert-ocean-tree'   # replace with your actual password
}

def login_to_capture_portal(login_url):
    response = requests.post(login_url, data=payload)
    if response.status_code == 200:
        print("Login successful")
    else:
        print(f"Login failed with status code: {response.status_code}")
        print(response.text)

# Main script
ssid_to_connect = "Jeg-Team"
os_type = platform.system()

while True:
    if os_type == "Linux":
        print("Scanning for Wi-Fi networks (Ubuntu)...")
        networks = scan_wifi_ubuntu()
        if ssid_to_connect in networks:
            print(f"Found '{ssid_to_connect}' network. Connecting...")
            connect_to_wifi_ubuntu(ssid_to_connect)
            
            # Wait for the connection to establish
            time.sleep(15)
            
            if is_connected_ubuntu(ssid_to_connect):
                print(f"Connected to '{ssid_to_connect}'. Checking internet connectivity...")
                if check_internet_connectivity():
                    print("Internet connection established. Detecting captive portal...")
                    login_url = get_redirect_url()
                    if login_url:
                        print(f"Logging in to capture portal at {login_url}...")
                        login_to_capture_portal(login_url)
                        break
                    else:
                        print("Could not detect captive portal URL. Retrying...")
                else:
                    print("No internet connectivity. Retrying...")
            else:
                print(f"Failed to connect to '{ssid_to_connect}'. Retrying...")
        else:
            print(f"'{ssid_to_connect}' network not found. Retrying...")

    elif os_type == "Windows":
        print("Scanning for Wi-Fi networks (Windows)...")
        networks = scan_wifi_windows()
        if ssid_to_connect in networks:
            print(f"Found '{ssid_to_connect}' network. Connecting...")
            connect_to_wifi_windows(ssid_to_connect)
            
            # Wait for the connection to establish
            time.sleep(15)
            
            if is_connected_windows(ssid_to_connect):
                print(f"Connected to '{ssid_to_connect}'. Checking internet connectivity...")
                if check_internet_connectivity():
                    print("Internet connection established. Detecting captive portal...")
                    login_url = get_redirect_url()
                    if login_url:
                        print(f"Logging in to capture portal at {login_url}...")
                        login_to_capture_portal(login_url)
                        break
                    else:
                        print("Could not detect captive portal URL. Retrying...")
                else:
                    print("No internet connectivity. Retrying...")
            else:
                print(f"Failed to connect to '{ssid_to_connect}'. Retrying...")
        else:
            print(f"'{ssid_to_connect}' network not found. Retrying...")

    # Wait before scanning again
    time.sleep(10)
