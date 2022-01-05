import math

#This is the variable storage for the simulation. Change these to whatever you want
priceOfGraphicsCard = 5000
priceOfRigExcludingGraphicsCard = 0
MoneyEarnedPerMinerPerDay = 29.00
numberOfPeopleInProject = 7

#These are some variables regarding power
IgnorePowerCost = False
PowerUsagePerGraphicsCardInKilowatts = 0.4
SolarCost = 4000
SolarPowerOutput = 5
AveragePowerCostPerKW = 0.2833

#These variables are for if we put some extra money into the project(E.g. $50 per week)
amountOfMoneyPutIntoProjectEachDayAsExtra = 0
amountOfMoneyPutIntoProjectEachWeekAsExtra = 0
amountOfMoneyPutIntoProjectEachMonthAsExtra = 0
amountOfMoneyPutIntoProjectEachYearAsExtra = 0

amountOfMoneyPerDayEachBeforeEndOfSimulation = 1000000

#This variable just outputs the data into a text file that should be easier to read
WriteToFile = True

#From this point is the actual simulation. Please try not to touch anything from here on
TotalInfo = ""
NumberOfSolarSetupsAtStart = 1
SolarPowerOutput = SolarPowerOutput * 8 / 3
numberOfMiners = 1
daysElapsed = 0
monthsElapsed = 0
yearsElapsed = 0
OurMoney = 0.00
MiningMoney = 0.00
totalMoney = 0.00
_20perDayValue = 0.00
_20perDaySet = False
_50perDayValue = 0.00
_50perDaySet = False
_100perDayValue = 0.00
_100perDaySet = False
_200perDayValue = 0.00
_200perDaySet = False
_500perDayValue = 0.00
_500perDaySet = False

def SimulateDay1():
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
    global NumberOfSolarSetupsAtStart
    global AveragePowerCostPerKW
    global _20perDayValue
    global _50perDayValue
    global _20perDaySet
    global _50perDaySet
    global _100perDayValue
    global _200perDayValue
    global _100perDaySet
    global _200perDaySet
    global _500perDayValue
    global _500perDaySet

    if ((_20perDaySet==False) & (numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject > 20)):
        _20perDaySet = True
        _20perDayValue = daysElapsed
    if ((_50perDaySet==False) & (numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject > 50)):
        _50perDaySet = True
        _50perDayValue = daysElapsed
    if ((_100perDaySet==False) & (numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject > 100)):
        _100perDaySet = True
        _100perDayValue = daysElapsed
    if ((_200perDaySet==False) & (numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject > 200)):
        _200perDaySet = True
        _200perDayValue = daysElapsed
    if ((_500perDaySet==False) & (numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject > 500)):
        _500perDaySet = True
        _500perDayValue = daysElapsed
        
    MiningMoney += amountOfMoneyPutIntoProjectEachDayAsExtra + amountOfMoneyPutIntoProjectEachWeekAsExtra/7 + amountOfMoneyPutIntoProjectEachMonthAsExtra/(30+1.25/3) + amountOfMoneyPutIntoProjectEachYearAsExtra/365.25
    
    totalMoney += MoneyEarnedPerMinerPerDay * numberOfMiners
    if (numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject > 50):
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
        if (NumberOfSolarSetupsAtStart * SolarPowerOutput * 0.07 < PowerUsagePerGraphicsCardInKilowatts * numberOfMiners * AveragePowerCostPerKW):
            if (MiningMoney >= SolarCost):
                MiningMoney -= SolarCost
                NumberOfSolarSetupsAtStart += 1
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
    SimulateDay1()
    moneyPerDayEach = numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject
    sentence = "Days Elapsed: " + str(daysElapsed) + "   " + "Yrs Elapsed: " + str(yearsElapsed) + "   " + "# Of Graphics Cards: " + str(numberOfMiners) + "   " + "$$ Each Person Earns Per Day: " + str(round(moneyPerDayEach, 2)) + "   " + "# Solar Setups: " + str(NumberOfSolarSetupsAtStart)
    TotalInfo += sentence + "\n"

print ("Calculations Complete")
if (WriteToFile):
    print ("Writing Simulation Data To Text File Now...")
    f = open("Bitcoin Mining Data.txt","w")
    f.write(TotalInfo)
    f.close()
    print ("Process Complete")

print("\n\n")
print("Important Information From Cost Comparison Simulation:")
print("\nYears until $20 per day each: " + str(_20perDayValue/365.25))
print("Years until $50 per day each: " + str(_50perDayValue/365.25))
print("Years until $100 per day each: " + str(_100perDayValue/365.25))
print("Years until $200 per day each: " + str(_200perDayValue/365.25))
print("Years until $500 per day each: " + str(_500perDayValue/365.25))
print("Years until $1000 per day each: " + str(daysElapsed/365.25))
