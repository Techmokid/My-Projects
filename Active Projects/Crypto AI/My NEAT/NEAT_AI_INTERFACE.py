import random,math,copy,time

class node():
    def __init__(self,nodeType):
        self.node_type = nodeType
        self.connected_nodes = []
        self.connection_weights = []
        self.node_input = -1000
        self.node_bias = random.random()

    def getNodeOutput(self,nodeManager):
        if (self in nodeManager):
            return -1000
        nodeManager.append(self)
        
        if (self.node_type == "input"):
            return self.node_input
        
        result = 0
        loops = 0
        for i in self.connected_nodes:
            result += self.connected_nodes[loops].getNodeOutput(nodeManager) * self.connection_weights[loops] + self.node_bias
            loops += 1
        return math.tanh(2*result)

    def setNodeInput(self,x):
        self.node_input = x

class genome():
    def __init__(self):
        self.fitness = 0
        self.generationsSurvived = 0
        self.clearGenomeData()

    def clearGenomeData(self):
        self.genome = []
    
    def generateNewRandomGenome(self,inputs,outputs,hidden,connections):
        self.clearGenomeData()
        
        for i in range(0,inputs):
            temp = node("input")
            self.genome.append(temp)
        
        for i in range(0,outputs):
            temp = node("output")
            self.genome.append(temp)
        
        for i in range(0,hidden):
            temp = node("hidden")
            self.genome.append(temp)
        
        for i in range(0,connections):
            #Now here's the random part. In here we connect a bunch of nodes randomly and simply ask if the structure is stable
            index_1 = random.randint(0,len(self.genome)-1)
            index_2 = random.randint(0,len(self.genome)-1)
            while (index_1 == index_2):
                index_2 = random.randint(0,len(self.genome)-1)

            #Now we have our 2 indexes. Simply connect them
            
            testGenome = copy.deepcopy(self)
            test_node_1 = testGenome.genome[index_1]
            test_node_2 = testGenome.genome[index_2]
            test_node_1.connected_nodes.append(test_node_2)
            test_node_1.connection_weights.append(random.random())
            if (testGenome.isGenomeStable()):
                self.genome = testGenome.genome
            else:
                testGenome = copy.deepcopy(self)
                test_node_1 = testGenome.genome[index_2]
                test_node_2 = testGenome.genome[index_1]
                test_node_1.connected_nodes.append(test_node_2)
                test_node_1.connection_weights.append(random.random())
                if (testGenome.isGenomeStable()):
                    self.genome = testGenome.genome
                else:
                    print("Error")

    def getInputNodes(self):
        result = []
        for i in self.genome:
            if (i.node_type == "input"):
                result.append(i)
        return result

    def getOutputNodes(self):
        result = []
        for i in self.genome:
            if (i.node_type == "output"):
                result.append(i)
        return result

    def getOutput(self,inputValues):
        if (len(inputValues) != len(self.getInputNodes())):
            raise Exception("Number Of Supplied Inputs Does Not Match AI Configuration!")
        
        for index,node_object in enumerate(self.getInputNodes()):
            node_object.setNodeInput(inputValues[index])
        
        result = []
        for index,node_object in enumerate(self.getOutputNodes()):
            result.append(node_object.getNodeOutput([]))
        return result

    def isGenomeStable(self):
        for i in self.getOutputNodes():
            if(i.getNodeOutput([]) == -1000):
                return False
        return True

    def getHiddenNodes(self):
        result = []
        for i in self.genome:
            if ((i.node_type != "input") and (i.node_type != "output")):
                result.append(i)
        return result

class network():
    def __init__(self,configPath,updateValuesRealtime=True,printTrainingTimes=False):
        self.liveConfigUpdate(configPath)

        self.printTrainingTimes = printTrainingTimes
        self.previousValidGenomes = []
        self.generateNewRandomNetwork()

        print("NEAT AI: Population size set to " + str(self.pop_size))
        print("NEAT AI: Input count " + str(self.num_inputs))
        print("NEAT AI: Output count " + str(self.num_outputs))

    def liveConfigUpdate(self,configPath):
        #NEAT
        self.fitness_criterion =   self.getConfigValue(configPath,"fitness_criterion")          #
        self.pop_size =            int(self.getConfigValue(configPath,"pop_size"))              #
        
        #Node Bias
        self.bias_max_value =      float(self.getConfigValue(configPath,"bias_max_value"))      #
        self.bias_min_value =      float(self.getConfigValue(configPath,"bias_min_value"))      #
        self.bias_mutate_rate =    float(self.getConfigValue(configPath,"bias_mutate_rate"))    #
        
        #Connection Rates
        self.conn_add_prob =       float(self.getConfigValue(configPath,"conn_add_prob"))       #
        self.conn_delete_prob =    float(self.getConfigValue(configPath,"conn_delete_prob"))    #

        #Node Rates
        self.node_add_prob =       float(self.getConfigValue(configPath,"node_add_prob"))       #
        self.node_delete_prob =    float(self.getConfigValue(configPath,"node_delete_prob"))    #

        #Network Parameters
        self.num_inputs =          int(self.getConfigValue(configPath,"num_inputs"))            #
        self.num_outputs =         int(self.getConfigValue(configPath,"num_outputs"))           #
        self.num_hidden =          int(self.getConfigValue(configPath,"num_hidden"))            #
        self.num_connections =     int(self.getConfigValue(configPath,"num_connections"))       #
        
        #Connection Weight
        self.weight_mutate_prob =  float(self.getConfigValue(configPath,"weight_mutate_prob"))  #
        self.weight_replace_prob = float(self.getConfigValue(configPath,"weight_replace_prob")) #
        
        #Default Reproduction
        self.survival_threshold =  float(self.getConfigValue(configPath,"survival_threshold"))  #
        self.minimum_network_size = int(self.getConfigValue(configPath,"minimum_network_size")) #
    
    def getConfigValue(self, path, key):
        with open(path) as f:
            for line in f.readlines():
                if (key in line):
                    return line.replace(' ','').replace('\t','').replace('\n','').split('=')[1]

    def generateNewRandomNetwork(self):
        #Initialization Functions
        self.genomes = []
        for i in range(0,self.pop_size):
            temp = genome()
            temp.generateNewRandomGenome(self.num_inputs,self.num_outputs,self.num_hidden,self.num_connections)
            self.genomes.append(temp)

    def getMutatedGenomeCopy(self,orig): #WIP!!!
        #Remember, the input value "result" is a "genome()" object
        #result.genome gives the list of nodes
        result = copy.deepcopy(orig)
        
        if (random.random() > self.conn_add_prob):
            #Add connection
            index_1 = random.randint(0, len(result.genome) - 1)
            index_2 = random.randint(0, len(result.genome) - 1)
            while(index_1 == index_2):
                index_2 = random.randint(0, len(result.genome) - 1)
            
            temp = copy.deepcopy(result)
            node_1 = temp.genome[index_1]
            node_2 = temp.genome[index_2]
            node_1.connected_nodes.append(node_2)
            node_1.connection_weights.append(random.random())
            
            if (temp.isGenomeStable() == False):
                temp = copy.deepcopy(result)
                node_2.connected_nodes.append(node_1)
                node_2.connection_weights.append(random.random())
            if (temp.isGenomeStable()):
                result = temp
        if (random.random() > self.conn_delete_prob):
            #Remove connection
            if (len(result.genome) != 0):
                index = random.randint(0, len(result.genome) - 1)
                while(result.genome[index].node_type == "input"):
                    index = random.randint(0, len(result.genome) - 1)

                if (len(result.genome[index].connected_nodes) != 0):
                    index_2 = random.randint(0, len(result.genome[index].connected_nodes))
                    result.genome[index].connected_nodes.pop(index_2-1)
                    result.genome[index].connection_weights.pop(index_2-1)
        if (random.random() > self.node_add_prob):
            #Add node
            temp = node("hidden")
            result.genome.append(temp)
        if ((random.random() > self.node_delete_prob) and (len(result.getHiddenNodes()) != 0)):
            #Remove node
            if (len(result.genome) != 0):
                index = random.randint(0, len(result.genome) - 1)
                while((result.genome[index].node_type == "input") or (result.genome[index].node_type == "output")):
                    index = random.randint(0, len(result.genome) - 1)

                result.genome.pop(index)
        if (random.random() > self.weight_mutate_prob):
            #Alter a random weight
            if (len(result.genome) != 0):
                index = random.randint(0, len(result.genome) - 1)
                while(result.genome[index].node_type == "input"):
                    index = random.randint(0, len(result.genome) - 1)

                if (len(result.genome[index].connected_nodes) != 0):
                    index_2 = random.randint(0, len(result.genome[index].connected_nodes))
                    result.genome[index].connection_weights[index_2-1] = random.random()
        if (random.random() > self.weight_replace_prob):
            #Completely rework the weights
            if (len(result.genome) != 0):
                index = random.randint(0, len(result.genome) - 1)
                while(result.genome[index].node_type == "input"):
                    index = random.randint(0, len(result.genome) - 1)

                if (len(result.genome[index].connected_nodes) != 0):
                    looper = 0
                    while (looper < len(result.genome[index].connected_nodes)):
                        result.genome[index].connection_weights[looper] = random.random()
                        looper += 1
        if (random.random() > self.bias_mutate_rate):
            #Mutate a random nodes bias value
            if (len(result.genome) != 0):
                index = random.randint(0, len(result.genome) - 1)
                while(result.genome[index].node_type == "input"):
                    index = random.randint(0, len(result.genome) - 1)
                
                result.genome[index].node_bias += self.clamp(random.random()-0.5,self.bias_min_value,self.bias_max_value)
        if (random.random() > self.weight_replace_prob):
            #Mutate a random nodes bias value
            if (len(result.genome) != 0):
                index = random.randint(0, len(result.genome) - 1)
                while(result.genome[index].node_type == "input"):
                    index = random.randint(0, len(result.genome) - 1)
                
                result.genome[index].node_weight = random.uniform(self.bias_min_value,self.bias_max_value)
        if (result.isGenomeStable()):
            return result
        return self.getMutatedGenomeCopy(orig)
        #return orig

    def clamp(self,n, minn, maxn):
        return max(min(maxn, n), minn)

    def updateGenomeList(self,optionalSecondaryFitnessCalculator=None):
        startTime = time.time()
        # We now have the entire genome list ordered by fitness
        #  1 - Get the fitness list of all the genomes
        #  2 - Sort the genomes by fitness (Flip if we want minimums to win):
        #  3 - Perform the genetic death algorithms to wittle out poor performing genomes
        #  4 - Create mutated clones of winning genomes
        #  5 - Breed the winning genomes (NOT IMPLEMENTED)
        
        # Step 1
        fitnessesList = []
        genomesList = copy.deepcopy(self.genomes)
        for i in genomesList:
            fitnessesList.append(i.fitness)
        
        # Step 2
        keydict = dict(zip(genomesList,fitnessesList))
        genomesList.sort(key=keydict.get)
        
        if(self.fitness_criterion == "min"):
            genomesList.reverse()
        elif(self.fitness_criterion != "max"):
            raise Exception("Invalid Fitness Criterion In Configuration File!")
        
        if (optionalSecondaryFitnessCalculator != None):
            genomesList = optionalSecondaryFitnessCalculator(genomesList)
        
        # Step 3
        looper = 0
        temp = copy.deepcopy(genomesList)
        genomesList = []
        s_t = self.survival_threshold
        p_s = self.pop_size
        for i in temp:
            survivalThreshold = (1-s_t)*math.pow(math.sin((math.pi/2)*(looper/p_s)),2) + s_t
            if (random.random() < survivalThreshold):
                genomesList.append(i)
            elif (i.generationsSurvived > 5):
                i.generationsSurvived -= 5
                genomesList.append(i)
            looper += 1
        
        # Step 4
        #requiredMutatedGenomes_split = int(p_s - len(genomesList))
        if (len(genomesList) != 0):
            if (len(genomesList) > self.minimum_network_size):
                print("NEAT AI: Number of surviving genomes:",len(genomesList))
                while (len(genomesList) != p_s):
                    i = random.choice(genomesList)
                    genomesList.append(self.getMutatedGenomeCopy(i))
                self.genomes = genomesList
            elif(len(self.previousValidGenomes) > self.minimum_network_size):
                print("NEAT AI: Rebooting genome from previous success attempts")
                genomesList = copy.deepcopy(self.previousValidGenomes)
                while (len(genomesList) != p_s):
                    i = random.choice(genomesList)
                    genomesList.append(self.getMutatedGenomeCopy(i))
                self.genomes = genomesList
            elif(len(self.previousValidGenomes) + len(genomesList) > self.minimum_network_size):
                for i in self.previousValidGenomes:
                    genomesList.append(i)
                print("NEAT AI: Rebooting genome from previous success attempts appended to current network data")
                while (len(genomesList) != p_s):
                    i = random.choice(genomesList)
                    genomesList.append(self.getMutatedGenomeCopy(i))
                self.genomes = genomesList
            else:
                if (len(genomesList) == 1):
                    print("NEAT AI: Discovered functional node. Storing node for later...")
                else:
                    print("NEAT AI: Discovered functional nodes. Storing",len(genomesList),"nodes for later...")
                for i in genomesList:
                    self.previousValidGenomes.append(i)
        else:
            print("NEAT AI: Complete extinction event, regenerating network!")
            self.generateNewRandomNetwork()
        
        if (self.printTrainingTimes):
            print("NEAT AI: Generation Learning Time: " + str(int((time.time() - startTime)*1000)/1000) + "s")
            print(" - Number of genomes: " + str(len(genomesList)))
