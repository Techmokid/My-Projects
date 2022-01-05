from PIL import Image

directory = "C:/Users/aj200/Desktop/Minecraft Modding/TutorialMod/src/main/resources/assets/tutorialmod/textures/item/tutorial_item.png"
im = Image.open(directory)
pixels = im.load()

for i in range(0,16):
    for j in range(0,16):
        r = pixels[i,j][0]
        g = pixels[i,j][1]
        b = pixels[i,j][2]
        if ((r==255) and (g==255) and (b==255)):
            pixels[i,j] = (255,255,255,0)

im.save(directory)
