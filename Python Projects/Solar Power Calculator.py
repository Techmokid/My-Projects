def endScript():
    var = input("Press Enter To Quit")
    quit()

print("\n\n\tSolar Calculator!\n")
PowerUsagePerDay = int(input("What is your monthly power usage? ")) * 12 / 365.25
PowerGenerationPerDay = int(input("How much power per hour does the solar setup generate? E.G. Is it a 2.2KW system? If so, type in 2.2: ")) * 8.00
CostOfPowerPerDay = int(input("What is your monthly power costs? ")) * 12 / 365.25
CostOfTheSolarPanelSetup = int(input("How much does your solar setup cost? "))

CostOfPowerPerkW = CostOfPowerPerDay / PowerUsagePerDay
MoneySavedPerDay = 0
ResultantElectricityBill = 0
YearsToSelfPay = 0
LeftOverPowerPerDay = 0
MoneyEarnedExtra = 0

if (PowerUsagePerDay > PowerGenerationPerDay):
    MoneySavedPerDay = CostOfPowerPerkW * PowerGenerationPerDay
    ResultantElectricityBill = (CostOfPowerPerkW * PowerUsagePerDay) - MoneySavedPerDay
    YearsToSelfPay = CostOfTheSolarPanelSetup / MoneySavedPerDay
else:
    LeftOverPowerPerDay = PowerUsagePerDay - PowerGenerationPerDay
    MoneySavedPerDay = PowerUsagePerDay * CostOfPowerPerkW
    MoneyEarnedExtra = LeftOverPowerPerDay * CostOfPowerPerDay
    YearsToSelfPay = CostOfTheSolarPanelSetup / (MoneySavedPerDay + MoneyEarnedExtra)

TotalSavedMoneyAfter5Years = 5 * MoneySavedPerDay * 365.25 - CostOfTheSolarPanelSetup
profitable = False
if (5 * MoneySavedPerDay * 365.25 - CostOfTheSolarPanelSetup > 0):
    profitable = True

print("Calculations Complete!")

if (!profitable):
    print("Unfortunately, this solar setup is not profitable for your household and will only result in money being lost overall, not saved")
    print("After the cost of solar panels after 5 years, you will be losing $" + TotalSavedMoneyAfter5Years + " overall")
else:
    print("This solar setup is profitable and will save you money!!!")
    var = MoneySavedPerDay * 365.25
    print("You will be saving $" + var + " per year on average, and after the cost of solar panels after 5 years, you will be saving a grand total of $" + TotalSavedMoneyAfter5Years + " every 5 years!")
    print("It will take " + YearsToSelfPay + " years for the solar setup to pay for itself!")
    
endScript()

