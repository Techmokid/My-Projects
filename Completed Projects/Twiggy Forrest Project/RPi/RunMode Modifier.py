import requests,hashlib,hmac

URL = "http://192.168.1.15:666/index2.php"

def encryptData(data,key):
    return hmac.new(bytes(key , 'utf-8'), msg = bytes(data , 'utf-8'), digestmod = hashlib.sha256).hexdigest()

def stripContent(x):
    content = str(x.content)
    startVal = content.find("<body>") + len("<body>")
    endVal = content.rfind("</body>")
    return content[startVal+2:endVal]

def setRunmode(ID,val):
    serverResponse = requests.get(url=URL,headers={'Setrunmode':val,'Id':ID})
    if (serverResponse.ok == False):
        raise Exception("Error when getting server response LOL")
    print(stripContent(serverResponse))

setRunmode(input("ID: "),input("Runmode: "))
