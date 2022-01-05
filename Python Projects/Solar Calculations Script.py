def SolarProfit(SolarCost,PowerOutput,LifeTimeYears,CostPerKW=0.07):
    ProfitPerLifetime = PowerOutput * 8 * CostPerKW * 365.25 * LifeTimeYears
    return ProfitPerLifetime

def ProfitCostRatio(Profit,Cost):
    return Profit/Cost

print("Solar Profit: " + str(SolarProfit(4000,5,5)))
print("Profit To Cost Ratio: " + str(ProfitCostRatio(SolarProfit(4000,5,5),4000)))
