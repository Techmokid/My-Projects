#https://github.com/coinbase/coinbase-python
from coinbase.wallet.client import Client
import json,time

cryptoCurrencyCode = "BTC"
currencyCode = "AUD"

#Phase 1 - Connection to coinbase
print("PHASE 1: Connecting to coinbase...")
client = Client("6ZG1i5yjMnkdUKdD","OUmaKOY9hW4MqfKCm9V6FzVY0OX30D0D")
user = client.get_current_user()

print("PHASE 1: Collecting account data...")
accounts = client.get_primary_account()


print("PHASE 1: Connected!\n\n")

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

def getAllCurrencies():
    result = []
    for i in client.get_currencies().data:
        result.append(i.id)
    return result

def getRandomCurrencyCode():
    return random.choice(getAllCurrencies())

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

#Phase 2 - Data collection
print("PHASE 2: Current Conversion Rate - $" + getValueFromJSON(client.get_exchange_rates(),currencyCode) + " " + currencyCode)
print("PHASE 2: Buy Price               - $" + getValueFromJSON(client.get_buy_price(currency_pair = cryptoCurrencyCode + "-" + currencyCode),"amount"))
print("PHASE 2: Sell Price              - $" + getValueFromJSON(client.get_buy_price(currency_pair = cryptoCurrencyCode + "-" + currencyCode),"amount"))
print("PHASE 2: Server Date             - " + getValueFromJSON(client.get_time(),"iso").split("T")[0])
print("PHASE 2: Server Time             - " + getValueFromJSON(client.get_time(),"iso").split("T")[1][:-1])

#print(client.get_historic_prices(currency_pair = cryptoCurrencyCode + "-" + currencyCode,period="all"))
print(getAllCurrencies())
