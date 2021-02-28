#Edit these values as required
<<<<<<< HEAD
pricePerMiner = 1300 + 6*1300                  # This is how much the mining rig earns per day. In this example, $22.50
earningsPerMiner = 16.5*6
numberOfPeople = 4                          # This is the number of people. We are splitting it between the 3 of us
daysAfterPaymentUntilNewMinerArrives = 60   # This is how long it takes between buying a miner, and having it here and ready to mine
=======
pricePerMiner = 6300                        # This is the cost of the mining rig. In this example, $6,300
earningsPerMiner = 29                     # This is how much the mining rig earns per day. In this example, $22.50
numberOfPeople = 3                          # This is the number of people. We are splitting it between the 3 of us
daysAfterPaymentUntilNewMinerArrives = 14   # This is how long it takes between buying a miner, and having it here and ready to mine
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c





#Don't touch anything below here-----------------------------------------------------------------
import time,math

def dayCorrector(x):
    while(x > 365):
        x -= 365
    return x

numberOfMiners = 1
daysElapsed = 0
<<<<<<< HEAD
once = True
=======
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c

while(True):
    msg = "Earnings/dy: $" + str(earningsPerMiner * numberOfMiners)
    msg += "   \t\tEarnings/wk: $" + str(earningsPerMiner * numberOfMiners * 7)
<<<<<<< HEAD
    if (once == False):
        msg += "   \t\tEarnings/dy each: $" + str(earningsPerMiner * numberOfMiners / numberOfPeople)
        msg += "   \t\tEarnings/wk each: $" + str(earningsPerMiner * numberOfMiners * 7 / numberOfPeople)
    msg += "   \t\tDys Elapsed:" + str(dayCorrector(daysElapsed))
    msg += "   \t\tYrs Elapsed: " + str(math.floor(daysElapsed/365))
    if (once == False):
        msg += "   \t\t# Rent: " + str(math.floor(earningsPerMiner * numberOfMiners * 7 / 360))
    print(msg)
    
    if ((earningsPerMiner * numberOfMiners * 7 / numberOfPeople >= 1000) and (once == False)):
        while(True):
            continue
    
    daysToNext = math.ceil(pricePerMiner / (earningsPerMiner * numberOfMiners)) + daysAfterPaymentUntilNewMinerArrives
    numberOfMiners += 1
    daysElapsed += daysToNext
    #time.sleep(1)
    if ((math.floor(daysElapsed / 365) >= 1) and once):
        once = False
        earningsPerMiner /= 2
        print()
        print("Activated Payouts")
        print()
    
=======
    msg += "   \t\tEarnings/dy each: $" + str(earningsPerMiner * numberOfMiners / numberOfPeople)
    msg += "   \t\tEarnings/wk each: $" + str(earningsPerMiner * numberOfMiners * 7 / numberOfPeople)
    msg += "   \t\tDys Elapsed:" + str(dayCorrector(daysElapsed))
    msg += "   \t\tYrs Elapsed: " + str(math.floor(daysElapsed/365))
    msg += "   \t\t# Rent: " + str(math.floor(earningsPerMiner * numberOfMiners * 7 / 360))
    print(msg)

    daysToNext = math.ceil(pricePerMiner / (earningsPerMiner * numberOfMiners)) + daysAfterPaymentUntilNewMinerArrives
    numberOfMiners += 1
    daysElapsed += daysToNext
    time.sleep(1)
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c
    
        
