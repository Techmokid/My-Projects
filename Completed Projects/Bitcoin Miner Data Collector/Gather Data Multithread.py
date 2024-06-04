import time,Close_AutoChrome,concurrent.futures

from openpyxl import Workbook

from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

print("[Data Collection]: Loading \"NiceHash\"...")
mainURL = "https://www.nicehash.com/profitability-calculator/"
driver = webdriver.Chrome ()
driver.get(mainURL + "-bitmain-antminer-s17e-(64th)")
time.sleep(5)
print()
print()
print()

def getWebsiteAddressFromMinerName(name):
    return mainURL + name.lower().replace(" ","-")

# Press the "Got it" button for cookies
button = None
print("Locating \"GOT IT!\" cookies button")
while(True):
    try:
        button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[7]/div/div/div[2]/button")
        break
    except:
        print("[WARNING] Having trouble locating cookies element. Retrying...")
        time.sleep(2)
a = ActionChains(driver)
a.move_to_element(button).perform()
button.click()

# Get miners list
deviceSelectPath = "//*[@id=\"app\"]/div[6]/div/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[2]/div[1]/div/div[2]/div[1]"
dropMenu = driver.find_element(By.XPATH, deviceSelectPath)
a = ActionChains(driver)
a.move_to_element(dropMenu).perform()
dropMenu.click()

devicesXPath = "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[2]/div[1]/div/div[2]/div[2]/div[2]"
minerNames = []
devices = driver.find_element(By.XPATH, devicesXPath)
child_elements = devices.find_elements(By.XPATH, "./*")
for index, child in enumerate(child_elements):
    minerNames.append(str(child.text))
driver.quit()




# Now we can search through all of these to get the URLs
urls = []
AMD_CPUs = 0
AMD_GPUs = 0
NVIDIA = 0
Intel_CPUs = 0
Bitmain_Antminers = 0
for name in minerNames:
    URL_Name = name.replace("-"," ").replace("  "," ").replace(" ","-").lower()

    if URL_Name == "bitmain-antminer-s17e-(64th)":
        URL_Name = "-" + URL_Name
    urls.append(mainURL + URL_Name)

    if URL_Name[:4] == "amd-":
        if URL_Name[:8] == "amd-cpu-":
            AMD_CPUs += 1
        else:
            AMD_GPUs += 1
    elif "bitmain-antminer-" in URL_Name:
        Bitmain_Antminers += 1
    elif "intel-cpu" in URL_Name:
        Intel_CPUs += 1
    elif "nvidia" in URL_Name:
        NVIDIA += 1

def calculateResult(driver):
    while (True):
        try:
            button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button")
            break
        except:
            print("[WARNING] Having trouble clicking calculate result. Retrying...")
            time.sleep(1)

    a = ActionChains(driver)
    a.move_to_element(driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[1]")).perform()
    time.sleep(2)
    a = ActionChains(driver)
    a.move_to_element(button).perform()
    
    while True:
        try:
            button.click()
            break
        except Exception as e:
            print(e)
            time.sleep(1)

def load_url(url):
    driver = webdriver.Chrome()
    driver.get(url)

    # Wait for page load
    while(True):
        try:
            driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button")
            break
        except:
            time.sleep(1)
    time.sleep(2)

    # Check if valid URL
    xpath = "//*[@id=\"app\"]/div[6]/div/div[4]/div[1]/div/div[1]/div/div[1]/div[2]/div[1]/div/div[2]/div[1]"
    minerName = str(driver.find_element(By.XPATH, xpath).text)
    if minerName == "":
        driver.quit()
        print("[ERROR] " + url)
        raise Exception("Error lol me: " + url)

    # Press the "Got it" button for cookies
    button = None
    while(True):
        try:
            button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[7]/div/div/div[2]/button")
            break
        except:
            time.sleep(1)
    a = ActionChains(driver)
    a.move_to_element(button).perform()
    button.click()
        
    # Set power cost
    element = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[2]/div/div[2]/input")
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys("0.23")

    # Set currency
    button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[1]")
    button.click()
    
    element = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[2]/div[1]/input")
    element.send_keys("aud")
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

    # Wait for calculation
    calculateResult(driver)
    time.sleep(1)
    while (True):
        try:
            button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button")
            break
        except:
            print("[WARNING] Having trouble clicking calculate result. Retrying...")
            time.sleep(1)
    time.sleep(1)

    # Gather data
    data = []
    running = True
    attempts = 0
    while(running):
        try:
            for i in range(0,10):
                try:
                    #Here we just need to read out the data and save it into an excel file
                    dataContainerXPath = "//*[@id=\"approx-income\"]/div[" + str(i) + "]/div"
                    
                    # //*[@id="approx-income"]/div[2]/div/div[1]/div[4]/small
                    # //*[@id="approx-income"]/div[2]/div/div[2]/div[4]/small
                    # //*[@id="approx-income"]/div[2]/div/div[3]/div[4]/small
                    # //*[@id="approx-income"]/div[2]/div/div[1]/div[4]
                    
                    print("Gathering income")
                    print(dataContainerXPath + "/div[1]/div[4]")
                    time.sleep(10)
                    IncomePerDay = driver.find_element(By.XPATH, dataContainerXPath + "/div[1]/div[4]").text
                    IncomePerWeek = str(int(IncomePerDay) * 7)
                    IncomePerMonth = str(int(IncomePerDay) * 30)

                    print("Gathering costs")
                    CostsPerDay = driver.find_element(By.XPATH, dataContainerXPath + "/div[2]/div[4]").text
                    CostsPerWeek = str(int(CostsPerDay) * 7)
                    CostsPerMonth = str(int(CostsPerDay) * 30)

                    print("Gathering profit")
                    ProfitPerDay = driver.find_element(By.XPATH, dataContainerXPath + "/div[3]/div[4]").text
                    ProfitPerWeek = str(int(ProfitPerDay) * 7)
                    ProfitPerMonth = str(int(ProfitPerDay) * 30)
                    running = False

                    print("Adding to result")
                    data.append(IncomePerDay)
                    data.append(IncomePerWeek)
                    data.append(IncomePerMonth)
                    data.append(CostsPerDay)
                    data.append(CostsPerWeek)
                    data.append(CostsPerMonth)
                    data.append(ProfitPerDay)
                    data.append(ProfitPerWeek)
                    data.append(ProfitPerMonth)
                    print("Yes")
                    break
                except:
                    continue
        except Exception as e:
            print("[INFO] Attempt: " + str(attempts))
            calculateResult()
            waitUntilReady()
            time.sleep(4)
            attempts += 1

    print(data)
    driver.quit()
    time.sleep(3)
    return data

urls = urls[:12]

# Now load all URLs in parallel and collect the data
all_data = []
with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
    futures = [executor.submit(load_url, url) for url in urls]

    for future in concurrent.futures.as_completed(futures):
        try:
            result = future.result()  # Retrieve the result from the future
            all_data.append(result)   # Collect the data
        except Exception as e:
            print(f"An error occurred: {e}")

# Now you have all the data in `all_data`
print(all_data)






