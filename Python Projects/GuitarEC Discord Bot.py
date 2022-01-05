import os,discord,time,sys
from random import random as rand

#Change these variables as you want---------------------------------------------------

commandStarter = "-"
AlertChannel = 461159041696006164

#List the functions. "Command, python function name, number of arguments, description"

functions = ["help","help",0,"Lists all commands and lists help tips"]
functions += ["randomNumber","randomNumberGenerator",2,"Picks a random integer between the minimum and maximum values.\n   You can set the minimum and maximum values by adding them to the end of the command"]
functions += ["randomDecimal","randomFloatGenerator",0,"Picks a random decimal number between 0 and 1"]
functions += ["randomBoolean","randomBooleanGenerator",0,"Picks a random Boolean value (True or False)"]

#System variables. Do not alter-------------------------------------------------------

online = False
token = "NjY3NTUyNDUwNDIwNjcwNDc2.XiEYyQ.DC8m-xqWgaiUBDd3K7dhOtmRwb8"
bot = discord.Client()

#Put bot functions here---------------------------------------------------------------

async def randomNumberGenerator(msg,args,shouldRun=True):
    if (shouldRun == False):
        return
    await msg.channel.send("Your random number is: " + str(rand(args[0], args[1])))

async def randomFloatGenerator(msg,args,shouldRun=True):
    if (shouldRun == False):
        return
    await msg.channel.send("Your random decimal number is: " + str(rand()))

async def randomBooleanGenerator(msg,args,shouldRun=True):
    if (shouldRun == False):
        return
    
    answer = True
    if (round(rand()) == 0):
        answer = False
    
    await msg.channel.send("Your random boolean is: " + str(answer))

#System functions. Do Not alter-------------------------------------------------------

async def help(msg,args=[],shouldRun=True):
    global commandStarter
    if (shouldRun == False):
        return
    
    if (len(args) == 0):
        sentence2 = ""
        for i in range(0,int(getNumberOfCommands())):
            if (int(getNumberOfArguments(i)) != 0):
                sentence2 += "\n - \"" + getCommand(i) + "\" takes " + str(getNumberOfArguments(i)) + " arguments"
            else:
                sentence2 += "\n - \"" + getCommand(i) + "\""
        
        sentence1 = "Use " + commandStarter + "help [command] to get more information on a command"
        sentence1 += "\nUnless stated otherwise, the commands do not take any arguments"
        await msg.channel.send(sentence1 + sentence2)
        return
    
    if (findCommandVal(args[0]) == -1):
        await msg.channel.send("I'm sorry, but I don't recognise the command: " + args[0])
        return
    
    index = findCommandVal(args[0])
    sentence = "Help information on the command \"" + args[0] + "\":" + "\n"
    sentence += " - Number Of Arguments Required: " + str(getNumberOfArguments(index)) + "\n"
    sentence += " - Description: " + getDescription(index)
    
    await msg.channel.send(sentence)

def getCommand(val):
    return functions[val*4]

def getFunctionName(val):
    return functions[val*4 + 1]

def getNumberOfArguments(val):
    return functions[val*4 + 2]

def getDescription(val):
    return functions[val*4 + 3]

def getNumberOfCommands():
    return len(functions)/4

def findCommandVal(command):
    result = -1
    for i in range(0,int(getNumberOfCommands())):
        if (getCommand(i) == command):
            result = i
    return result

#Bot events---------------------------------------------------------------------------

@bot.event
async def on_ready():
    global AlertChannel,online
    
    if (online == False):
        print("\n\nGuitarEC Discord Bot")
        print("------------------")
        await bot.get_channel(AlertChannel).send("Good Morning everyone! I am now online!")
        print("Bot Online!")
        online = True
    else:
        print("Bot has reconnected after loosing connection temporarily")

@bot.event
async def on_message(msg):
    #if msg.author == bot.user:
    #    return
    
    global commandStarter
    msgArray = str(msg.content).split(' ')
    
    #Split the message into command and arguments
    commandSent = msgArray[0]
    msgArray.pop(0)
    args = msgArray
    
    #If the message doesn't start with the command starter, ignore it
    if (commandSent.find(commandStarter) != 0):
        return
    
    #Create special case for help function
    if (commandStarter + "help" == commandSent):
        await help(msg,args)
    else:
        #Command is detected. Now to find if the command exists
        for i in range(0,int(getNumberOfCommands())):
            if (commandStarter + getCommand(i) == commandSent):
                if (getNumberOfArguments(i) == len(args)):
                    await globals()[getFunctionName(i)](msg,args)
                else:
                    await msg.channel.send("Incorrect Number Of Arguments! Expected " + str(getNumberOfArguments(i)) + ", but got " + str(len(args)))

#System checks for function errors----------------------------------------------------

j = 0
error = False
for i in functions:
    if (j % 4 == 1):
        try:
            globals()[i](shouldRun=False)
        except Exception as ex:
            message = "{0}".format(type(ex).__name__, ex.args)
            if (str(message) == "KeyError"):
                print("ERROR: COMMAND NOT FOUND - " + str(i))
                error = True
    j += 1

if (error):
    time.sleep(5)
    sys.exit()

if (getNumberOfCommands() % 1 != 0):
    print("ERROR: NUMBER OF COMMANDS DOES NOT EQUAL NUMBER OF FUNCTIONS!")
    time.sleep(5)
    sys.exit()

#Now check to see if there are command doubleups--------------------------------------

error = False
for i in range(0,int(getNumberOfCommands())):
    for j in range(0,int(getNumberOfCommands())):
        if (i != j):
            if (getCommand(i) == getCommand(j)):
                print("WARNING: COMMAND DOUBLEUP FOUND WITH COMMAND: " + getCommand(i))
                error = True
            if (getFunctionName(i) == getFunctionName(j)):
                print("WARNING: COMMAND " + getCommand(i) + " AND COMMAND " + getCommand(j) + " BOTH POINT TO FUNCTION " + getFunctionName(i))
                error = True
if (error):
    print(" - SETUP WILL CONTINUE, BUT THIS MAY LEAD TO UNDESIRED RESULTS!\n\n\n")

#Start the bot------------------------------------------------------------------------

print("Starting bot")
bot.run(token)
