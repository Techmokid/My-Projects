import subprocess
import time
import sys
from selenium import webdriver
from selenium.webdriver.firefox.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
import time
import urllib.request

SSID = "Jeg-Team"

LOGIN_URL = (
    "https://clearpass.jeg.systems/guest/Jeg-Team.php?"
    "cmd=login&mac=e8%3A2a%3A44%3A82%3Ac1%3Abb&essid=Jeg-Team"
    "&ip=10.10.1.216&apname=449%20MAIN"
    "&apmac=28%3Ade%3A65%3Adc%3A6b%3A57"
    "&vcname=Jaycar%20Midland"
    "&switchip=captiveportal-login.jeg.systems"
    "&url=http%3A%2F%2Fwww.msftconnecttest.com%2Fredirect"
    "&_browser=1"
)

POWERSHELL_SCRIPT = r"""
Add-Type -AssemblyName System.Runtime.WindowsRuntime

$asTaskGeneric = ([System.WindowsRuntimeSystemExtensions].GetMethods() |
    Where-Object {
        $_.Name -eq 'AsTask' -and
        $_.GetParameters().Count -eq 1 -and
        $_.GetParameters()[0].ParameterType.Name -eq 'IAsyncOperation`1'
    })[0]

function Await($WinRtTask, $ResultType) {
    $asTask = $asTaskGeneric.MakeGenericMethod($ResultType)
    $netTask = $asTask.Invoke($null, @($WinRtTask))

    # Wait up to 10 seconds instead of forever
    if (-not $netTask.Wait(10000)) {
        throw "Timed out waiting for Windows Mobile Hotspot API."
    }

    return $netTask.Result
}

$connectionProfile = [Windows.Networking.Connectivity.NetworkInformation,Windows.Networking.Connectivity,ContentType=WindowsRuntime]::GetInternetConnectionProfile()

if ($null -eq $connectionProfile) {
    Write-Error "No active internet connection profile found."
    exit 1
}

$tetheringManager = [Windows.Networking.NetworkOperators.NetworkOperatorTetheringManager,Windows.Networking.NetworkOperators,ContentType=WindowsRuntime]::CreateFromConnectionProfile($connectionProfile)

$currentState = $tetheringManager.TetheringOperationalState

Write-Output "Current hotspot state: $currentState"

if ($currentState -eq "On") {
    Write-Output "Mobile hotspot is already on. Nothing to do."
    exit 0
}

if ($currentState -eq "InTransition") {
    Write-Error "Mobile hotspot is currently transitioning. Try again in a few seconds."
    exit 2
}

$result = Await ($tetheringManager.StartTetheringAsync()) ([Windows.Networking.NetworkOperators.NetworkOperatorTetheringOperationResult])

Write-Output "Mobile hotspot result: $($result.Status)"

if ($result.Status -ne "Success") {
    exit 3
}
"""

def run_cmd(command):
    """
    Runs a Windows command and returns stdout as text.
    """
    try:
        result = subprocess.run(
            command,
            capture_output=True,
            text=True,
            shell=True,
            check=False
        )
        return result.stdout.strip(), result.stderr.strip(), result.returncode
    except Exception as e:
        return "", str(e), 1


def get_current_wifi_ssid():
    """
    Returns the currently connected Wi-Fi SSID, or None if not connected.
    """
    stdout, stderr, code = run_cmd("netsh wlan show interfaces")

    if code != 0:
        print(f"Failed to check Wi-Fi interface: {stderr}")
        return None

    for line in stdout.splitlines():
        line = line.strip()

        # Avoid matching BSSID
        if line.startswith("SSID") and not line.startswith("BSSID"):
            parts = line.split(":", 1)
            if len(parts) == 2:
                return parts[1].strip()

    return None


def connect_to_wifi(ssid):
    """
    Connects to a Wi-Fi network using netsh.

    Note:
    This assumes Windows already has a profile for the network,
    or that the open network can be connected to directly.
    """
    print(f"Connecting to Wi-Fi network: {ssid}")

    command = f'netsh wlan connect name="{ssid}" ssid="{ssid}"'
    stdout, stderr, code = run_cmd(command)

    if code != 0:
        print("Wi-Fi connection command failed.")
        print(stderr or stdout)
        return False

    # Give Windows time to associate
    for _ in range(15):
        time.sleep(1)
        current_ssid = get_current_wifi_ssid()

        if current_ssid == ssid:
            print(f"Connected to {ssid}")
            return True

        print(f"Waiting for Wi-Fi connection... currently on: {current_ssid}")

    print(f"Timed out trying to connect to {ssid}")
    return False

def force_type(driver, wait, css_selector, text):
    element = wait.until(
        EC.presence_of_element_located((By.CSS_SELECTOR, css_selector))
    )

    # Force the element into view
    driver.execute_script(
        "arguments[0].scrollIntoView({block: 'center', inline: 'nearest'});",
        element
    )

    time.sleep(0.3)

    # Re-fetch it after scrolling in case the page layout changed
    element = wait.until(
        EC.element_to_be_clickable((By.CSS_SELECTOR, css_selector))
    )

    try:
        element.click()
        element.clear()
        element.send_keys(text)
    except Exception:
        # Fallback: JavaScript-set the value and fire input/change events
        driver.execute_script(
            """
            arguments[0].focus();
            arguments[0].value = arguments[1];
            arguments[0].dispatchEvent(new Event('input', { bubbles: true }));
            arguments[0].dispatchEvent(new Event('change', { bubbles: true }));
            """,
            element,
            text
        )

    return element

def force_click(driver, wait, css_selector):
    element = wait.until(
        EC.presence_of_element_located((By.CSS_SELECTOR, css_selector))
    )

    driver.execute_script(
        "arguments[0].scrollIntoView({block: 'center', inline: 'nearest'});",
        element
    )

    time.sleep(0.3)

    element = wait.until(
        EC.element_to_be_clickable((By.CSS_SELECTOR, css_selector))
    )

    try:
        element.click()
    except Exception:
        driver.execute_script("arguments[0].click();", element)

    return element

def open_login_portal_firefox(url):
    print("Opening Firefox with Selenium...")

    options = Options()
    options.add_argument("--headless")
    driver = webdriver.Firefox(options=options)
    wait = WebDriverWait(driver, 20)

    driver.get(url)

    print(" - Typing Username")
    force_type(
        driver,
        wait,
        "input#ID_form574746f1_weblogin_user",
        "6992@jeg.systems"
    )

    print(" - Typing Password")
    force_type(
        driver,
        wait,
        "input#ID_form574746f1_weblogin_password",
        "ocean-desert-ocean-tree"
    )

    print(" - Accepting Terms")
    force_click(
        driver,
        wait,
        "input#ID_form574746f1_weblogin_visitor_accept_terms"
    )

    print(" - Submitting Form")
    force_click(
        driver,
        wait,
        "input#ID_form574746f1_weblogin_submit"
    )

    print(" - Form Submitted")
    print(" - Waiting for internet connection...")
    for _ in range(30):
        if internet_is_working():
            print(" - Internet connection confirmed")
            driver.quit()
            return None

        print(" - Still waiting for internet...")
        time.sleep(1)

    print(" - Internet connection was not confirmed")
    return driver

def internet_is_working(test_url="https://www.google.com", timeout=5):
    """
    Returns True if we can successfully reach google.com.
    """
    try:
        urllib.request.urlopen(test_url, timeout=timeout)
        return True
    except Exception:
        return False


def enable_hotspot():
    try:
        result = subprocess.run(
            [
                "powershell",
                "-NoProfile",
                "-ExecutionPolicy",
                "Bypass",
                "-Command",
                POWERSHELL_SCRIPT,
            ],
            capture_output=True,
            text=True,
            timeout=15,
            check=False,
        )

        if result.stdout:
            print(result.stdout.strip())

        if result.stderr:
            print(result.stderr.strip(), file=sys.stderr)

        if result.returncode == 0:
            return True

        print(f"Failed to enable hotspot. Exit code: {result.returncode}")
        return False

    except subprocess.TimeoutExpired:
        print("PowerShell timed out. Windows hotspot API probably got stuck.")
        return False

    except FileNotFoundError:
        print("PowerShell was not found. This script is intended for Windows.")
        return False

def main():
    current_ssid = get_current_wifi_ssid()

    print(f"Current Wi-Fi network: {current_ssid}")

    if current_ssid != SSID:
        connected = connect_to_wifi(SSID)

        if not connected:
            print(f"Could not connect to {SSID}. Exiting.")
            sys.exit(1)
    else:
        print(f"Already connected to {SSID}")

    driver = open_login_portal_firefox(LOGIN_URL)

    print("Starting Hotspot Bridge...")
    enable_hotspot()

    # Keep the script alive so Firefox does not immediately close.
    input("Press Enter to close and exit...")
    if (driver != None):
        driver.quit()


if __name__ == "__main__":
    main()
