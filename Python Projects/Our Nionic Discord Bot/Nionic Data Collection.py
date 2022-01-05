import os,time,discord
from datetime import datetime

os.system("title "+"Data Collector")

ChannelToTalkTo = 461159041696006164
AlertChannel = 461159041696006164
logChannel = 461159041696006164

haveYouStartedYet = False
token = 'MzczMDkwODk1NTQ3MDcyNTEy.XfDKjw.rpgF8GTcUsUVU4YMFxUx3tJfipI'
bot = discord.Client()

print("Data Collector Bot")
print("------------------")

listOfSentInfo = []

def runCommand(cmd):
    return os.system(cmd)

def runCommands(cmd):
    #Turn Command List To Command String
    commandList = ""
    for i in cmd:
        commandList += i + "\n"
    commandList=commandList[:-1]
    
    #Write Command String To File For Execution
    f = open("tempCommandExecution.bat",'w+')
    f.write(commandList)
    f.close()
    
    #Execute Command File
    os.system("tempCommandExecution.bat")

async def logMessage(message):
    date = datetime.date(datetime.now())
    time = datetime.time(datetime.now())
    
    channel = message.channel
    user = message.author
    msg = message.content
    msg = msg.replace("\"","'")
    
    try:
        await bot.get_channel(logChannel).send(str(user) + " sent message containing: " + msg)
    except:
        pass
    
    cmd = "start cmd /c python \"Log Msg.py\" \"" + str(channel) + "\" \"" + str(user) + "\" \"" + str(msg) + "\""
    #runCommand(cmd)

@bot.event
async def on_ready():
    global AlertChannel
    f = open("Should We Show Start Message.txt",'r+')
    if (f.readline() == "T"):
        await bot.get_channel(AlertChannel).send("Bot Response: Data Online")
    f.close()
    
    print("Data Collector Bot Connected")

@bot.event
async def on_message(message):
    if (str(message.guild) != "Discord Bot Testing Server"):
        return
    
    if (str(message.content) == "Bot Status"):
        await bot.get_channel(ChannelToTalkTo).send("Bot 1 Returned: Data Bot Running")
        return

    date = datetime.date(datetime.now())
    time = datetime.time(datetime.now())
    channel = message.channel
    user = message.author
    msg = message.content
    attachments = message.attachments

    attachList = ""
    for i in attachments:
        attachList += i.url + "\n"

    stringToSearch = str(user) + " sent message containing: " + msg
    print(str(user) + " sent message containing: " + msg + " and " + attachList)
    
    if (msg not in listOfSentInfo):
        listOfSentInfo.append(stringToSearch)
        #await bot.get_channel(logChannel).send(stringToSearch)
        await logMessage(message)
    else:
        listOfSentInfo.remove(msg)

bot.run(token,bot=False)
