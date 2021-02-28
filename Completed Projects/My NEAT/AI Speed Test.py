import NEAT_AI_INTERFACE as naii
import time

nn = naii.network("config.txt")

startTime = time.time()
nn.genomes[0].fitness = 0
print(len(nn.genomes))
nn.updateGenomeList()
print(time.time() - startTime)
