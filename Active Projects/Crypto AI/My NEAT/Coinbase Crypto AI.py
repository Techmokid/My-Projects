import NEAT_AI_INTERFACE as naii
import coinbase_handler as cbh
import os,time

AIData = cbh.getBaseAIData("config.txt")

#Access using "coinbaseData[0].price"
coinbaseData = cbh.getPreviousPricesList()
with open("Fitness Monitor.txt","w+") as f:
    f.write("")

#Start of AI code
numberOfGenerations = 0
def RunAIs(nn, config):
    global numberOfGenerations
    numberOfGenerations += 1
    
    print("Training Generation: " + str(numberOfGenerations))
    start_time = time.time()
    genomes = nn.genomes
    
    #Here we have the entire AI structure network. Just iterate over all the different structures in the network
    maxFitness = -100000
    testCoinbaseData = cbh.getPreviousPricesList(True)
    for g in genomes:
        #iterating over every genome
        exampleWallet = 500
        exampleShares = 0
        for baseIndex in range(0,len(testCoinbaseData) - AIData.inputs_count):
            temp = []
            for currentPosition in range(0,AIData.inputs_count):
                temp.append(float(testCoinbaseData[baseIndex + currentPosition].price))
            neat_outputs = g.getOutput(temp)
            if (neat_outputs[0] > 0.5):
                percentage = neat_outputs[2]
                if (percentage < 0):
                    percentage = 0
                if (percentage > 1):
                    percentage = 1
                
                #Here we buy
                buyPrice = float(testCoinbaseData[baseIndex + currentPosition].price) / 10000
                numberOfSharesThatICanBuy = exampleWallet / buyPrice
                numberOfBoughtShares = numberOfSharesThatICanBuy * percentage
                
                exampleWallet -= buyPrice * numberOfBoughtShares
                exampleShares += numberOfBoughtShares
            if (neat_outputs[1] > 0.5):
                percentage = neat_outputs[2]
                if (percentage < 0):
                    percentage = 0
                if (percentage > 1):
                    percentage = 1
                
                #Here we sell
                sellPrice = float(testCoinbaseData[baseIndex + currentPosition].price) / 11000
                numberOfSoldShares = exampleShares * percentage
                
                exampleWallet += sellPrice * numberOfSoldShares
                exampleShares -= numberOfSoldShares
        g.fitness = exampleWallet
        if (exampleWallet > maxFitness):
            maxFitness = exampleWallet
    nn.updateGenomeList()
    print(" - Best fitness: " + str(maxFitness))
    with open("Fitness Monitor.txt","a+") as f:
        f.write(str(numberOfGenerations) + "\t\t\t" + str(maxFitness) + "\n")
    print(" - Training Time:  " + str(int((time.time() - start_time)*100)/100) + " seconds\n")

print("NEAT AI: Configuring NEAT AI file data...")
print("NEAT AI: Note, depending on your configuration, this may take awhile")
print("NEAT AI: To speed this up, please edit the \"num_hidden\" and \"num_connections\" values in the config file")
nn = naii.network("config.txt",False)

print()
for i in range(0,100):
    RunAIs(nn,"config.txt")
