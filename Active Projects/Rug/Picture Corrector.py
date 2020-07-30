import os,operator
from PIL import Image

src = "test.jpg"

#destination file is renamed so to not overwrite the original
dst = "CORRECTED_" + src

#Delete destination file if it already exists
if (os.path.exists(dst)):
    os.remove(dst)

#Load up the image
im = Image.open(src)
pixels = im.load()

width, height = im.size

#Define the nearest pixels
validColours = []
totalPixels = width * height
loops = 0
oneTimeTrigger = False
def findNearestPixelColour(pixel):
    global validColours,loops,totalPixels,oneTimeTrigger
    
    if (loops % 10000 == 0):
        print("Image Conversion: " + str(round(100 * float(loops) / float(totalPixels),2)) + "\t% complete")
    
    loops += 1
    
    if (oneTimeTrigger == False):
        oneTimeTrigger = True
        f = open("colours.txt","r")
        for i in f.readlines():
            validColours.append(i.replace("\n","").replace("\t","").replace(" ","").split(','))
        f.close()
    
    r = pixel[0]
    g = pixel[1]
    b = pixel[2]
    
    best = [0,0,0]
    for i in validColours:
        r_temp = int(i[0])
        g_temp = int(i[1])
        b_temp = int(i[2])
        
        bestDiff = abs(pixel[0] - best[0]) + abs(pixel[1] - best[1]) + abs(pixel[2] - best[2])
        curntDif = abs(pixel[0] - r_temp) + abs(pixel[1] - g_temp) + abs(pixel[2] - b_temp)
        
        if (bestDiff > curntDif):
            best = [r_temp,g_temp,b_temp]
    
    return best

#Edit the image
for i in range(0,width):
    for j in range(0,height):
        pixel = findNearestPixelColour(pixels[i,j])
        pixels[i,j] = (pixel[0],pixel[1],pixel[2],255)

im.save(dst)
