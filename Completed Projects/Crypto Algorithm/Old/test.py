import coinbase_handler2 as cbh
import random,time,requests

def getCurrencyID(name):
    i = cbh.client.get_primary_account()
    if (i.balance.currency == name):
        return i.id
    for i in cbh.client.get_accounts().data:
        if (i.balance.currency == name):
            return i.id
    return ""

class CoinbaseWalletAuth():
    def __init__(self, api_key, secret_key):
        self.api_key = api_key
        self.secret_key = secret_key

    def __call__(self, request):
        timestamp = str(int(time.time()))
        message = timestamp + request.method + request.path_url + (request.body or b'').decode()
        signature = hmac.new(bytes(self.secret_key, 'utf-8'), message.encode('utf-8'), hashlib.sha256).hexdigest()

        request.headers.update({
            'CB-ACCESS-SIGN': signature,
            'CB-ACCESS-TIMESTAMP': timestamp,
            'CB-ACCESS-KEY': self.api_key,
            'CB-VERSION': '2020-01-18'
        })
        return request
    
def moveMoneyBetweenAccounts(takeFrom, giveTo):
    giveTo = takeFrom
    account = cbh.tradingClient.get_account(takeFrom)
    
    #account.transfer_money(
    #   to="<coinbase_account_id>",
    #   amount="1",
    #   currency="BTC"
    #)
    txs = {
        'type': 'transfer',
        'account_id': takeFrom,
        'to': giveTo,
        'amount': '10',
        'currency': 'XRP'
    }
    
    auth = CoinbaseWalletAuth(cbh.api_key, cbh.api_secret)
    api_url = 'https://api.coinbase.com/v2/'
    r = requests.post(api_url + 'accounts/' + takeFrom + '/transactions', json=txs, auth=auth)
    print(r)
    print(r.json())
    
    print("Check 2")

#BTC: 3e8a19dd-1e81-5619-a317-fb24cfec6ccb
#BAT: bdd55819-62e3-59ca-b8d2-fdc28b90e1c5
#XLM: 2e7b0eb9-250e-50a2-bb1b-867a402f4f81
#MKR: 69ee3fcd-9eee-574d-944b-1fd0e2119ee5

BTC = getCurrencyID("BTC")
BAT = getCurrencyID("BAT")
XLM = getCurrencyID("XLM")
MKR = getCurrencyID("MKR")

print(BTC)
print(BAT)
print(XLM)
print(MKR)

moveMoneyBetweenAccounts(MKR,XLM)
