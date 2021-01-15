#Edit these values as required
pricePerMiner = 6300                # This is the cost of the mining rig. In this example, $6,300
earningsPerMiner = 22.5             # This is how much the mining rig earns per day. In this example, $22.50
numberOfPeople = 3                  # This is the number of people. We are splitting it between the 3 of us
daysUntilNewMinerIsReady = 14       # This is how long it takes between buying a miner, and having it here and ready to mine





#Don't touch anything below here-----------------------------------------------------------------
import time,math

def dayCorrector(x):
    while(x > 365):
        x -= 365
    return x

numberOfMiners = 1
daysElapsed = 0

while(True):
    msg = "Earnings/dy: $" + str(earningsPerMiner * numberOfMiners)
    msg += "   \t\tEarnings/wk: $" + str(earningsPerMiner * numberOfMiners * 7)
    msg += "   \t\tEarnings/dy each: $" + str(earningsPerMiner * numberOfMiners / numberOfPeople)
    msg += "   \t\tEarnings/wk each: $" + str(earningsPerMiner * numberOfMiners * 7 / numberOfPeople)
    msg += "   \t\tDys Elapsed:" + str(dayCorrector(daysElapsed))
    msg += "   \t\tYrs Elapsed: " + str(math.floor(daysElapsed/365))
    msg += "   \t\t# Rent: " + str(math.floor(earningsPerMiner * numberOfMiners * 7 / 360))
    print(msg)

    daysToNext = math.ceil(pricePerMiner / (earningsPerMiner * numberOfMiners)) + daysUntilNewMinerIsReady
    numberOfMiners += 1
    daysElapsed += daysToNext
    time.sleep(1)
    
        
