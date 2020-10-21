import coinbase_handler as cbh
import random,time,os

#coinbaseData is a list of "pricePoint" objects
#price,date,time,easyDateTime
def getCurrencyDirection(data,timeSpan):
    first = float(data[len(data) - 1].price)
    last = float(data[len(data) - 1 - timeSpan].price)
    return (first - last) / first

def getCurrencyID(name):
    i = cbh.client.get_primary_account()
    if (i.balance.currency == name):
        return i.id
    for i in cbh.client.get_accounts().data:
        if (i.balance.currency == name):
            return i.id
    return ""

def getCurrencyName(ID):
    i = cbh.client.get_primary_account()
    if (i.id == ID):
        return i.balance.currency
    for i in cbh.client.get_accounts().data:
        if (i.id == ID):
            return i.balance.currency
    return ""

def sendMessage(phoneNumber,body):
    command = "curl \"https://api.twilio.com/2010-04-01/Accounts/AC715653ed2adcaf4ca653470fb3ce7740/Messages.json\" -X POST --data-urlencode \"To=" + phoneNumber + "\" --data-urlencode \"From=+61488844045\" "
    command += "--data-urlencode \"Body=" + body + "\" -u AC715653ed2adcaf4ca653470fb3ce7740:510996988097dd33867c3d3f38454117"
    os.system("cmd /c \"" + command + "\"")

currentMaxTierCrypto = "BTC"
while (True):
    currentMaxCurrency = cbh.getAllCurrencies()[0]
    currentMaxValue = -1000
    for i in cbh.getAllCurrencies():
        cbh.cryptoCurrencyCode = i
        direction = getCurrencyDirection(cbh.getPreviousPricesList(),5)
        if (direction > currentMaxValue):
            currentMaxCurrency = i
            currentMaxValue = direction
    
    accountsContainingMoney = []
    i = cbh.client.get_primary_account()
    if (float(i.balance.amount) != 0):
        accountsContainingMoney.append(i.id)
    
    for i in cbh.client.get_accounts().data:
        if ((float(i.balance.amount) != 0) and (i.balance.currency != currentMaxCurrency)):
            accountsContainingMoney.append(i.id)
    
    if (len(accountsContainingMoney) > 0):
        print("\nCurrency shift detected. New best coin:",currentMaxCurrency)
        account = getCurrencyID(currentMaxCurrency)

        if (currentMaxTierCrypto != currentMaxCurrency):
            currentMaxTierCrypto = currentMaxCurrency
            msg = "Crypto value change detected. Please move all assets over to crypto ID \"" + currentMaxCurrency + "\" from the following cryptos: "
            for i in accountsContainingMoney:
                tempAccount = cbh.client.get_account(i)
                n = tempAccount.native_balance
                b = tempAccount.balance
                msg += ", $" + b.currency
            sendMessage("+61498580292",msg)
            print(" - Alerted user to send all crypto to currency ID: ",currentMaxCurrency)
            time.sleep(21600)
    cbh.updatePrices()
