import psutil,os,time

# Function to close any open Chrome browsers controlled by Selenium
def close_selenium_browsers():
    for process in psutil.process_iter(['pid', 'name']):
        try:
            # Check if the process is Chrome or ChromeDriver
            if process.info['name'].lower() == 'chromedriver.exe':
                print(f"Terminating process: {process.info['name']} with PID: {process.info['pid']}")
                os.kill(process.info['pid'], 9)
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass

    time.sleep(1)
    for process in psutil.process_iter(['pid', 'name']):
        try:
            # Check if the process is Chrome or ChromeDriver
            if process.info['name'].lower() == 'chrome.exe':
                print(f"Terminating process: {process.info['name']} with PID: {process.info['pid']}")
                os.kill(process.info['pid'], 9)
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass

# Example usage
close_selenium_browsers()
