import requests

URL = "http://192.168.1.15:8080/index2.php"

def setServerValue(key, val):
    global ID
    
    serverResponse = requests.get(url=URL,headers={'Setvalue':val,'Key':key,'Id':ID})
    if (serverResponse.ok == False):
        raise Exception("Error when getting server response LOL")

ID = input("ID: ")
setServerValue("RunMode",input("Value: "))
