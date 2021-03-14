import random,math

results = []
def funct():
    global results
    
    probabilityOfWinning = 0.5
    startingBet = 1
    availableMoney = 10_000
    betMultiplier = 2
    winningsMultiplier = 2

    currentBet = startingBet
    maximumAmount = 0
    looper = 0
    while(availableMoney > 0):
        looper += 1
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

    print("We went broke after a max profit of $",maximumAmount,"and after",looper,"iterations")
    results.append([maximumAmount,looper])

x = 0
while(x < 100):
    x += 1
    funct()

averageProfit = 0
averageLoops = 0
for i in results:
    averageProfit += i[0]
    averageLoops += i[1]
    
print("Average Max Profit: $" + str(averageProfit / x))
print("Average Max Loops: " + str(averageLoops / x))
