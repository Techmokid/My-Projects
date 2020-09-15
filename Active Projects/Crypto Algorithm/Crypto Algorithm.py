import coinbase_handler as cbh
import random,time

#coinbaseData is a list of "pricePoint" objects
#price,date,time,easyDateTime
with open("Wallet Contents.txt","w+") as f:
    f.write("")

for currency in cbh.getAllCurrencies():
    cbh.cryptoCurrencyCode = currency
    coinbaseData = cbh.getPreviousPricesList(False)
    
