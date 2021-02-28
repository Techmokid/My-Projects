from matplotlib import pyplot as plt
#import coinbase_handler as cbh

loopers = 0
listOfPrices = []
listOfPositions = []
#for i in cbh.getPreviousPricesList(True):
#    loopers += 1
#    listOfPrices.append(float(i.price))
#    listOfPositions.append(float(loopers))
with open("Fitness Monitor.txt") as f:
    for i in f.readlines():
        loopers += 1
        listOfPrices.append(float(i))
        listOfPositions.append(float(loopers))

plt.figure()
plt.title("Historic Crypto Values")
plt.xlabel("Generation")
plt.ylabel("Price")
plt.plot(listOfPositions,listOfPrices)
plt.show()
