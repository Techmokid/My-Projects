import asyncio,time,os
from discord.ext.commands import Bot
from discord import Game

ToBot = False
f=open("C:\\Users\\Andrey\\AppData\\Local\\Programs\\Python\\Python36-32\\Lib\\site-packages\\discord\\client.py",'r')
data = f.readlines(0)
f.close()
line = 345
lineSentence = data[line - 1].split(" = ")
if (ToBot):
    lineSentence[0] = lineSentence[0] + " = kwargs.pop('bot', True)\n"
else:
    lineSentence[0] = lineSentence[0] + " = False\n"
data[line - 1] = lineSentence[0]
solution = ""
for i in data:
    solution +=i

yes=True
if(yes):
    f=open("C:\\Users\\Andrey\\AppData\\Local\\Programs\\Python\\Python36-32\\Lib\\site-packages\\discord\\client.py",'w')
    f.write(solution)
    f.close()


TOKEN = "MzczMDkwODk1NTQ3MDcyNTEy.DhobmQ.TeGNR3xLYiVa4pAbxgIAXPPKVUM"
BOT_PREFIX = ("!")
client = Bot(command_prefix=BOT_PREFIX)

@client.command()
async def Start():
    print("Started")
    while(True):
        await asyncio.sleep(61)
        await client.say("!Work")

@client.event
async def on_ready():
    print("Logging In...")
    await client.change_presence(game=Game(name="with AutoWorkBot!"))
    print("Logged in as " + client.user.name)

client.run(TOKEN)
