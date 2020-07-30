from pathlib import Path
from PIL import Image
import os,shutil,time

src = [
    "example images 1/",
    "example images 2/",
    "example images 3/",
    "example images 4/"
]

dst = "result/"
errorFile = "errors.txt"

def createFile(x):
    if (os.path.exists(x)):
        shutil.rmtree(x)
    os.mkdir(x)

allSrcPaths = []
allDstPaths = []

def getAllImageFiles():
    global allSrcPaths,src
    for x in src:
        for i in Path(x).glob('**/*'):
            NameErrorDetection(str(i))
        for i in Path(x).glob('**/*.png'):
            allSrcPaths.append(i)
        for i in Path(x).glob('**/*.jpg'):
            allSrcPaths.append(i)
        for i in Path(x).glob('**/*.jpeg'):
            allSrcPaths.append(i)

def updateImageFiles():
    global allDstPaths
    allDstPaths = []
    for i in Path(dst).glob('**/*.png'):
        allDstPaths.append(i)
    for i in Path(dst).glob('**/*.jpg'):
        allDstPaths.append(i)
    for i in Path(dst).glob('**/*.jpeg'):
        allDstPaths.append(i)

def NameErrorDetection(directory):
    corDir = directory.replace("\\","/")
    if (corDir.split('/')[-1][0] != "."):
        return
    os.rename(directory,corDir[:corDir.rfind('/')] + "/a" + corDir[corDir.rfind('/') + 1:])

def DoubleUpDetection(directory):
    #img = Image.open(directory)
    try:
        img = Image.open(directory)
    except:
        with open(errorFile,'a+') as f:
            f.write("\n" + directory)
        return
    for path in allDstPaths:
        if (ImagesMatch(directory,str(path))):
            return
        pass
    
    # If you get this far, then it is a completely original image with no double-ups
    
    temp = directory.replace('\\','/').split('/')
    shutil.copyfile(directory,dst + temp[-1])
    updateImageFiles()

def ImagesMatch(Image_1, Image_2):
    img_1 = Image.open(Image_1)
    img_2 = Image.open(Image_2)
    
    if ((img_1.width != img_2.width) or (img_1.height != img_2.height)):
        return False

    pixels_1 = img_1.load()
    pixels_2 = img_2.load()
    
    x = 0
    y = 0
    while (x < img_1.width):
        while (y < img_1.height):
            try:
                if (pixels_1[x,y][0] != pixels_2[x,y][0]):
                    return False
                if (pixels_1[x,y][1] != pixels_2[x,y][1]):
                    return False
                if (pixels_1[x,y][2] != pixels_2[x,y][2]):
                    return False
            except:
                try:
                    if (pixels_1[x,y] != pixels_2[x,y]):
                        return False
                    if (pixels_1[x,y] != pixels_2[x,y]):
                        return False
                    if (pixels_1[x,y] != pixels_2[x,y]):
                        return False
                except:
                    pass
            y += 1
        x += 1
    return True

print("Copying Files...\n\n\n")
getAllImageFiles()
createFile(dst)

loops = 0
prev = 0
for path in allSrcPaths:
    temp = str(round(100 * loops / len(allSrcPaths)))
    if (temp != prev):
        prev = temp
        print("Percentage: " + temp + "%")
    DoubleUpDetection(str(path))
    loops += 1

print("\n\n\nProcess Finished! Close this window whenever ready")

while(True):
    pass
















































