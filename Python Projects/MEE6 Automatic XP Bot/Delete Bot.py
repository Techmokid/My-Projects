import discord,os,time
from discord.ext import commands

os.system("title "+"Delete Bot")

ChannelToTalkTo = 800970018682568757
AlertChannel = 652550973021093889
token = 'MzczMDkwODk1NTQ3MDcyNTEy.XfDKjw.rpgF8GTcUsUVU4YMFxUx3tJfipI'
bot = discord.Client()

@bot.event
async def on_ready():
    global AlertChannel
    f = open("C:/Users/aj200/AppData/Local/Programs/Python/Python38/My Python Scripts/Our Nionic Discord Bot/Should We Show Start Message.txt",'r+')
    if (f.readline() == "T"):
        await bot.get_channel(AlertChannel).send("Delete Online")
    f.close()
    
    print("Delete Bot Connected")

@bot.event
async def on_message(message):
    if (str(message.content) == "Bot Status"):
        await bot.get_channel(ChannelToTalkTo).send("Bot 3 Returned: Delete Bot Running")
        return
    
    global boolean
    if ((message.content == "0Qf4urQcBZKII4RqL6Y8") and (message.author == bot.user)):
        await message.delete()

bot.run(token,bot=False)
