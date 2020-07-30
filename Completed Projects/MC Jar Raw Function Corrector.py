import requests,os,shutil,zipfile,time
from pathlib import Path

src = "C:/Temp/forgeVersion/forge/src/main/java"
def fixString(func):
    func = func.replace("func_78753_a","windowClick")
    func = func.replace("field_190927_a","EMPTY")
    func = func.replace("func_193011_a","updateScreenPosition")
    func = func.replace("func_194125_a","isInCreativeTab")
    func = func.replace("func_190926_b","isEmpty")
    func = func.replace("func_191197_a","withSize")
    func = func.replace("func_191283_b","loadAllItems")
    func = func.replace("func_191281_a","saveAllItems")
    func = func.replace("func_192400_c","getIngredients")
    func = func.replace("func_193365_a","getIngredients")
    func = func.replace("func_190916_E","getCount")
    func = func.replace("fontRendererObj","fontRenderer")
    func = func.replace("drawCreativeTabHoveringText","drawHoveringText")
    func = func.replace(".xPosition",".x")
    func = func.replace(".yPosition",".y")
    func = func.replace("func_190920_e","setCount")
    func = func.replace("func_190918_g","setCount")
    func = func.replace(".xCoord",".x")
    func = func.replace(".yCoord",".y")
    func = func.replace(".zCoord",".z")
    
    func = func.replace("mc.theWorld","mc.world")
    func = func.replace("mc.thePlayer.","mc.player.")
    func = func.replace("mc.thePlayer)","mc.player)")
    func = func.replace("mc.thePlayer ","mc.player ")
    func = func.replace("mc.thePlayer;","mc.player;")
    #func = func.replace("mc.world","mc.theWorld")
    #func = func.replace("mc.player.","mc.thePlayer.")
    #func = func.replace("mc.player)","mc.thePlayer)")
    #func = func.replace("mc.player ","mc.thePlayer ")
    #func = func.replace("mc.player;","mc.thePlayer;")
    return func

def correct(directory):
    f = open(directory,'r')
    fileContents = f.readlines()
    f.close()

    pos = 0
    for i in fileContents:
        fileContents[pos] = fixString(fileContents[pos])
        pos += 1
    
    f = open(directory,'w')
    f.writelines(fileContents)
    f.close()

pathlist = Path(src).glob('**/*.java')
for path in pathlist:
    path_in_str = str(path)
    print("Correcting File: " + path_in_str)
    correct(path_in_str)
