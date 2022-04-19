import os

resistorList  = [10,11,12,13,15,16,18,20,22,24,27,30,33,36,39,43,47,51,56,62,68,75,82,91,
                 100,110,120,130,150,160,180,200,220,240,270,300,330,360,390,430,470,510,560,620,680,750,820,910,
                 1000,1100,1200,1300,1500,1600,1800,2000,2200,2400,2700,3000,3300,3600,3900,4300,4700,5100,5600,6200,6800,7500,8200,9100,
                 10_000,11_000,12_000,13_000,15_000,16_000,18_000,20_000,22_000,24_000,27_000,30_000,33_000,36_000,39_000,43_000,47_000,51_000,56_000,62_000,68_000,75_000,82_000,91_000,
                 100_000,110_000,120_000,130_000,150_000,160_000,180_000,200_000,220_000,240_000,270_000,300_000,330_000,360_000,390_000,430_000,470_000,510_000,560_000,620_000,680_000,750_000,820_000,910_000,
                 1_000_000,
                 10_000_000
]

capacitorList = [
    0.1,0.22,0.47,0.68,
    1,1.5,2.2,3.3,4.7,6.8,
    10,22,33,47,
    100,220,330,470,
    1000,2200,4000,4700,8000,
    10_000
]

# Time Period (seconds)   T = 0.693 * C * (R1 + 2*R2)
# High Time (seconds)     H = 0.693 * C * (R1 + R2)
# Low Time (seconds)      L = 0.693 * C * R2
# Frequency (hertz)       F = 1/T
# Duty Cycle (Percentage) D = 100 * (H/T) = 100 * (R1 + R2) / (R1 + 2*R2)

# NOTE:
#  - C only affects the frequency, so it's just a multiplier
#  - R1 only affects the high time, it doesn't affect low time
#  - R2 affects everything

# Therefore, we calculate R2 and C first to get us the required low time. THEN calculate R1


print("Calculating results")
def T(C,R1,R2):
    C = uF_to_F(C)
    return 0.693 * C * (R1 + 2*R2)
def H(C,R1,R2):
    C = uF_to_F(C)
    return 0.693 * C * (R1 + R2)
def HwD(C,R1,R2):
    C = uF_to_F(C)
    return 0.693 * C * R1
def L(C,R2):
    C = uF_to_F(C)
    return 0.693 * C * R2
def F(C,R1,R2):
    C = uF_to_F(C)
    return 1/T(C,R1,R2)
def D(R1,R2):
    return 100 * (R1 + R2) / (R1 + 2*R2)
def uF_to_F(C):
    return C / 1_000_000

resultsNormal = []
resultsWithDiode = []
for R1 in resistorList:
    for R2 in resistorList:
        for C in capacitorList:
            tmp = [
                R1,
                R2,
                C,
                T(C,R1,R2),
                H(C,R1,R2),
                L(C,R2),
                F(C,R1,R2),
                D(R1,R2)
            ]
            resultsNormal.append(tmp)
            tmp2 = [
                R1,
                R2,
                C,
                T(C,R1,R2),
                HwD(C,R1,R2),
                L(C,R2),
                F(C,R1,R2),
                D(R1,R2)
            ]
            resultsWithDiode.append(tmp)

print("Saving results...")
f = open(os.getcwd() + "/Precalculated Output Normal.txt",'w+')
for i in resultsNormal:
    f.write(str(i[0]) + "," + str(i[1]) + "," + str(i[2]) + "," + str(i[3]) + "," + str(i[4]) + "," + str(i[5]) + "," + str(i[6]) + "," + str(i[7]) + "\n")
f.close()
f = open(os.getcwd() + "/Precalculated Output With Diode.txt",'w+')
for i in resultsWithDiode:
    f.write(str(i[0]) + "," + str(i[1]) + "," + str(i[2]) + "," + str(i[3]) + "," + str(i[4]) + "," + str(i[5]) + "," + str(i[6]) + "," + str(i[7]) + "\n")
f.close()
