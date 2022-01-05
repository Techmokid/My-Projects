#!/usr/bin/python3.6
print("Content-Type: text/html\n\n")

import random
import math
from os import system
from time import gmtime, strftime
import asyncio
from discord.ext.commands import Bot
from discord import Game
print("Imported all modules successfully!\n\n")

TOKEN = "NDYxMTU5ODUzMDU1MDE2OTYy.DhUJdg.mGHp8E7fulh8F5tpz5rLN5a7DxA"
BOT_PREFIX = ("*","!","?")
client = Bot(command_prefix=BOT_PREFIX)
CurrentUserCurrency = []
CurrentUsers = []
Servers = []
Reminds = []
Times = []
FinTime = []
TimeUntilNextMine = []
TimesMined = []
MiningPrices = []
MiningCooldown = []
Running = False

#Commands
@client.command(name='8ball',aliases=['eightball','eight_ball','8_ball'],pass_context=True)
async def eight_ball(context):
    possible_responses = ['That is a resounding no', 'It is not looking likely', 'Too hard to tell', 'it is quite possible', 'Definitely']
    await client.say(random.choice(possible_responses) + ', ' + context.message.author.mention)

@client.command(name='btc',aliases=['BTC','bitcoin','Bitcoin','BITCOIN'])
async def bitcoin():
    url = 'https://api.coindesk.com/v1/bpi/currentprice/BTC.json'
    response = requests.get(url)
    result = response.json()['bpi']['USD']['rate']
    arr = result.split(',')
    value = arr[0] + arr[1]
    await client.say("Bitcoin price is currently $" + str(round(float(value)*1.35,2)) + " AUD")

@client.command()
async def sqrt(number):
    await client.say(math.sqrt(float(number)))

@client.command()
async def dice(number):
    result = random.randrange(1,int(number)+1)
    await client.say("You rolled a " + str(result))

@client.command()
async def multiply(number):
    arr = number.split(",")
    result = float(arr[0]) * float(arr[1])
    sentence = str(arr[0]) + " times " + str(arr[1]) + " equals " + str(result)
    await client.say(sentence)

@client.command(name='Currency',aliases=['currency','money','Money','MONEY','CURRENCY','profile','Profile','PROFILE','me','Me','ME'],pass_context=True)
async def Currency(context,User='BLANK'):
    global CurrentUserCurrency
    global CurrentUsers
    global MiningPrices
    global MiningCooldown
    tempVal = 0
    
    if (User=='BLANK'):
        result = -9999
        for i in CurrentUsers:
            if(context.message.author.mention==CurrentUsers[tempVal]):
                result = tempVal
            else:
                tempVal+=1
        try:
            User = CurrentUsers[result]
            Value = CurrentUserCurrency[result]
        except:
            await client.say("An error has occurred. Have you tried the command '!Users' yet?")
        
        sentence = User + " has $" + str(round(float(Value),2)) + "\n\n"
        sentence += "Everytime you work, you can get a maximum of $" + str(round(float(MiningPrices[result]),2))
        sentence += "\nYou can work " + str(round(float(MiningCooldown[result]))) + " seconds after any previous work"
        await client.say(sentence)
    else:
        result = 0
        for i in CurrentUsers:
            if(User==CurrentUsers[tempVal]):
                result = tempVal
            else:
                tempVal+=1
        User = CurrentUsers[result]
        Value = CurrentUserCurrency[result]
        sentence = User + " has $" + str(Value)
        await client.say(sentence)

@client.command(aliases=['users','USERS'],pass_context=True)
async def Users(context):                                                                                                               #USERS CODE
    global CurrentUserCurrency
    global CurrentUsers
    global TimeUntilNextMine
    global TimesMined
    global MiningPrices
    global MiningCooldown
    DoTheyExistInSystem = False
    tempVal = 0
    
    for i in CurrentUsers:
        if(context.message.author.mention==CurrentUsers[tempVal]):
            DoTheyExistInSystem = True
        tempVal +=1
    if(DoTheyExistInSystem==False):
        CurrentUsers.append(context.message.author.mention)
        CurrentUserCurrency.append(0)
        TimeUntilNextMine.append(0)
        TimesMined.append(0)
        MiningPrices.append(100)
        MiningCooldown.append(60)
        print("User " + context.message.author.mention + " has just joined!")
        await client.say("You have been added to my internal memory. Welcome " + context.message.author.mention + "!")
    
    sentence = "The Users currently in my memory are: "
    var = 0
    for i in CurrentUsers:
        sentence += CurrentUsers[var] + ", "
        var += 1
    await client.say(sentence)

@client.command(pass_context=True,aliases=['upgrade','UPGRADE'])
async def Upgrade(context,command1,command2):                                                                                                                     #Shopping Code
    global CurrentUserCurrency
    global CurrentUsers
    global MiningPrices
    global MiningCooldown
    cost = 0
    user = -9999
    helper = False
    
    if ((command1=='help') or (command1=='Help') or (command1=='HELP') or (command2=='help') or (command2=='Help') or (command2=='HELP')):
        sentence = "You asked for help with the upgrade shop? Well you asked the right person!\n\n"
        sentence += "To buy something from the shop, use the command ?Upgrade buy [Name of upgrade]\n"
        sentence += "To check store prices without actually buying anything from the shop, use the command ?Upgrade price [Name of upgrade]\n\n"
        sentence += "The upgrade currently available instore are:\n"
        sentence += "\t-cooldown: This is the time taken before you can work again. Upgrading this decreases the time taken between work. Who's a busy little bee?\n"
        sentence += "\t-workprices: This is the maximum amount of money you can get from each work. It's almost like getting a promotion for saying ?work!"
        await client.say(sentence)
        helper = True
    
    if (helper == False):
        if((command2=='Cooldown') or (command2=='CoolDown') or (command2=='cooldown') or (command2=='COOLDOWN') or (command2=='coolDown')):
            var = 0
            for i in CurrentUsers:
                if(i == context.message.author.mention):
                    user = var
                else:
                    var += 1

            cost = round((200*100) / float(MiningCooldown[user]),2)
        
            if((command1=='price') or (command1=='Price') or (command1=='PRICE') or (command1=='prices') or (command1=='Prices') or (command1=='PRICES')):
                await client.say("The cost of the cooldown upgrade for " + context.message.author.mention + " is $" + str(cost))
            elif((command1=='buy') or (command1=='Buy') or (command1=='BUY')):
                if(float(CurrentUserCurrency[user]) >= cost):
                    await client.say("You have bought the cooldown upgrade!")
                    MiningCooldown[user] = str(float(MiningCooldown[user]) / 1.25)
                    CurrentUserCurrency[user] = str(float(CurrentUserCurrency[user]) - cost)
                else:
                   await client.say("You do not have enough for this upgrade")
            else:
                await client.say("I do not know that upgrade")
        elif((command2=='WorkPrices') or (command2=='WorkPrices') or (command2=='workprices') or (command2=='WORKPRICES') or (command2=='workPrices')):
            var = 0
            for i in CurrentUsers:
                if(i == context.message.author.mention):
                    user = var
                else:
                    var += 1

            cost = round(3 * float(MiningPrices[user]),2)
        
            if((command1=='price') or (command1=='Price') or (command1=='PRICE') or (command1=='prices') or (command1=='Prices') or (command1=='PRICES')):
                await client.say("The cost of the work prices upgrade for " + context.message.author.mention + " is $" + str(cost))
            elif((command1=='buy') or (command1=='Buy') or (command1=='BUY')):
                if(float(CurrentUserCurrency[user]) >= cost):
                    await client.say("You have bought the work prices upgrade!")
                    MiningPrices[user] = str(float(MiningPrices[user]) * 1.25)
                    CurrentUserCurrency[user] = str(float(CurrentUserCurrency[user]) - cost)
                else:
                   await client.say("You do not have enough for this upgrade")
            else:
                await client.say("I do not know that upgrade")
        else:
            await client.say("I do not understand. Try formatting your command as ?Upgrade [buy/price] [upgrade name]")
    
@client.command()
async def GetPassKey():
    global keyUsed
    global key
    
    result = random.randrange(1,99999999+1)
    print("Requested Password: " + str(result))
    await client.say("Password has been sent to the administrator")

    keyUsed = False
    key = result

@client.command()
async def Admin(command,password):
    global keyUsed
    global key
    global CurrentUserCurrency
    global CurrentUsers
    
    try:
        if((str(password)==str(key)) and (keyUsed==False)):
            keyUsed = True
            await client.say("Password Accepted. Processing Command...")
            if(str(command)=='ForceRestart'):
                await on_ready()
            if(str(command)=='ShutDown'):
                await client.say("Goodnight Everyone!")
            if(str(command)=='ClearCurrency'):
                CurrentUserCurrency = []
                while (len(CurrentUsers) != len(CurrentUserCurrency)):
                    CurrentUserCurrency.append(0)
                await client.say("All money has been removed from memory")
        else:
            await client.say("Incorrect or already used Password. Forced Restart Denied")
    except:
        await client.say("Please Enter Administrator Password")

@client.command(aliases=['square','SQUARE'])
async def Square(number):
    result = math.pow(float(number),2)

@client.command()
async def add(number):
    arr = number.split(",")
    result = float(arr[0]) + float(arr[1])
    sentence = float(arr[0]) + " plus " + float(arr[1]) + " equals " + str(result)
    await client.say(sentence)

@client.command()
async def subtract(number):
    arr = number.split(",")
    result = float(arr[0]) - float(arr[1])
    await client.say(float(arr[0]) + " subtract " + float(arr[1]) + " equals " + result)

@client.command(pass_context=True)
async def RemindMe(context,sentence,time):
    global Reminds
    global Times

    if((len(time.split('s'))==2)):
        arr=time.split('s')
        await client.say("I have started a timer for " + arr[0] + " seconds")
        Reminds.append(sentence)
        Times.append(int(arr[0]))
        
    elif((len(time.split('m'))==2)):
        arr=time.split('m')
        await client.say("I have started a timer for " + arr[0] + " minutes")
        Reminds.append(sentence)
        Times.append(int(arr[0]) * 60)
        
    elif((len(time.split('h'))==2)):
        arr=time.split('h')
        await client.say("I have started a timer for " + arr[0] + " hours")
        Reminds.append(sentence)
        Times.append(int(arr[0]) * 3600)
        
    elif(len(time.split(':'))==3):
        #The Value is a Specific Time
        await client.say("I'm still being worked on here. Please try again soon though :)")
    else:
        await client.say("That is not a valid time!")
        return

@client.command(aliases=['finishedtimers','finishedtimer','FinishedTimer','FINISHEDTIMER','FINISHEDTIMERS'])
async def FinishedTimers():
    global FinTime
    
    sentence = "The following timers have finished: "
    val = 0
    for i in FinTime:
        print(FinTime[val])
        sentence += FinTime[val] + ", "
        val += 1
    await client.say(sentence)

@client.command(pass_context=True)
async def TalkToOtherServers(context):
    for server in client.servers:
        if(server!=context.message.author.server):
            await client.say(context.message.author.mention + " says Hello!")

@client.command(aliases=['clearfinishedtimers','clearFinishedTimers','CLEARFINISHEDTIMERS'])
async def ClearFinishedTimers():
    global FinTime
    FinTime = []

@client.command(pass_context=True,aliases=['lottery','LOTTERY','Lotto','LOTTO','lotto'])
async def Lottery(context,amount):
    global CurrentUserCurrency
    global CurrentUsers

    amount = float(amount)
    winnings = 1000000
    var = 0
    user = -9999
    
    for i in CurrentUsers:
        if(i == context.message.author.mention):
            user = var
        else:
            var += 1
    
    if (float(CurrentUserCurrency[user]) < amount):
        await client.say("You don't have enough money to buy a lottery ticket at this price")
    else:
        CurrentUserCurrency[user] =  str(float(CurrentUserCurrency[user]) - amount)
        randomValue = random.randrange(1,1000000)
        if (randomValue < 2):
            await client.say("CONGRATULATIONS!!! You won the jackpot of " + str(amount * winnings))
            CurrentUserCurrency[user] = str(float(CurrentUserCurrency[user]) + amount * winnings)
        else:
            await client.say("Unfortunately you didn't win this time")

@client.command(aliases=['work','WORK'],pass_context=True)
async def Work(context):
    global CurrentUserCurrency
    global CurrentUsers
    global TimeUntilNextMine
    global TimesMined
    global MiningPrices
    global MiningCooldown

    var = 0
    user = -9999
    
    for i in CurrentUsers:
        if(i == context.message.author.mention):
            user = var
        else:
            var += 1
    
    if(int(TimeUntilNextMine[user]) < 1):
        TimesMined[user] = str(int(TimesMined[user]) + 1)
        rand = random.randrange(1,int(round(float(MiningPrices[user])) + 1))
        CurrentUserCurrency[user] = str(float(CurrentUserCurrency[user]) + rand)
        
        if(rand < float(MiningPrices[user]) / 4):
            result = context.message.author.mention + " had a bad day and only earned $" + str(rand)
        elif((rand > float(MiningPrices[user]) / 4) and (rand < float(MiningPrices[user]) / 2)):
            result = context.message.author.mention + " had an ok day and earned $" + str(rand)
        elif((rand >  float(MiningPrices[user]) / 2) and (rand < float(MiningPrices[user]) / 4 * 3)):
            result = context.message.author.mention + " had a good day and earned $" + str(rand)
        else:
            result = context.message.author.mention + " had a great day and earned $" + str(rand) + "!"
        TimeUntilNextMine[user] = float(MiningCooldown[user])
        await client.say(result)

        if (float(TimesMined[user]) == 10):
            sentence = context.message.author.mention + ", your bills are due"
            amount = float(MiningPrices[user]) / 8 * 3
            CurrentUserCurrency[user] = str(float(CurrentUserCurrency[user]) - amount)
            await client.say(sentence)
            sentence = context.message.author.mention + " now has $" + CurrentUserCurrency[user] + " in his account"
            TimesMined[user] = 0
    else:
        await client.say("You've only just worked! Relax, kick your feet up, and rest for at least another " + TimeUntilNextMine[user] + " seconds")

@client.command(aliases=['LB','Lb','lB','leaderboard','Leaderboard','leaderBoard','LEADERBOARD','LeaderBoard'])
async def lb():
    global CurrentUserCurrency
    global CurrentUsers
    
    sortedCurrencies = CurrentUserCurrency
    sortedCurrencies.sort()
    sortedCurrencies.reverse()
    
    sortedUsers = []
    var = -1
    for i in CurrentUserCurrency:
        var += 1
        if (CurrentUserCurrency[var] == sortedCurrencies[var]):
            sortedUsers.append(CurrentUsers[var])

    sentence = "The current leaderboard:"
    var = 1
    for i in sortedUsers:
        sentence += "\n" + str(var) + " - " + str(sortedUsers[var-1]) + " has $" + str(round(float(sortedCurrencies[var-1]),2))
        var += 1
    await client.say(sentence)

#Events
@client.event
async def on_ready():
    global CurrentUserCurrency
    global CurrentUsers
    global TimeUntilNextMine
    global TimesMined
    global MiningPrices
    global MiningCooldown

    #Here is where you would read from the file and seperate out to get the variables Users and Currency
    try:
        f=open("/home/aj2000wa/public_html/cgi-bin/Discord User Currency Data.txt",'r')
        
        print("File is open!")
        RawInput = []
        RawInput = f.readlines(0)
        print(RawInput)
        sentence1 = RawInput[0].split('|')
        sentence2 = RawInput[1].split('|')
        sentence3 = RawInput[2].split('|')
        sentence4 = RawInput[3].split('|')
        sentence5 = RawInput[4].split('|')
        sentence6 = RawInput[5].split('|')
        
        CurrentUsers = sentence1[:-1]
        CurrentUserCurrency = sentence2[:-1]
        TimeUntilNextMine = sentence3[:-1]
        TimesMined = sentence4[:-1]
        MiningPrices = sentence5[:-1]
        MiningCooldown = sentence6[:-1]
    except:
        print("ERROR: Could not load all variables correctly")
        print("Press Enter to Quit")
        end = input()
        quit()
    await client.change_presence(game=Game(name="with Andrey!"))
    print("Logged in as " + client.user.name)
    
    sentence = "Loaded CurrentUsers: "
    for a in CurrentUsers:
        sentence += a + ","
    
    sentence += "\nLoaded CurrentUserCurrency: "
    for b in CurrentUserCurrency:
        sentence += b + ","
    
    sentence += "\nLoaded TimeUntilNextMine: "
    for c in TimeUntilNextMine:
        sentence += c + ","
    
    sentence += "\nLoaded TimesMined: "
    for d in TimesMined:
        sentence += d + ","
    
    sentence += "\nLoaded MiningPrices: "
    for e in MiningPrices:
        sentence += e + ","
    
    sentence += "\nLoaded MiningCooldown: "
    for f in MiningCooldown:
        sentence += f + ","
    print(sentence)

#Seperate Functions
async def list_servers():
    global CurrentUserCurrency
    global CurrentUsers
    global Servers
    global Times
    global Reminds
    global FinTime
    global TimeUntilNextMine
    global MiningPrices
    global MiningCooldown
    
    await client.wait_until_ready()
    while not client.is_closed:
        await asyncio.sleep(1)
        
        sentence = "Current Servers: "
        for server in client.servers:
            sentence += server.name + ","
        if(Servers!=sentence):
            print(sentence)
            print()
            Servers = sentence
        
        sentence = ""
        f = open("/home/aj2000wa/public_html/cgi-bin/Discord User Currency Data.txt",'w')
        for i in CurrentUsers:
            sentence += str(i) + "|"
        sentence += "\n"
        for i in CurrentUserCurrency:
            sentence += str(i) + "|"
        sentence += "\n"
        for i in TimeUntilNextMine:
            sentence += str(i) + "|"
        sentence += "\n"
        for i in TimesMined:
            sentence += str(i) + "|"
        sentence += "\n"
        for i in MiningPrices:
            sentence += str(i) + "|"
        sentence += "\n"
        for i in MiningCooldown:
            sentence += str(i) + "|"
        f.write(sentence)
        f.close()

        val = 0
        for i in Times:
            Times[val] = Times[val] - 1
            if(Times[val]==0):
                print("Timer finished")
                FinTime.append(Reminds[val])
                del Times[val]
                del Reminds[val]
            val += 1
        
        val2 = 0
        for i in TimeUntilNextMine:
            if ((int(i) < 1) == False):
                TimeUntilNextMine[val2] = str(int(TimeUntilNextMine[val2]) - 1)
            val2 += 1

#Function Calls
client.loop.create_task(list_servers())
client.run(TOKEN)
