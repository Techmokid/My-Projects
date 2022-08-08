import time

ReactorInternalSize = "5x3x4"

cols = int(ReactorInternalSize.split("x")[0])
rows = int(ReactorInternalSize.split("x")[1])
dpth = int(ReactorInternalSize.split("x")[2])
reactorData = [[[0 for k in range(dpth)] for j in range(rows)] for i in range(cols)]

for x in reactorData:
    print(x)
    print()


def NearbyBlocks(x,y,z):
    if (x < 0):
        raise Exception("Invalid block position!")
    if (y < 0):
        raise Exception("Invalid block position!")
    if (z < 0):
        raise Exception("Invalid block position!")
    if (x >= cols):
        raise Exception("Invalid block position!")
    if (y >= rows):
        raise Exception("Invalid block position!")
    if (z >= dpth):
        raise Exception("Invalid block position!")
    
    NearbyBlocks = []
    if (x == 0):
        NearbyBlocks.append("Reactor Casing")
    else:
        NearbyBlocks.append(reactorData[x-1][y][z])
    if (y == 0):
        NearbyBlocks.append("Reactor Casing")
    else:
        NearbyBlocks.append(reactorData[x][y-1][z])
    if (z == 0):
        NearbyBlocks.append("Reactor Casing")
    else:
        NearbyBlocks.append(reactorData[x][y][z-1])
    
    if (x == cols - 1):
        NearbyBlocks.append("Reactor Casing")
    else:
        NearbyBlocks.append(reactorData[x+1][y][z])
    if (y == rows - 1):
        NearbyBlocks.append("Reactor Casing")
    else:
        NearbyBlocks.append(reactorData[x][y+1][z])
    if (z == dpth - 1):
        NearbyBlocks.append("Reactor Casing")
    else:
        NearbyBlocks.append(reactorData[x][y][z+1])
    return NearbyBlocks

def AxisBlocks(x,y,z):
    NearbyBlocks = []
    for i in range (0,cols):
        if (i != x):
            NearbyBlocks.append(reactorData[i][y][z])
    for i in range (0,rows):
        if (i != y):
            NearbyBlocks.append(reactorData[x][i][z])
    for i in range (0,dpth):
        if (i != z):
            NearbyBlocks.append(reactorData[x][y][i])
    return NearbyBlocks

def CoolerCount2(x,y,z,cooler):
    nearbyBlocks = NearbyBlocks(x,y,z)
    CoolerCount(cooler,nearbyBlocks)

def CoolerCount(cooler,nearbyBlocks):
    result = 0
    for i in nearbyBlocks:
        if (i == cooler):
            result += 1
    return result

def ConvertPassiveModeratorCells():
    for x in range(0,cols):
        for y in range(0,rows):
            for z in range(0,dpth):
                if (reactorData[x][y][z] == "Passive Moderator"):
                    for i in NearbyBlocks(x,y,z):
                        if (i == "Reactor Cell"):
                            reactorData[x][y][z] = "Active Moderator"

def IsReactorValid():
    ConvertPassiveModeratorCells()
    
    for x in range(0,cols):
        for y in range(0,rows):
            for z in range(0,dpth):
                nearbyBlocks = NearbyBlocks(x,y,z)
                if (reactorData[x][y][z] == "Water Cooler"):
                    if ((CoolerCount("Reactor Cell",nearbyBlocks) < 1) and (CoolerCount("Active Moderator",nearbyBlocks) < 1)):
                        return False
                elif (reactorData[x][y][z] == "Redstone Cooler"):
                    if (CoolerCount("Reactor Cell",nearbyBlocks) < 1):
                        return False
                elif (reactorData[x][y][z] == "Quartz Cooler"):
                    if (CoolerCount("Active Moderator",nearbyBlocks) < 1):
                        return False
                elif (reactorData[x][y][z] == "Gold Cooler"):
                    if ((CoolerCount("Water Cooler",nearbyBlocks) == 0) or (CoolerCount("Redstone Cooler",nearbyBlocks) == 0)):
                        return False
                elif (reactorData[x][y][z] == "Glowstone Cooler"):
                    if (CoolerCount("Active Moderator",nearbyBlocks) < 2):
                        return False
                elif (reactorData[x][y][z] == "Lapis Cooler"):
                    if ((CoolerCount("Reactor Cell",nearbyBlocks) < 1) or (CoolerCount("Reactor Casing",nearbyBlocks) < 1)):
                        return False
                elif (reactorData[x][y][z] == "Diamond Cooler"):
                    if ((CoolerCount("Water Cooler",nearbyBlocks) < 1) or (CoolerCount("Quartz Cooler",nearbyBlocks) < 1)):
                        return False
                elif (reactorData[x][y][z] == "Liquid Helium Cooler"):
                    if ((not (CoolerCount("Redstone Cooler",nearbyBlocks) == 1)) or (CoolerCount("Reactor Casing",nearbyBlocks) < 1)):
                        return False
                elif (reactorData[x][y][z] == "Enderium Cooler"):
                    if (CoolerCount("Reactor Casing",nearbyBlocks) != 3):
                        return False
                elif (reactorData[x][y][z] == "Cryotheum Cooler"):
                    if (CoolerCount("Reactor Cell",nearbyBlocks) < 2):
                        return False
                elif (reactorData[x][y][z] == "Iron Cooler"):
                    if (CoolerCount("Gold Cooler",nearbyBlocks) < 1):
                        return False
                elif (reactorData[x][y][z] == "Emerald Cooler"):
                    if ((CoolerCount("Active Moderator",nearbyBlocks) < 1) or (CoolerCount("Reactor Cell",nearbyBlocks) < 1)):
                        return False
                elif (reactorData[x][y][z] == "Copper Cooler"):
                    if (CoolerCount("Glowstone Cooler",nearbyBlocks) < 1):
                        return False
                elif (reactorData[x][y][z] == "Copper Cooler"):
                    if (CoolerCount("Glowstone Cooler",nearbyBlocks) < 1):
                        return False
                elif (reactorData[x][y][z] == "Tin Cooler"):
                    if (CoolerCount("Lapis Cooler",AxisBlocks(x,y,z)) < 2):
                        return False
                elif (reactorData[x][y][z] == "Magnesium Cooler"):
                    if ((CoolerCount("Active Moderator",nearbyBlocks) < 1) or (CoolerCount("Reactor Casing",nearbyBlocks) < 1)):
                        return False
    return True

def GetReactorSpecs(FuelBasePower,FuelBaseHeat):
    #Calculate cooling
    deltaHeat = 0
    for x in range(0,cols):
        for y in range(0,rows):
            for z in range(0,dpth):
                if (reactorData[x][y][z] == "Water Cooler"):
                    deltaHeat -= 60
                elif (reactorData[x][y][z] == "Redstone Cooler"):
                    deltaHeat -= 90
                elif (reactorData[x][y][z] == "Quartz Cooler"):
                    deltaHeat -= 90
                elif (reactorData[x][y][z] == "Gold Cooler"):
                    deltaHeat -= 120
                elif (reactorData[x][y][z] == "Glowstone Cooler"):
                    deltaHeat -= 130
                elif (reactorData[x][y][z] == "Lapis Cooler"):
                    deltaHeat -= 120
                elif (reactorData[x][y][z] == "Diamond Cooler"):
                    deltaHeat -= 150
                elif (reactorData[x][y][z] == "Liquid Helium Cooler"):
                    deltaHeat -= 140
                elif (reactorData[x][y][z] == "Enderium Cooler"):
                    deltaHeat -= 120
                elif (reactorData[x][y][z] == "Cryotheum Cooler"):
                    deltaHeat -= 160
                elif (reactorData[x][y][z] == "Iron Cooler"):
                    deltaHeat -= 80
                elif (reactorData[x][y][z] == "Emerald Cooler"):
                    deltaHeat -= 160
                elif (reactorData[x][y][z] == "Copper Cooler"):
                    deltaHeat -= 80
                elif (reactorData[x][y][z] == "Tin Cooler"):
                    deltaHeat -= 120
                elif (reactorData[x][y][z] == "Magnesium Cooler"):
                    deltaHeat -= 110

    #Calculate heating
    efficiency = 100
    reactorCells = 0
    for x in range(0,cols):
        for y in range(0,rows):
            for z in range(0,dpth):
                nearbyBlocks = NearbyBlocks(x,y,z)
                nearbyReactorCells = CoolerCount("Reactor Cell",nearbyBlocks)
                nearbyReactorModerators = CoolerCount("Active Moderator",nearbyBlocks)
                
                if (reactorData[x][y][z] == "Reactor Cell"):
                    reactorCells += 1
                    #TAKE INTO ACCOUNT EFFICIENCY BOOST WHEN REACTOR CELLS ARE ADJACENT!!!
    
    for x in range(0,cols):
        for y in range(0,rows):
            for z in range(0,dpth):
                if (reactorData[x][y][z] == "Active Moderator"):
                    continue
                #Calculate the efficiency boost from the moderators

    return [reactorData,deltaHeat,energyGenerated]
    
#print(reactorData)
reactorData[0][0][0] = "Enderium Cooler"
reactorData[4][0][0] = "Enderium Cooler"
reactorData[0][0][3] = "Enderium Cooler"
reactorData[4][0][3] = "Enderium Cooler"

print(IsReactorValid())

time.sleep(5)
print("Running total calculator")

allValidBlocks = ["Water Cooler", "Redstone Cooler", "Quartz Cooler", "Gold Cooler", "Glowstone Cooler", "Lapis Cooler", "Diamond Cooler", "Liquid Helium Cooler", "Enderium Cooler",
                  "Cryotheum Cooler", "Iron Cooler", "Emerald Cooler", "Copper Cooler", "Tin Cooler", "Magnesium Cooler", "Air", "Reactor Cell", "Passive Moderator"]


























