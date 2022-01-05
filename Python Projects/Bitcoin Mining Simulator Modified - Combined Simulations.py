import math

#This is the variable storage for the simulation. Change these to whatever you want
priceOfGraphicsCard = 889
priceOfRigExcludingGraphicsCard = 0
MoneyEarnedPerMinerPerDay = 25.90
numberOfPeopleInProject = 6

#These are some variables regarding power
IgnorePowerCost = False
PowerUsagePerGraphicsCardInKilowatts = 3.5
SolarCost = 8000
SolarPowerOutput = 6.615
AveragePowerCostPerKW = 0.3

#These variables are for if we put some extra money into the project(E.g. $50 per week)
amountOfMoneyPutIntoProjectEachDayAsExtra = 0
amountOfMoneyPutIntoProjectEachWeekAsExtra = 0
amountOfMoneyPutIntoProjectEachMonthAsExtra = 0
amountOfMoneyPutIntoProjectEachYearAsExtra = 0
amountOfMoneyPerDayEachBeforeEndOfSimulation = 1000

#This variable just outputs the data into a text file that should be easier to read
WriteToFile = True

#This is for already existant bitcoin miners
avalon6 = False
AntminerS5 = False
AntminerS7 = False
AntminerS9 = False
BaikalGiantB = False
BaikalGiantN = False

#From this point is the actual simulation. Please try not to touch anything from here on
TotalInfo = ""
NumberOfSolarSetupsAtStart = 1
SolarPowerOutput = SolarPowerOutput * 8
PowerUsagePerGraphicsCardInKilowatts = PowerUsagePerGraphicsCardInKilowatts * 24
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

if (avalon6):
    PowerUsagePerGraphicsCardInKilowatts = 1.1
    priceOfRigExcludingGraphicsCard = 60
elif (AntminerS5):
    PowerUsagePerGraphicsCardInKilowatts = 0.59
    priceOfRigExcludingGraphicsCard = 0
elif (AntminerS7):
    PowerUsagePerGraphicsCardInKilowatts = 1.3
    priceOfRigExcludingGraphicsCard = 0
elif (AntminerS9):
    PowerUsagePerGraphicsCardInKilowatts = 1.35
    priceOfRigExcludingGraphicsCard = 0
elif (BaikalGiantB):
    PowerUsagePerGraphicsCardInKilowatts = 0.4
    priceOfRigExcludingGraphicsCard = 0
elif (BaikalGiantN):
    PowerUsagePerGraphicsCardInKilowatts = 0.06
    priceOfRigExcludingGraphicsCard = 0

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

def SimulateDay2():
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
        if (NumberOfSolarSetupsAtStart * SolarPowerOutput < PowerUsagePerGraphicsCardInKilowatts * numberOfMiners):
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
    sentence = "Days Elapsed: " + str(daysElapsed) + "   " + "Yrs Elapsed: " + str(yearsElapsed) + "   " + "Number of Solar Setups: " + str(numberOfMiners) + "   " + "Money Earned Per Day Each: " + str(round(moneyPerDayEach, 2))
    TotalInfo += "\t" + sentence + "\n"

print ("Calculations Complete")
if (WriteToFile):
    print ("Writing Simulation Data To Text File Now...")
    f = open("Bitcoin Mining Data.txt","w+")
    f.write("ON-GRID:\n")
    f.write(TotalInfo)
    f.close()
    print ("Process Complete")

print("\n\n\n\n")
print("Important Information From Cost Comparison Simulation (On-Grid):")
print("\nYears until $20/day each:   \t" + str(round(_20perDayValue/365.25,2)))
print("Years until $50/day each:   \t" + str(round(_50perDayValue/365.25,2)))
print("Years until $100/day each:  \t" + str(round(_100perDayValue/365.25,2)))
print("Years until $200/day each:  \t" + str(round(_200perDayValue/365.25,2)))
print("Years until $500/day each:  \t" + str(round(_500perDayValue/365.25,2)))
print("Years until $1000/day each: \t" + str(round(daysElapsed/365.25,2)))
print("\nTime to completion: " + str(round(daysElapsed/365.25 - 0.5)) + " years, " + str(round((daysElapsed/365.25 - round(daysElapsed/365.25 - 0.5))*12 - 0.5)) + " months, " + str(round(((daysElapsed/365.25 - round(daysElapsed/365.25 - 0.5))*12 - round((daysElapsed/365.25 - round(daysElapsed/365.25 - 0.5))*12 - 0.5))*30)) + " days")

NumberOfSolarSetupsAtStart = 1
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
TotalInfo = ""

while (numberOfMiners < amountOfMoneyPerDayEachBeforeEndOfSimulation * numberOfPeopleInProject / MoneyEarnedPerMinerPerDay):
    SimulateDay2()
    moneyPerDayEach = numberOfMiners * MoneyEarnedPerMinerPerDay / numberOfPeopleInProject
    sentence = "Days Elapsed: " + str(daysElapsed) + "   " + "Yrs Elapsed: " + str(yearsElapsed) + "   " + "Number of Solar Setups: " + str(numberOfMiners) + "   " + "$$ Each Person Earns Per Day: " + str(round(moneyPerDayEach, 2)) + "   " + "# Solar Setups: " + str(NumberOfSolarSetupsAtStart)
    TotalInfo += "\t" + sentence + "\n"

print ("Calculations Complete")
if (WriteToFile):
    print ("Writing Simulation Data To Text File Now...")
    f = open("Bitcoin Mining Data.txt","a")
    f.write("\n\n\nOFF-GRID:\n")
    f.write(TotalInfo)
    f.close()
    print ("Process Complete")

print("\n\n\n\n")
print("Important Information From Power Comparison Simulation (Off-Grid):")
print("\nYears until $20/day each:   \t" + str(round(_20perDayValue/365.25,2)))
print("Years until $50/day each:   \t" + str(round(_50perDayValue/365.25,2)))
print("Years until $100/day each:  \t" + str(round(_100perDayValue/365.25,2)))
print("Years until $200/day each:  \t" + str(round(_200perDayValue/365.25,2)))
print("Years until $500/day each:  \t" + str(round(_500perDayValue/365.25,2)))
print("Years until $1000/day each: \t" + str(round(daysElapsed/365.25,2)))
print("\nTime to completion: " + str(round(daysElapsed/365.25 - 0.5)) + " years, " + str(round((daysElapsed/365.25 - round(daysElapsed/365.25 - 0.5))*12 - 0.5)) + " months, " + str(round(((daysElapsed/365.25 - round(daysElapsed/365.25 - 0.5))*12 - round((daysElapsed/365.25 - round(daysElapsed/365.25 - 0.5))*12 - 0.5))*30)) + " days")
