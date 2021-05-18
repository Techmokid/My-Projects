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
    element = driver.find_element_by_xpath("//input[@type='text']")
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(Keys.BACK_SPACE)
    element.send_keys(cost)

#Move to the currency field and type into that
def setCurrency(currency):
    button = driver.find_element_by_xpath("//i[@class='fa fa-caret-down']")
    button.click()
    
    element = driver.find_element_by_xpath("//input[@placeholder='search']")
    element.send_keys(currency)
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

def setDeviceName(deviceName):
    button = driver.find_element_by_xpath("html/body/div[1]/div[6]/div[1]/div[2]/div[1]/div[1]/div[1]/div[1]/div[1]/div[2]/div[1]/div[1]/div[2]/div[1]/div[1]/i[2]")
    button.click()

    element = driver.find_element_by_xpath("html/body/div[1]/div[6]/div[1]/div[2]/div[1]/div[1]/div[1]/div[1]/div[1]/div[2]/div[1]/div[1]/div[2]/div[2]/div[1]/input[1]")
    element.send_keys(deviceName)
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

def incrementDeviceID():
    xpath = "html/body/div[1]/div[6]/div[1]/div[2]/div[1]/div[1]/div[1]/div[1]/div[1]/div[2]/div[1]/div[1]/div[2]/div[1]/div[1]/i[2]"
    #xpath = "html/body/div[1]/div[6]/div[2]/div[2]/div[1]/div[1]/div[1]/div[1]/div[1]/div[2]/div[1]/div[1]/div[2]/div[1]/div[1]/i[2]"
    button = driver.find_element_by_xpath(xpath)
    a = ActionChains(driver)
    a.move_to_element(button).perform()
    button.click()

    time.sleep(1)
    element = driver.find_element_by_xpath("/html/body/div/div[6]/div/div[2]/div[1]/div/div[1]/div[1]/div[1]/div[2]/div[1]/div/div[2]/div[2]/div[1]/input")
    element.send_keys(Keys.ARROW_DOWN)
    element.send_keys(Keys.ENTER)

def calculateResult():
    xpath = "/html/body/div/div[6]/div/div[2]/div[1]/div/div[1]/div[1]/div[1]/div[4]/button"
    button = driver.find_element_by_xpath(xpath)
    a = ActionChains(driver)
    a.move_to_element(button).perform()
    button.click()

# use firefox to get page with javascript generated content
print("[Data Collection]: Loading \"NiceHash\"...")
w = WebDriverWait(driver, 8)
time.sleep(8)

button = None
while(True):
        try:
            button = driver.find_element_by_xpath("//button[@class='btn primary medium fluid']")
            break
        except:
            print("Error finding element. Retrying...")
            time.sleep(2)
a = ActionChains(driver)
a.move_to_element(button).perform()
button.click()

setPowerCost("0.26")
setCurrency("aud")
time.sleep(8)
calculateResult()
time.sleep(5)

def waitUntilReady():
    while(True):
        try:
            driver.find_element_by_xpath("//button[@class='btn primary medium fluid']")
            break
        except:
            print("Error 1")
            time.sleep(1)

dataContainerXPath = "/html/body/div/div[6]/div/div[2]/div[1]/div/div[1]/div[2]/div/div[2]/table/tbody"
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

while(True):
    incrementDeviceID()
    waitUntilReady()
    time.sleep(2)
    calculateResult()
    waitUntilReady()
    time.sleep(2)

    while(True):
        try:
            a = ActionChains(driver)
            a.move_to_element(driver.find_element_by_xpath(dataContainerXPath + "/tr[1]/td[2]/small[1]")).perform()
            
            #Here we just need to read out the data and save it into an excel file
            IncomePerDay = driver.find_element_by_xpath(dataContainerXPath + "/tr[1]/td[2]/small[1]").text
            IncomePerWeek = driver.find_element_by_xpath(dataContainerXPath + "/tr[1]/td[3]/small[1]").text
            IncomePerMonth = driver.find_element_by_xpath(dataContainerXPath + "/tr[1]/td[4]/small[1]").text
            
            CostsPerDay = driver.find_element_by_xpath(dataContainerXPath + "/tr[2]/td[2]/small[1]").text
            CostsPerWeek = driver.find_element_by_xpath(dataContainerXPath + "/tr[2]/td[3]/small[1]").text
            CostsPerMonth = driver.find_element_by_xpath(dataContainerXPath + "/tr[2]/td[4]/small[1]").text
            
            ProfitPerDay = driver.find_element_by_xpath(dataContainerXPath + "/tr[3]/td[2]/small[1]").text
            ProfitPerWeek = driver.find_element_by_xpath(dataContainerXPath + "/tr[3]/td[3]/small[1]").text
            ProfitPerMonth = driver.find_element_by_xpath(dataContainerXPath + "/tr[3]/td[4]/small[1]").text
            break
        except:
            print("Error. Trying again")

    tempData = []
    tempData.append(driver.find_element_by_xpath("//h2[@class='mb16 text-muted']").text)
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

    if (str(driver.find_element_by_xpath("//h2[@class='mb16 text-muted']").text) == "NVIDIA TITAN XP"):
        break
wb.save('incomeValues.xlsx')













































time.sleep(10)
driver.close()
