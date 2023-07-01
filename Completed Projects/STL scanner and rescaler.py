import os,trimesh,shutil





#--------------------------------------------------------------------------------------------------------------------------
#---------------------                      Start Of User Variables                      ----------------------------------
#--------------------------------------------------------------------------------------------------------------------------

origDir = 'C:\\Users\\Techmo\\Desktop\\STL Files\\ISS'
modifiedDir = origDir + '_Rescaled'
rescalePercentage = 170

Printers = []
#Printers.append(["E3P",[300,300,300]])
#Printers.append(["E3N",[220,220,250]])
#Printers.append(["E5P",[220,220,280]])
#Printers.append(["G2S",[280,250,300]])
Printers.append(["Ender 3 Pro   ",[300,300,300]])
Printers.append(["Ender 3 V2 Neo",[220,220,250]])
Printers.append(["Ender 5 S1    ",[220,220,280]])
Printers.append(["Guider II S   ",[280,250,300]])
Printers.append(["Protech Resin ",[160,129,80 ]])
Printers.append(["Protech FPE1  ",260,260,260])

#--------------------------------------------------------------------------------------------------------------------------
#----------------------                      End Of User Variables                      -----------------------------------
#--------------------------------------------------------------------------------------------------------------------------








print("Checking pre-existing path")
modifiedDir += "_" + str(rescalePercentage) + "%"
if (os.path.exists(modifiedDir)):
    shutil.rmtree(modifiedDir)
shutil.copytree(origDir,modifiedDir)

for i,printer in enumerate(Printers):
    if (len(printer) == 4):
        Printers[i] = [printer[0],[printer[1],printer[2],printer[3]],0]
    elif (len(printer) == 2):
        Printers[i].append(0)
    else:
        raise Exception("Invalid printer parameters: " + str(printer))

print("Reading directories")
files = []
folders = []
STLs = []
for subdir, dirs, files2 in os.walk(modifiedDir):
    for file in files2:
        if (".stl" in file.lower()):
            files.append(os.path.join(subdir, file))
            STLs.append(trimesh.load_mesh(os.path.join(subdir, file)))

def scaleSTL(stl,scaleX,scaleY=None,scaleZ=None):
    for vertex in stl.vertices:
        if ((scaleY==None) or (scaleZ==None)):
            vertex *= scaleX
        else:
            vertex[0] *= scaleX
            vertex[1] *= scaleY
            vertex[2] *= scaleZ

def doesSTLFitOnPrinter(stl, print_bed_x, print_bed_y, print_bed_z):
    printDim = [print_bed_x, print_bed_y, print_bed_z]
    printDim.sort() #Put the printers dimensions from largest to smallest

    inf = 999999999999999
    minX = inf
    minY = inf
    minZ = inf
    maxX = -inf
    maxY = -inf
    maxZ = -inf
    for vertex in stl.vertices:
        if (vertex[0] > maxX):
            maxX = vertex[0]
        elif (vertex[0] < minX):
            minX = vertex[0]
        if (vertex[1] > maxY):
            maxY = vertex[1]
        elif (vertex[1] < minY):
            minY = vertex[1]
        if (vertex[2] > maxZ):
            maxZ = vertex[2]
        elif (vertex[2] < minZ):
            minZ = vertex[2]
    X = maxX - minX
    Y = maxY - minY
    Z = maxZ - minZ
    STLDim = [X,Y,Z]
    STLDim.sort()

    if (STLDim[0] > printDim[0]):
        return False
    if (STLDim[1] > printDim[1]):
        return False
    if (STLDim[2] > printDim[2]):
        return False
    return True










#--------------------------------------------------------------------------------------------------------------------------
#------------------------                      Start of User Script                      ----------------------------------
#--------------------------------------------------------------------------------------------------------------------------
    
print()
if ((rescalePercentage == 100) or (rescalePercentage <= 0) or (rescalePercentage == "") or (rescalePercentage == None)):
    print("No STL rescaling selected")
else:
    print("STL rescaling set to: " + str(rescalePercentage) + " %")
rescalePercentage /= 100

print("Running script")
for i, loaded_mesh in enumerate(STLs):
    scaleSTL(loaded_mesh,rescalePercentage)
    loaded_mesh.export(files[i])

    for printer in Printers:
        if(doesSTLFitOnPrinter(loaded_mesh,printer[1][0],printer[1][1],printer[1][2])):
            printer[2] += 1

print()
for printer in Printers:
     print(" - " + printer[0] + " - STLs that fit: " + str(printer[2]) + "/" + str(len(files)) + " = " + str(round(100*printer[2]/len(files),2)) + " %     " + str(len(files) - printer[2]) + " STL files failed to fit on the bed")












