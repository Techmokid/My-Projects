import math

#This is the variable storage for the simulation. Change these to whatever you want
priceOfGraphicsCard = 389.00
priceOfRigExcludingGraphicsCard = 500.00
MoneyEarnedPerMinerPerDay = 1.70
numberOfPeopleInProject = 6
OurMoney = 0.00
MiningMoney = 0.00
totalMoney = 0.00
numberOfMiners = 1
daysElapsed = 0
monthsElapsed = 0
yearsElapsed = 0

#These are some variables regarding power
IgnorePowerCost = False
PowerUsagePerGraphicsCardInKilowatts = 0.15
SolarCost = 5500
SolarPowerOutput = 6.6
NumberOfSolarSetups = 1

#These variables are for if we put some extra money into the project(E.g. $50 per week)
amountOfMoneyPutIntoProjectEachDayAsExtra = 0
amountOfMoneyPutIntoProjectEachWeekAsExtra = 0
amountOfMoneyPutIntoProjectEachMonthAsExtra = 0
amountOfMoneyPutIntoProjectEachYearAsExtra = 0

amountOfMoneyPerDayEachBeforeEndOfSimulation = 1000

#This variable just outputs the data into a text file that should be easier to read
WriteToFile = False

#From this point is the actual simulation. Please try not to touch anything from here on
TotalInfo = ""
SolarPowerOutput = SolarPowerOutput / 3

def SimulateDay():
    global priceOfGraphicsCard
    global priceOfRigExcludingGraphicsCard
    global MoneyEarnedPerMinerPerDay
    global numberOfPeopleInProject
    global OurMoney
    global MiningMoney
    global totalMoney
    global numberOfMiners
    global daysElapsed
    global monthsElapsed
    global yearsElapsed
    global amountOfMoneyPutIntoProjectEachDayAsExtra
    global amountOfMoneyPutIntoProjectEachWeekAsExtra
    global amountOfMoneyPutIntoProjectEachMonthAsExtra
    global amountOfMoneyPutIntoProjectEachYearAsExtra
    global IgnorePowerCost
    global PowerUsagePerGraphicsCardInKilowatts
    global SolarCost
    global SolarPowerOutput
    global NumberOfSolarSetups
    
    MiningMoney += amountOfMoneyPutIntoProjectEachDayAsExtra + amountOfMoneyPutIntoProjectEachWeekAsExtra/7 + amountOfMoneyPutIntoProjectEachMonthAsExtra/(30+1.25/3) + amountOfMoneyPutIntoProjectEachYearAsExtra/365.25
    
    totalMoney += MoneyEarnedPerMinerPerDay * numberOfMiners
    if (yearsElapsed > 0):
        MiningMoney += totalMoney * 0.5
        OurMoney += totalMoney * 0.5
    else:
        MiningMoney += totalMoney;
    totalMoney = 0
    
    daysElapsed += 1
    monthsElapsed = math.floor(daysElapsed / (30 + 1.25 / 3))
    yearsElapsed = math.floor(daysElapsed / 365.25)

    if (IgnorePowerCost):
        if (numberOfMiners % 18 != 0):
            while (MiningMoney >= priceOfGraphicsCard):
                numberOfMiners += 1
                MiningMoney -= priceOfGraphicsCard
        else:
            while (MiningMoney >= (priceOfGraphicsCard + priceOfRigExcludingGraphicsCard)):
                numberOfMiners += 1
                MiningMoney -= (priceOfGraphicsCard + priceOfRigExcludingGraphicsCard)
    else:
        if (NumberOfSolarSetups * SolarPowerOutput < PowerUsagePerGraphicsCardInKilowatts * numberOfMiners):
            if (MiningMoney >= SolarCost):
                MiningMoney -= SolarCost
                NumberOfSolarSetups += 1
        else:
            if (numberOfMiners % 18 != 0):
                while (MiningMoney >= priceOfGraphicsCard):
                    numberOfMiners += 1
                    MiningMoney -= priceOfGraphicsCard
            else:
                while (MiningMoney >= (priceOfGraphicsCard + priceOfRigExcludingGraphicsCard)):
                    numberOfMiners += 1
                    MiningMoney -= (priceOfGraphicsCard + priceOfRigExcludingGraphicsCard)


print("Calculating... This might take a few moments")

while (numberOfMiners < amountOfMoneyPerDayEachBeforeEndOfSimulation * numberOfPeopleInProject / MoneyEarnedPerMinerPerDay):
    SimulateDay()
    moneyPerDayEach = numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject
    sentence = "Days Elapsed: " + str(daysElapsed) + "   " + "Yrs Elapsed: " + str(yearsElapsed) + "   " + "# Of Graphics Cards: " + str(numberOfMiners) + "   " + "$$ Each Person Earns Per Day: " + str(round(moneyPerDayEach, 2)) + "   " + "# Solar Setups: " + str(NumberOfSolarSetups)
    TotalInfo += sentence + "\n"

print ("Calculations Complete")
if (WriteToFile):
    print ("Writing Simulation Data To Text File Now...")
    f = open("Bitcoin Mining Data.txt","w")
    f.write(TotalInfo)
    f.close()
    print ("Process Complete")

print ("Displaying Simulation Data now...")
print(TotalInfo)
    
