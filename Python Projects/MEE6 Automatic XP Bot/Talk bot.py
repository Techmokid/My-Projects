import discord,os,time,winsound
from discord.ext import commands

os.system("title "+"Talk Bot")

ChannelToTalkTo = 800970018682568757
AlertChannel = 652550973021093889
haveYouStartedYet = False
token = 'MzczMDkwODk1NTQ3MDcyNTEy.XfDKjw.rpgF8GTcUsUVU4YMFxUx3tJfipI'
bot = discord.Client()

@bot.event
async def on_ready():
    global AlertChannel
    f = open("C:/Users/aj200/AppData/Local/Programs/Python/Python38/My Python Scripts/Our Nionic Discord Bot/Should We Show Start Message.txt",'r+')
    if (f.readline() == "T"):
        await bot.get_channel(AlertChannel).send("Talk Online")
    f.close()
    
    print("Talk Bot Connected")
    await bot.get_channel(ChannelToTalkTo).send("0Qf4urQcBZKII4RqL6Y8")

@bot.event
async def on_message(message):
    global ChannelToTalkTo,haveYouStartedYet
    
    if (str(message.content) == "Bot Status"):
        await bot.get_channel(ChannelToTalkTo).send("Bot 4 Returned: Talk Bot Running")
        return
    
    if (((message.author == bot.user) and (message.content == "0Qf4urQcBZKII4RqL6Y8")) or ((haveYouStartedYet == False) and (message.content == "start"))):
        haveYouStartedYet = True
        time.sleep(60)
        await bot.get_channel(ChannelToTalkTo).send("0Qf4urQcBZKII4RqL6Y8")
        winsound.Beep(800, 200)

bot.run(token,bot=False)
