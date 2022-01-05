import os,discord,re
from datetime import datetime

os.system("title "+"Swear Monitor")

print("Swear Monitor")
print("-------------")

ChannelToTalkTo = 652550973021093889
AlertChannel = 652550973021093889
haveYouStartedYet = False
token = 'MzczMDkwODk1NTQ3MDcyNTEy.XfDKjw.rpgF8GTcUsUVU4YMFxUx3tJfipI'
bot = discord.Client()

def stripCharacters(x,sub):
    if (sub):
        x = x.replace("!","i")
        x = x.replace("$","s")
        x = x.replace("#","h")
    
    return ''.join([i for i in re.sub(re.compile('\W'), '', x) if not i.isdigit()]).replace('_','').lower() 

def on_exit(sig, func=None):
    os.system("start /min cmd /c python \"Reset User Control.py\"")

@bot.event
async def on_ready():
    await bot.change_presence(activity=discord.Game(name="Dual-control Active"))
    
    global AlertChannel
    f = open("Should We Show Start Message.txt",'r+')
    if (f.readline() == "T"):
        await bot.get_channel(AlertChannel).send("Bot Response: Redaction Monitor Online")
    f.close()
    print("Swear Monitor Connected")

@bot.event
async def on_message(message):
    if (str(message.guild) != "Nionica"):
        return
    
    if (str(message.content) == "Bot Status"):
        await bot.get_channel(ChannelToTalkTo).send("Bot 2 Returned: Swear Monitor Running")
        return
    
    with open("User Swearing Database.txt") as my_file:
        for line in my_file:
            if (stripCharacters(line,True) in stripCharacters(message.content,True)):
                await message.delete()
                await message.channel.send(message.author + ": ---Redacted---")
            if (stripCharacters(line,True) in stripCharacters(message.content,False)):
                try:
                    await message.delete()
                except:
                    pass

#win32api.SetConsoleCtrlHandler(on_exit, True)
bot.run(token,bot=False)
