import subprocess
import platform
import time
import os
from selenium import webdriver
from selenium.webdriver.firefox.service import Service as FirefoxService
from webdriver_manager.firefox import GeckoDriverManager
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.service import Service as FirefoxService

NETWORK_USERNAME = "6992@jeg.systems"
NETWORK_PASSWORD = "ocean-desert-ocean-tree"

def check_current_connection():
    os_type = platform.system().lower()

    if 'windows' in os_type:
        check_command = 'netsh wlan show interfaces'
    elif 'linux' in os_type:
        check_command = 'nmcli -t -f active,ssid dev wifi | egrep \'^yes\''
    else:
        raise Exception("Unsupported operating system")

    result = subprocess.run(check_command, shell=True, capture_output=True, text=True)
    return result.stdout

def disconnect_current_connection():
    os_type = platform.system().lower()

    if 'windows' in os_type:
        disconnect_command = 'netsh wlan disconnect'
    elif 'linux' in os_type:
        disconnect_command = 'nmcli con down id $(nmcli -t -f active,ssid dev wifi | egrep \'^yes\' | cut -d":" -f2)'
    else:
        raise Exception("Unsupported operating system")

    result = subprocess.run(disconnect_command, shell=True, capture_output=True, text=True)
    return result.returncode == 0

def scan_and_connect(network_name):
    os_type = platform.system().lower()
    attempts = 0
    
    while attempts < 5:
        current_connection = check_current_connection()
        if current_connection:
            if network_name in current_connection:
                print(f"Already connected to {network_name}")
                return True
            else:
                print(f"Currently connected to a different network. Disconnecting...")
                if not disconnect_current_connection():
                    print(f"Failed to disconnect from the current network")
                    return False
                
        if 'windows' in os_type:
            scan_command = 'netsh wlan show networks'
            connect_command = f'netsh wlan connect name={network_name}'
        elif 'linux' in os_type:
            scan_command = 'nmcli dev wifi list'
            connect_command = f'nmcli dev wifi connect "{network_name}"'
        else:
            raise Exception("Unsupported operating system")

        # Scan for networks
        result = subprocess.run(scan_command, shell=True, capture_output=True, text=True)
        if network_name in result.stdout:
            print(f"Network {network_name} found. Connecting...")
            
            # Connect to the network
            result = subprocess.run(connect_command, shell=True, capture_output=True, text=True)
            if result.returncode == 0:
                print(f"Connected to {network_name}")
                time.sleep(5)  # Wait a few seconds to ensure connection is established
            else:
                print(f"Failed to connect to {network_name}")
                print(result.stdout)
                print(result.stderr)
                return False
        else:
            print(f"Network {network_name} not found")
            attempts += 1
            time.sleep(3)
            continue
        return True
    return False

def navigate_to_capture_portal(url):
    options = webdriver.FirefoxOptions()
    #options.add_argument('--headless')  # Run headless browser

    #driver = webdriver.Firefox(executable_path='geckodriver.exe', options=options)
    #driver = webdriver.Firefox(service=FirefoxService(GeckoDriverManager().install()), options=options)
    service = FirefoxService(executable_path=r'C:\Users\Techmo\Documents\GitHub\My-Projects\Active Projects\Work network login\geckodriver.exe')

    driver = webdriver.Firefox(service=service, options=options)
    driver.get(url)
    print("Loading webpage")
    time.sleep(5)  # Wait for possible redirects
    
    try:
        print("Webpage loaded. Logging in...")
        username_field = driver.find_element(By.XPATH, "/html/body/div[2]/div[2]/div/div/form/div/div[15]/div[2]/input")
        password_field = driver.find_element(By.XPATH, "/html/body/div[2]/div[2]/div/div/form/div/div[16]/div[2]/input")
        username_field.send_keys(NETWORK_USERNAME)
        password_field.send_keys(NETWORK_PASSWORD)
        login_button = driver.find_element(By.ID, "login_button")
        login_button.click()

        print(f"Navigated to {driver.current_url}")
        return driver.current_url

    except Exception as e:
        print(f"Error navigating to capture portal: {e}")
        return None

    finally:
        driver.quit()

network_name = "Jeg-Team"

if scan_and_connect(network_name):
    capture_portal_url = "https://clearpass.jeg.systems/guest/Jeg-Team.php"
    final_url = navigate_to_capture_portal(capture_portal_url)
    if final_url:
        print(f"Final URL after navigation: {final_url}")
    else:
        print("Unable to navigate to the capture portal or handle the login.")
