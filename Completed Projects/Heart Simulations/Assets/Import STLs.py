import os,shutil,pymesh

src = ["C:/Users/aj200/Documents/GitHub/My-Projects/Active Projects/Heart Mark 1","C:/Users/aj200/Documents/GitHub/My-Projects/Active Projects/Heart Mark 2"]
dst = os.getcwd().replace("\\","/") + "/Object Files/"

for x in src:
    for root,dirs,files in os.walk(x):
        for i in files:
            if (i[-4:] == (".obj")):
                shutil.copy(root+"/"+i,dst)
