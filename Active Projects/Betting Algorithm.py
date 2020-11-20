import random

probabilityOfWinning = 0.5
startingBet = 1
availableMoney = 10_000
betMultiplier = 3
winningsMultiplier = 2

currentBet = startingBet
maximumAmount = 0
while(availableMoney > 0):
    if (maximumAmount < availableMoney):
        maximumAmount = availableMoney
    
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
