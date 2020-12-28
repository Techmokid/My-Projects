import coinbase_handler as cbh
import neat,os,time

local_dir = os.path.dirname(__file__)
config_path = os.path.join(local_dir, "config-feedforward.txt")
AIData = cbh.getBaseAIData()

#Access using "coinbaseData[0].price"
coinbaseData = cbh.getPreviousPricesList()
with open("Fitness Monitor.txt","w+") as f:
    f.write("")

#Start of AI code
numberOfGenerations = 1
def RunAIs(genomes, config):
    global numberOfGenerations
    print("Training Generation: " + str(numberOfGenerations))
    start_time = time.time()
    numberOfGenerations += 1
    
    nets = []
    ge = []

    for _,g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g,config)
        nets.append(net)
        ge.append(g)
        g.fitness = 0
    
    #Here we have the entire AI structure network. Just iterate over all the different structures in the network
    maxFitness = -100000
    testCoinbaseData = cbh.getPreviousPricesList(True)
    for indexCounter,genome in enumerate(ge):
        currentNet = nets[indexCounter]
        
        #For each genome, simply run the wallet calculations
        #ge[x].fitness = calculateOverallFitness(ge[x])
        
        exampleWallet = 500
        exampleShares = 0
        for baseIndex in range(0,len(testCoinbaseData) - AIData.inputs_count):
            temp = []
            for currentPosition in range(0,AIData.inputs_count):
                temp.append(float(testCoinbaseData[baseIndex + currentPosition].price))
            neat_outputs = currentNet.activate(temp)
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
        genome.fitness = exampleWallet
        if (exampleWallet > maxFitness):
            maxFitness = exampleWallet
    print(" - Best fitness: " + str(maxFitness))
    with open("Fitness Monitor.txt","a+") as f:
        f.write(str(maxFitness) + "\n")
    print(" - Training Time:  " + str(time.time() - start_time) + "\n")

print("NEAT AI: Configuring NEAT AI file data...")
config = neat.config.Config(
    neat.DefaultGenome,
    neat.DefaultReproduction,
    neat.DefaultSpeciesSet,
    neat.DefaultStagnation,
    config_path)
    
p = neat.Population(config)

stats = neat.StatisticsReporter()
p.add_reporter(stats)

print("NEAT AI: Running simulation...\n")
winner = p.run(RunAIs,1000)
print("NEAT AI: Simulation complete!\n\n\n")

print(winner)

with open("Best Network.txt","w+") as f:
    f.write(str(winner))
