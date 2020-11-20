import random,math

# sin(45) is the "Break even" point
probabilityOfWinning = 0.5
startingBet = 1
availableMoney = 100_000_000
betMultiplier = 2
winningsMultiplier = 2

currentBet = startingBet
maximumAmount = 0
looper = 0
while(availableMoney > 0):
    looper += 1
    if (maximumAmount < availableMoney):
        maximumAmount = availableMoney
    if (looper == 1_000_000):
        print(maximumAmount)
        looper = 0
    randomPick = random.random()
    
    if (randomPick <= probabilityOfWinning):
        # We won the bet
        availableMoney += currentBet * winningsMultiplier
        #print("Won: ",currentBet,"\t\t\tCurrent Available Amount:",availableMoney)
        currentBet = startingBet
    else:
        #We lost the bet
        #print("Lost:",currentBet,"\t\t\tCurrent Available Amount:",availableMoney)
        currentBet *= betMultiplier
        availableMoney -= currentBet

print("We went broke",maximumAmount)
