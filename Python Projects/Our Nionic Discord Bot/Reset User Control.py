import discord,time

token = 'MzczMDkwODk1NTQ3MDcyNTEy.XeCQYw.dnoSu4mfslZgJa_R9Q57c8Y_peM'
bot = discord.Client()

@bot.event
async def on_ready():
    await bot.change_presence(activity=discord.Game(name="User-only Control"))
    time.sleep(60*60*24)
    await bot.close()

bot.run(token,bot=False)
