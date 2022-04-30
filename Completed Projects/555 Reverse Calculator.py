import math

f = float(input("(1/2) Please enter the requested frequency (Hz): "))
d = float(input("(2/2) Please enter the requested duty cycle (%): "))

#capacitorList = [1E-7,6.8E-5,480*1E-6,.0039,.03,1.5E-7,7.2E-5,5E-4,.004,.031,.22*1E-6,7.5E-5,510*1E-6,4100*1E-6,.032,3.3E-7,8.2E-5,5.2E-4,.0042,.033,.47*1E-6,8.8E-5,5.4E-4,.0043,34E3*1E-6,.68*1E-6,100*1E-6,550*1E-6,.0046,.036,1E-6,1.08E-4,5.6E-4,.0047,.037,1.5E-6,120*1E-6,590*1E-6,.0048,.038,2E-6,1.24E-4,6.2E-4,.005,.039,2.2E-6,1.3E-4,6.45E-4,5100*1E-6,.04,3E-6,1.4E-4,6.5E-4,5400*1E-6,41E3*1E-6,3.3*1E-6,1.45E-4,680*1E-6,.0055,.047,4E-6,1.5E-4,7E-4,.0056,.048,4.7E-6,161*1E-6,7.08E-4,.0058,5E4*1E-6,5*1E-6,170*1E-6,
#	7.3E-4,.006,.055,5.6E-6,180*1E-6,800*1E-6,.0065,56E3*1E-6,6.8*1E-6,189*1E-6,8.2E-4,.0068,.06,7E-6,200*1E-6,8.5E-4,.0072,.062,8E-6,210*1E-6,8.6E-4,7400*1E-6,.066,8.2E-6,2.16E-4,.001,.0076,68E3*1E-6,10*1E-6,220*1E-6,1100*1E-6,.0078,.076,1.2E-5,230*1E-6,.0012,8200*1E-6,.1,15*1E-6,2.33E-4,.0013,.0083,.11,1.6E-5,240*1E-6,.0014,.0084,.12,1.8E-5,2.43E-4,.0015,.0087,.15,20*1E-6,2.5E-4,1600*1E-6,.009,.22,2.1E-5,2.7E-4,.0017,.0096,.33,2.2E-5,3E-4,.0018,.01,.47,2.4E-5,320*1E-6,.002,.011,.666,25*1E-6,324*1E-6,
#	.0021,.012,2.7E-5,3.3E-4,2200*1E-6,.013,30*1E-6,340*1E-6,.0025,.015,33*1E-6,3.5E-4,.0026,.016,3.5E-5,3.7E-4,2700*1E-6,17E3*1E-6,3.6E-5,378*1E-6,.0028,.018,3.9E-5,380*1E-6,.0029,.02,40*1E-6,3.9E-4,.003,.022,43*1E-6,400*1E-6,.0031,.023,4.7E-5,420*1E-6,.0033,.024,50*1E-6,4.3E-4,.0034,25E3*1E-6,5.3E-5,4.5E-4,3500*1E-6,.026,5.6E-5,460*1E-6,.0036,.027,60*1E-6,4.7E-4,3700*1E-6,28E3*1E-6]
#resistorList = [1.5, 4.7, 10, 47, 100, 220, 330, 470, 680, 1000, 2200, 3300, 4700, 10000, 22000, 47000, 100000, 330000, 1000000]

capacitorList = [
    0.1,0.22,0.47,0.68,
    1,1.5,2.2,3.3,4.7,6.8,
    10,22,33,47,
    100,220,330,470,
    1000,2200,4000,4700,8000,
    10_000
]
resistorList  = [10,11,12,13,15,16,18,20,22,24,27,30,33,36,39,43,47,51,56,62,68,75,82,91,
                 100,110,120,130,150,160,180,200,220,240,270,300,330,360,390,430,470,510,560,620,680,750,820,910,
                 1000,1100,1200,1300,1500,1600,1800,2000,2200,2400,2700,3000,3300,3600,3900,4300,4700,5100,5600,6200,6800,7500,8200,9100,
                 10_000,11_000,12_000,13_000,15_000,16_000,18_000,20_000,22_000,24_000,27_000,30_000,33_000,36_000,39_000,43_000,47_000,51_000,56_000,62_000,68_000,75_000,82_000,91_000,
                 100_000,110_000,120_000,130_000,150_000,160_000,180_000,200_000,220_000,240_000,270_000,300_000,330_000,360_000,390_000,430_000,470_000,510_000,560_000,620_000,680_000,750_000,820_000,910_000,
                 1_000_000,
                 10_000_000
]

for i in range(0,len(capacitorList)):
    capacitorList[i] /= 1_000_000
    
def formatUnit(x,p):
    units = ["p","n","μ","m","","k","M","G"]
    x *= math.pow(10,3*4)
    logMult = math.floor(math.log(x,1000))
    unit = units[logMult]
    x /= math.pow(10,logMult * 3)
    return str(round(x,10)) + unit + p
    
def rcalc():
    global f,d,capacitorList,resistorList

    d /= 100
    if (f <= 0):
        raise Exception("Frequency smaller than or equal to zero!")
    #if (d < 0.5 or d > 1):
    #    raise Exception("Duty cycle outside of valid bounds!")

    tmp1 = []
    tmp2 = []
    for c in capacitorList:
        for r1 in resistorList:
            for r2 in resistorList:
                timeH = 0.693 * (r1 + r2) * c
                timeL = 0.693 * r2 * c
                if (d > 0.5):
                    period = timeH + timeL
                    dc = timeH / period
                    frequency = 1 / period
                    tmp1.append([
                        c,
                        r1,
                        r2,
                        dc*100,
                        frequency,
                        abs(dc - d) * 1000 + abs(frequency - f)
                    ])

                timeHwD = 0.693 * r1 * c
                period = timeHwD + timeL
                dc = timeH / period
                frequency = 1 / period
                tmp2.append([
                    c,
                    r1,
                    r2,
                    dc*100,
                    frequency,
                    abs(dc - d) * 1000 + abs(frequency - f)
                ])

    # Sort the list
    if (d > 0.5):
        tmp1.sort(key = lambda x: x[5])
    tmp2.sort(key = lambda x: x[5])

    if (d > 0.5):
        print("Closest found matches for normal 555 astable circuit:")
        
        result = ""
        for i in range(0,10):
            #if (tmp[i][5] > 50):
            #    break
            result += "C: " + formatUnit(tmp1[i][0],"F") + "\t\tR1: " + formatUnit(tmp1[i][1],"Ω") + "\t\tR2: " + formatUnit(tmp1[i][2],"Ω")
            result += "\t\tDuty Cycle: " + str(tmp1[i][3]) + "%\t\tFrequency: " + formatUnit(tmp1[i][4],"Hz") + "\n"
        print(result)
    else:
        print("Normal 555 astable circuit is incompatible with duty cycles under 50%")
    print()
    print("Closest found matches for modified 555 astable circuit:")
    
    result = ""
    for i in range(0,10):
        #if (tmp[i][5] > 50):
        #    break
        result += "C: " + formatUnit(tmp2[i][0],"F") + "\t\tR1: " + formatUnit(tmp2[i][1],"Ω") + "\t\tR2: " + formatUnit(tmp2[i][2],"Ω")
        result += "\t\tDuty Cycle: " + str(tmp2[i][3]) + "%\t\tFrequency: " + formatUnit(tmp2[i][4],"Hz") + "\n"
    print(result)
    print("NOTE: Modified 555 astable circuit is similiar to normal astable circuit, except with a diode from pin 7 to pin 2/6, and a second diode from pin 2/6 to R2")

print()
rcalc()
print()
print("-------------------")
input("Press ENTER to quit")
