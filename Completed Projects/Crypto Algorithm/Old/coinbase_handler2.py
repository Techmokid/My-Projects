#https://github.com/coinbase/coinbase-python
from coinbase.wallet.client import Client
from pycoinbaseapi.wallet.client import Client as TradingClient
import json,random,time,os

api_key = "6ZG1i5yjMnkdUKdD"
api_secret = "OUmaKOY9hW4MqfKCm9V6FzVY0OX30D0D"

client = ""
tradingClient = ""
cryptoCurrencyCode = ""
user = ""
accounts = ""

while(True):
    try:
        client = Client(api_key,api_secret)
        tradingClient = TradingClient(api_key,api_secret)
        cryptoCurrencyCode = client.get_primary_account().balance.currency
        user = client.get_current_user()
        accounts = [client.get_primary_account()]
        break
    except:
        print("Could not login to coinbase. Retrying...")

currencyCode = "AUD"

def getValueFromJSON(inputString,value):
    inputString = str(inputString)
    
    correctedInputString = []
    currentSentence = ""
    for x in inputString:
        if (x != '\n'):
            currentSentence += x
        else:
            correctedInputString.append(currentSentence)
            currentSentence = ""
    
    for x in correctedInputString:
        if ("\"" + value + "\"" in x):
            return stripValueFromJSONLine(x)
    return ""

def getAccount(currency):
    global client
    retrying = False
    while(True):
        try:
            rawData = client.get_accounts()
            if (retrying):
                client = Client(api_key,api_secret)
            break
        except:
            print("Error retrieving account data. Retrying...")
            retrying = True
    for i in rawData.data:
        if (str(i.balance.currency) == currency):
            return i
    return None

def stripValueFromJSONLine(x,key=False):
    running = False
    currentSentence = ""
    loops = 0
    if (key):
        loops = 1
    for i in x:
        if (running and i != '"'):
            currentSentence += i
        if (i == '"'):
            running = not running
            if (running == False):
                loops += 1
                if (loops == 2):
                    return currentSentence
                currentSentence = ""

class pricePoint():
    def __init__(self,PRICE,TIME):
        self.price = PRICE
        self.date = TIME.split("T")[0]
        self.time = TIME.split("T")[1][:-1]
        self.easyDateTime = self.date.replace("-","") + self.time.replace(":","")

def getAllCurrencies():
    return ["BTC",
            "ETH",
            "XRP",
            "LINK",
            "BCH",
            "LTC",
            "EOS",
            "XTZ",
            "XLM",
            "ATOM",
            "DASH",
            "ETC",
            "ZEC",
            "MKR",
            "OMG",
            "DAI",
            "COMP",
            "CGLD",
            "ALGO",
            "BAT",
            "ZRX",
            "KNC",
            "BAND",
            "REP",
            "NMR",
            "OXT"]

def getRandomCryptoCode():
    return str(random.choice(getAllCurrencies()))

HistoricPrices_Currency = []
HistoricPrices_Values = []

def getHistoricPrices(temp):
    if (temp not in HistoricPrices_Currency):
        HistoricPrices_Currency.append(temp)
        HistoricPrices_Values.append(client.get_historic_prices(currency_pair = temp + "-" + currencyCode,period="all"))
    
    loops = 0
    for i in HistoricPrices_Currency:
        if (temp in i):
            return (HistoricPrices_Values[loops])
        loops += 1

def getPreviousPricesList(randomCrypto=False):
    resultList = []
    rawData = None
    if (randomCrypto):
        rawData = getHistoricPrices(getRandomCryptoCode())
    else:
        rawData = getHistoricPrices(cryptoCurrencyCode)
    
    for i in rawData.prices:
        resultList.append(pricePoint(i.price,i.time))
    return resultList[::-1]

def getCurrentBuyPrice():
    return getValueFromJSON(client.get_buy_price(currency_pair = cryptoCurrencyCode + "-" + currencyCode),"amount")
def getCurrentSellPrice():
    return getValueFromJSON(client.get_sell_price(currency_pair = cryptoCurrencyCode + "-" + currencyCode),"amount")
def getConversionRate():
    return getValueFromJSON(client.get_exchange_rates(),currencyCode)
def getBaseAIData(configPath):
    return AI_Data(configPath)
def updatePrices():
    global HistoricPrices_Currency,HistoricPrices_Values,accounts,client
    
    retrying = False
    while(True):
        try:
            HistoricPrices_Currency = []
            HistoricPrices_Values = []
            accounts = [client.get_primary_account()]
    
            for i in getAllCurrencies():
                getHistoricPrices(i)
                accounts.append(getAccount(i))
            if (retrying):
                client = Client(api_key,api_secret)
            break
        except:
            print("Error retrieving account data. Retrying...")
            retrying = True
    

print("COINBASE: Populating historic crypto prices")
updatePrices()
