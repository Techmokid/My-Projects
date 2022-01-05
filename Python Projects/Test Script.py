import base64,requests,sys,time

url = 'https://api.github.com/repos/Techmokid/My-Discord-Project-1/contents/Log%20Msg.py'
req = requests.get(url)
if req.status_code == requests.codes.ok:
    req = req.json()  # the response is a JSON
    # req is now a dict with keys: name, encoding, url, size ...
    # and content. But it is encoded with base64.
    content = str(base64.b64decode(req['content']))
    content = content.replace("\\n","\n")
    content = content.replace("\\r","")
    content = content.replace("'","")[1:]
    result = content.split("\n")
else:
    print('Content was not found.')
    time.sleep(2)
    sys.exit()

print(content)
