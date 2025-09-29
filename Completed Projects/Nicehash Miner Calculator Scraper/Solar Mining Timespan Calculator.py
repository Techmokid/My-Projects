import math
from datetime import datetime, timedelta

# Device Parameters
DeviceCost               = 5000                      # How much does your full crypto miner cost? Be that an ASIC unit, or a full tower PC with a graphics card. Just the total cost of the rig
DeviceEarningsPerDay     = 30                        # According to "https://www.nicehash.com/profitability-calculator", how much your rig will earn per day on average
DevicePowerUsageInKW     = 3                         # Just how many kilowatts of power your rig pulls
DeviceQuantity           = 1                         # How many rigs are we starting with? Just the one unit? Or do we have a few

# Solar Parameters
DoSolar                  = True                      # Are we using a solar array to make our power costs completely free? Or are we not doing that?
                                                     # If this is set to True,  "DeviceEarningsPerDay" above should be the "Income" value on the nicehash calculator
                                                     # If this is set to False, "DeviceEarningsPerDay" above should be the "Profit" value on the nicehash calculator
SolarUnitCost            = 9000                      # How much does the solar setup we're planning actually cost? Include all setup costs and everything
SolarPowerGenerationInKW = 9                         # How many kilowatts of power will the chosen solar setup generate on average?
                                                     # If unsure and it's a battery solar setup, take your solar capacity and divide by 3. E.g. a 6.6kw setup with batteries should be 2.2kW on average
SolarUnitQuantity        = math.ceil(DevicePowerUsageInKW/SolarPowerGenerationInKW)

# Other Parameters
startingCash             = 0                         # How much cash does this project start with? If not planning on taking out a loan, leave this as just zero
DaysForDeviceToArrive    = 30                        # When we buy a new crypto miner, how many days does it take to arrive from the factory?
DaysForSolarToArrive     = 60                        # When we purchase a new solar setup, how many days does it take to arrive and get setup ready?















# --------------------- BELOW THIS LINE IS THE ACTUAL SIMULATION ENVIRONMENT. DO NOT TOUCH UNDER HERE ------------------------
class Simulation:
    def __init__(self, params):
        self.DeviceCost                = params[0]
        self.DeviceEarningsPerDay      = params[1]
        self.DevicePowerUsageInKW      = params[2]
        self.DeviceQuantity            = params[3]
        self.SolarUnitCost             = params[4]
        self.SolarPowerGenerationInKW  = params[5]
        self.SolarUnitQuantity         = params[6]
        self.DoSolar                   = params[7]
        self.startingCash              = params[8]
        self.dayCounter                = 0
        self.changeOccurred            = True
        
        self.devicePurchaseDelayInDays = params[9]               # How many days after we put in an order does the devices appear at our house
        self.solarPurchaseDelayInDays  = params[10]               # How many days after we put in an order does the solar setups arrive and get installed
        self.devicePurchaseBacklog     = []
        self.solarPurchaseDelayBacklog  = []
    
    def TryPurchaseSmart(self):
        CurrentSolarGeneration = self.SolarPowerGenerationInKW * self.SolarUnitQuantity
        CurrentPowerDraw       = self.DevicePowerUsageInKW * self.DeviceQuantity
        if (CurrentPowerDraw + self.DevicePowerUsageInKW > CurrentSolarGeneration):
            if not self.TryPurchasingSolar():
                return False
        return self.TryPurchaseDevice()

    def TryPurchaseDevice(self):
        if self.startingCash >= self.DeviceCost:
            #self.DeviceQuantity += 1
            self.devicePurchaseBacklog.append(self.dayCounter + self.devicePurchaseDelayInDays)
            
            self.startingCash -= self.DeviceCost
            self.changeOccurred = True
            return True
        return False

    def TryPurchasingSolar(self):
        if self.startingCash >= self.SolarUnitCost:
            #self.SolarUnitQuantity += 1
            self.solarPurchaseDelayBacklog.append(self.dayCounter + self.solarPurchaseDelayInDays)
            
            self.startingCash -= self.SolarUnitCost
            self.changeOccurred = True
            return True
        return False

    def CheckPurchaseArrivals(self):
        for i in self.devicePurchaseBacklog[:]:  # ← the [:] makes a copy
            if self.dayCounter >= i:
                self.DeviceQuantity += 1
                self.devicePurchaseBacklog.remove(i)
                self.changeOccurred = True

        for i in self.solarPurchaseDelayBacklog[:]:  # ← the [:] makes a copy
            if self.dayCounter >= i:
                self.SolarUnitQuantity += 1
                self.solarPurchaseDelayBacklog.remove(i)
                self.changeOccurred = True
    
    def CalculateDay(self):
        self.CheckPurchaseArrivals()
        self.dayCounter += 1

        # Check solar capacity
        CurrentSolarGeneration = self.SolarPowerGenerationInKW * self.SolarUnitQuantity
        AvailableDevices       = min(self.DeviceQuantity, math.floor(CurrentSolarGeneration/self.DevicePowerUsageInKW)) # An exception for if devices arrive out of order with solar, overloading the solar capacity
        CurrentPowerDraw       = self.DevicePowerUsageInKW * AvailableDevices

        if not self.DoSolar:
            AvailableDevices = self.DeviceQuantity
        self.startingCash += self.DeviceEarningsPerDay * AvailableDevices
        
        if not self.DoSolar:
            self.TryPurchaseDevice()
            return 0
        
        while (self.startingCash > self.DeviceCost + self.SolarUnitCost):
            self.TryPurchaseSmart()
        self.TryPurchaseSmart()

        if (CurrentPowerDraw > CurrentSolarGeneration) and self.changeOccurred:
            print("WARNING: Solar generation overload! Cannot support this many devices at this time!\n")
        return self.DeviceQuantity - AvailableDevices

    def CalculateToYear(self, year):
        while ((self.dayCounter < 365 * year) and (self.DeviceEarningsPerDay*self.DeviceQuantity < 1000)):
            shedUnits = self.CalculateDay()
            
            if (self.changeOccurred):
                #msg  = "Total Days: " + str(self.dayCounter)
                #msg += "   Years: " + str(self.dayCounter // 365)
                #msg += "   Days: " + str(self.dayCounter % 365)
                msg = "[" + (datetime.now() + timedelta(days=self.dayCounter)).strftime("%d/%m/%Y") + "]"
                msg += "   Device #: " + str(self.DeviceQuantity)
                if self.DoSolar:
                    msg += "   Solar #: " + str(self.SolarUnitQuantity)
                msg += "   Profit/day: " + str(self.DeviceEarningsPerDay*self.DeviceQuantity)

                if self.DoSolar:
                    msg += "   Power Draw / Solar Gen: " + str(self.DevicePowerUsageInKW*self.DeviceQuantity) + " / "+ str(self.SolarPowerGenerationInKW*self.SolarUnitQuantity) + " kW"
                
                if (shedUnits > 0):
                    msg += "   Offline shed units: " + str(shedUnits)
                print(msg)
                
                self.changeOccurred = False

        print()
        if (self.dayCounter == 365 * year): # Simulation timed out
            print("Simulation environment timed out after the maximum number of years calculating. Max daily profit reached: $" + str(self.DeviceQuantity*self.DeviceEarningsPerDay))
        else: #Simulation reached max profit within timeframe
            print("Simulation environment reached $1000 daily / $7000 weekly / $30,000 monthly / $365,000 yearly within: " + str(round(self.dayCounter / 365,2)) + " years")

            future_date = datetime.now() + timedelta(days=self.dayCounter)
            print("If simulation example was started today, you would have this cash flowing in on approximately " + str(future_date.strftime("%d/%m/%Y")))
            

if DeviceEarningsPerDay <= 0:
    raise Exception("Device earnings cannot be negative or zero")

simulationParameters = [
    DeviceCost,
    DeviceEarningsPerDay,
    DevicePowerUsageInKW,
    DeviceQuantity,

    SolarUnitCost,
    SolarPowerGenerationInKW,
    SolarUnitQuantity,
    DoSolar,

    startingCash,
    DaysForDeviceToArrive,
    DaysForSolarToArrive
]

sim = Simulation(simulationParameters)
sim.CalculateToYear(10)

for i in range(5):
    print()
input("--- Press Enter to close window ---")
