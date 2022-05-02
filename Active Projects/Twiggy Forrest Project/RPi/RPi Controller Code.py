from os.path import exists
import requests

#URL = "http://www.techmo.unity.chickenkiller.com"
URL = "http://192.168.1.15:8080"
ID_Filepath = "C:/Users/aj200/Desktop/ID.txt"

# If the device does not have an assigned ID, get one
if (exists(ID_Filepath) == False):
    requests.get(url=URL,params={'Newid':'1'}).text

PARAMS = {}

r = requests.get(url=URL)

print(r.text)
