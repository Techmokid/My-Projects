import coinbase_handler as cbh
import random,time

currency_ID_1 = "BTC"
currency_ID_2 = "DASH"

#coinbaseData is a list of "pricePoint" objects
#price,date,time,easyDateTime
with open("Wallet Contents.txt","w+") as f:
    f.write("")

def getCurrencyDirection(data,timeSpan):
    first = float(data[len(data) - 1].price)
    last = float(data[len(data) - 1 - timeSpan].price)
    return (first - last) / first

while (True):
    cbh.cryptoCurrencyCode = currency_ID_1
    coinbaseData_1 = cbh.getPreviousPricesList()
    direction_1 = getCurrencyDirection(coinbaseData_1,5)
    
    cbh.cryptoCurrencyCode = currency_ID_2
    coinbaseData_2 = cbh.getPreviousPricesList()
    direction_2 = getCurrencyDirection(coinbaseData_2,5)
    
    direction = direction_1 - direction_2
    
    print(direction)
    if (direction > 0):
        pass
    else:
        pass
    break
