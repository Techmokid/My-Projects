#https://github.com/coinbase/coinbase-python
from coinbase.wallet.client import Client
import json,random,time,os

cryptoCurrencyCode = "BTC"
currencyCode = "AUD"
client = Client("6ZG1i5yjMnkdUKdD","OUmaKOY9hW4MqfKCm9V6FzVY0OX30D0D")

user = client.get_current_user()
accounts = client.get_primary_account()

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

class AI_Data():
    def __init__(self,configPath):
        self.population = self.getValue(configPath,"pop_size")
        self.inputs_count = self.getValue(configPath,"num_inputs")
        self.outputs_count = self.getValue(configPath,"num_outputs")
        self.hidden_count = self.getValue(configPath,"num_hidden")
    def getValue(self,path,key):
        f = open(path)
        for i in f.readlines():
            if (key in i):
                return int(i.replace(" ","").replace("\t","").replace("\n","").split('=')[1])

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

print("COINBASE: Populating historic crypto prices")
for i in getAllCurrencies():
    getHistoricPrices(i)
