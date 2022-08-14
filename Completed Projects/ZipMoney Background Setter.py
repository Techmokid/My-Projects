from PIL import Image,ImageDraw,ImageFont
import ctypes,os,shutil,datetime

debtLeft = 0

with open("C:/Temp/Zip Debt Left.txt",'r') as f:
    debtLeft = float(f.read())

imgDir = "C:/Temp/Python Zip Status/"

if (os.path.exists(imgDir)):
    shutil.rmtree(imgDir)
os.makedirs(imgDir)

img = Image.new('RGB', (1842,1036), color = 'gray')
pixels = img.load()

for x in range(img.size[0]):
    for y in range(img.size[1]):
        if (y > 995):
            pixels[x,y] = (0,255,0)

fnt1 = ImageFont.truetype('C:/Windows/Fonts/Arial.ttf', 100)
d = ImageDraw.Draw(img)
d.text((350,400), "ZipMoney Debt Left: $" + str(round(debtLeft)), font=fnt1, fill=(250,250,250))

dateTime = datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S")
fnt2 = ImageFont.truetype('C:/Windows/Fonts/Arial.ttf', 50)
d.text((550,550), "Last Updated: " + dateTime, font=fnt2, fill=(250,250,250))

img.save(imgDir + "ZipMoney Status.bmp")
ctypes.windll.user32.SystemParametersInfoW(20, 0, imgDir + "ZipMoney Status.bmp" , 0)
