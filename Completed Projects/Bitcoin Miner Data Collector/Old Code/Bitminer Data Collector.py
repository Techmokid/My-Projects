#https://www.selenium.dev/selenium/docs/api/java/org/openqa/selenium/Keys.html#TAB
#https://www.geeksforgeeks.org/interacting-with-webpage-selenium-python/
#https://www.tutorialspoint.com/how-to-navigate-back-to-current-page-from-frame-in-selenium-webdriver

import time
from openpyxl import Workbook
from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
driver = webdriver.Chrome ()
driver.get("https://www.nicehash.com/profitability-calculator/-bitmain-antminer-s17e-(64th)")

data = []

def getWebsiteAddressFromMinerName(name):
    return "https://www.nicehash.com/profitability-calculator/" + name.lower().replace(" ","-")

#Type into the elec costs field
def setPowerCost(cost):
    element = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[2]/div/div[2]/input")
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(cost)

#Move to the currency field and type into that
def setCurrency(currency):
    button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[1]")
    button.click()
    
    element = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[2]/div[1]/input")
    element.send_keys(currency)
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

def setDeviceName(deviceName):
    button = driver.find_element(By.XPATH, "html/body/div[1]/div[6]/div[1]/div[2]/div[1]/div[1]/div[1]/div[1]/div[1]/div[2]/div[1]/div[1]/div[2]/div[1]/div[1]/i[2]")
    button.click()

    element = driver.find_element(By.XPATH, "html/body/div[1]/div[6]/div[1]/div[2]/div[1]/div[1]/div[1]/div[1]/div[1]/div[2]/div[1]/div[1]/div[2]/div[2]/div[1]/input[1]")
    element.send_keys(deviceName)
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

def incrementDeviceID():
    xpath = "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div/div[1]/div[2]/div[1]/div/div[2]"
    while(True):
        try:
            button = driver.find_element(By.XPATH, xpath)
            a = ActionChains(driver)
            a.move_to_element(button).perform()
            button.click()
            break
        except:
            try:
                button = driver.find_element(By.XPATH, xpath)
                a = ActionChains(driver)
                a.move_to_element(driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[1]")).perform()
                button.click()
                break
            except:
                print("[WARNING] Having trouble clicking device increment. Retrying...")
                time.sleep(1)
                pass

    time.sleep(1)
    element = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div/div[1]/div[2]/div[1]/div/div[2]/div[2]/div[1]/input")
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

def scrapeData():
    xpath = "/html/body/div/div[6]/div/div[2]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button"
    button = driver.find_element(By.XPATH, xpath)
    a = ActionChains(driver)
    a.move_to_element(button).perform()
    button.click()

def waitUntilReady():
    while(True):
        try:
            driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button")
            break
        except:
            print("[INFO] Awaiting button operation...")
            time.sleep(1)

def calculateResult():
    while (True):
        try:
            button = driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button")
            break
        except:
            print("[WARNING] Having trouble clicking calculate result. Retrying...")
            time.sleep(1)

    a = ActionChains(driver)
    a.move_to_element(driver.find_element(By.XPATH, "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div[1]/div[1]/div[1]/div[1]/div/div[2]/div[1]")).perform()

    while True:
        try:
            button.click()
            break
        except Exception as e:
            print(e)
            time.sleep(1)








# use firefox to get page with javascript generated content
print("[Data Collection]: Loading \"NiceHash\"...")
time.sleep(5)

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

# Find the currency
print("Setting power cost")
setPowerCost("0.27")

print("Setting currency")
setCurrency("aud")
time.sleep(1)

wb = Workbook()
ws1 = wb.active
previousAddress = ""

tempData = []
tempData.append("Name Of Miner")
tempData.append("Income Per Day")
tempData.append("Income Per Week")
tempData.append("Income Per Month")
tempData.append("Costs Per Day")
tempData.append("Costs Per Week")
tempData.append("Costs Per Month")
tempData.append("Profit Per Day")
tempData.append("Profit Per Week")
tempData.append("Profit Per Month")
ws1.append(tempData)

calculateResult()

print("Data scraping started")
first = True
while(True):
    if first:
        first = False
    else:
        incrementDeviceID()
    
    waitUntilReady()
    time.sleep(1)
    #print("\nGathering data...")
    calculateResult()
    waitUntilReady()
    time.sleep(4)

    running = True
    attempts = 0
    while(running):
        try:
            for i in range(0,10):
                try:
                    #Here we just need to read out the data and save it into an excel file
                    #                     //*[@id=\"approx-income\"]/div[3]/table/tbody
                    dataContainerXPath = "//*[@id=\"approx-income\"]/div[" + str(i) + "]/table/tbody"
                    IncomePerDay = driver.find_element(By.XPATH, dataContainerXPath + "/tr[1]/td[2]").text
                    IncomePerWeek = driver.find_element(By.XPATH, dataContainerXPath + "/tr[1]/td[3]").text
                    IncomePerMonth = driver.find_element(By.XPATH, dataContainerXPath + "/tr[1]/td[4]").text
                    
                    CostsPerDay = driver.find_element(By.XPATH, dataContainerXPath + "/tr[2]/td[2]").text
                    CostsPerWeek = driver.find_element(By.XPATH, dataContainerXPath + "/tr[2]/td[3]").text
                    CostsPerMonth = driver.find_element(By.XPATH, dataContainerXPath + "/tr[2]/td[4]").text
                    
                    ProfitPerDay = driver.find_element(By.XPATH, dataContainerXPath + "/tr[3]/td[2]").text
                    ProfitPerWeek = driver.find_element(By.XPATH, dataContainerXPath + "/tr[3]/td[3]").text
                    ProfitPerMonth = driver.find_element(By.XPATH, dataContainerXPath + "/tr[3]/td[4]").text
                    running = False
                    break
                except:
                    continue
        except Exception as e:
            print("[INFO] Attempt: " + str(attempts))
            calculateResult()
            waitUntilReady()
            time.sleep(4)
            attempts += 1
            
    
    minerName = "//*[@id=\"app\"]/div[6]/div[2]/div[4]/div[1]/div/div[1]/div/div[1]/div[2]/div[1]/div/div[2]/div[1]/span"
    minerName = driver.find_element(By.XPATH, minerName).text
    print("Data gathered: " + str(minerName))
    
    tempData = []
    tempData.append(str(minerName))
    tempData.append(IncomePerDay)
    tempData.append(IncomePerWeek)
    tempData.append(IncomePerMonth)
    tempData.append(CostsPerDay)
    tempData.append(CostsPerWeek)
    tempData.append(CostsPerMonth)
    tempData.append(ProfitPerDay)
    tempData.append(ProfitPerWeek)
    tempData.append(ProfitPerMonth)
    ws1.append(tempData)

    if (str(minerName) == "iPollo V1 Mini SE Plus"):
        break

print("Saving Excel document...")
wb.save('incomeValues.xlsx')
driver.close()

print("Completed task successfully!")
print()
print()
print()
print("Feel free to close this window now")
while(True):
    continue
