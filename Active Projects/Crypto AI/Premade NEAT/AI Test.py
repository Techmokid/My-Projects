import neat,random,os,time

local_dir = os.path.dirname(__file__)
config_path = os.path.join(local_dir, "config-feedforward.txt")

def Update(genomes, config):
    print("Generation...")
    
    nets = []
    ge = []

    for _,g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g,config)
        nets.append(net)
        ge.append(g)
        g.fitness = 0
    
    for x,g in enumerate(ge):
        result = []
        for x in range(0,100):
            result.append(0)
        neat_outputs = nets[x].activate(result)
        g.fitness = neat_outputs[0]
            
config = neat.config.Config(
    neat.DefaultGenome,
    neat.DefaultReproduction,
    neat.DefaultSpeciesSet,
    neat.DefaultStagnation,
    config_path)
    
p = neat.Population(config)
    
#p.add_reporter(neat.StdOutReporter(False))
stats = neat.StatisticsReporter()
p.add_reporter(stats)

winner = p.run(Update,100)
print(winner)
