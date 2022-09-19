import os

dir1 = "C:/Users/aj200/Desktop/3DBenchy for Guider 2S.gx"
dir2 = "C:/Users/aj200/Desktop/3DBenchy for Guider 2.gx"

if (not os.path.exists(dir1)):
    raise Exception("Could not locate file: " + dir1)
if (not os.path.exists(dir2)):
    raise Exception("Could not locate file: " + dir2)

f1 = open(dir1,'rb')
f2 = open(dir2,'rb')
f1_data = f1.readlines()
f2_data = f2.readlines()
f1.close()
f2.close()

x = 0
for i in range(2,min(len(f1_data),len(f2_data))):
    if (("G1" not in str(f1_data[i])) or ("G1" not in str(f2_data[i]))):           #Ignore movement commands. They will be irrelevant
        if ((str(f1_data[i])[2] != ";") or (str(f2_data[i])[2] != ";")):            #Ignore code comments. They are useless to us
            print(str(i) + ": \t\t" + str(f1_data[i]) + "\t\t\t" + str(f2_data[i]))
            x += 1
