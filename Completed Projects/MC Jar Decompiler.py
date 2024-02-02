import requests,os,shutil,zipfile,time
from subprocess import check_output
from pathlib import Path

directory = "C:/Users/aj200/AppData/Roaming/.minecraft/mods/BrandonsCore-1.16.5-3.0.13.244-universal.jar"
SkipModUnzipping = True
startingMCVersion = '1.16.5'
endingMCVersion = '1.18.2'

#This is for decompiling the jar file
if not SkipModUnzipping:
    if(os.path.exists("C:/Temp/procyon/")):
        shutil.rmtree("C:/Temp/procyon/")
    os.system('cmd /c "java -jar C:/Windows/procyon.jar -jar "' + directory + '" -o C:/Temp/procyon"')

    if(os.path.exists(directory) == False):
        print("ERROR!")

src = "C:/Temp/procyon/"

#This is for Correcting the decompiled jar
functionList = []
fieldList = []

def getFunctionList():
    global functionList
    print("Collecting Functions List...")
    url = 'https://raw.githubusercontent.com/jrbudda/Vivecraft_110/master/mcppatches/mappings/methods.csv'
    data = requests.get(url).text
    functionList = splitTextToLines(data)
    functionList.pop(0)
    functionList.pop()

def getFieldList():
    global fieldList
    print("Collecting Fields List...")
    url = 'https://raw.githubusercontent.com/jrbudda/Vivecraft_110/master/mcppatches/mappings/fields.csv'
    data = requests.get(url).text
    fieldList = splitTextToLines(data)
    fieldList.pop(0)
    fieldList.pop()

def splitTextToLines(text):
    result = [""]
    pos = 0
    for i in text:
        if (i != '\n'):
            result[pos] += i
        else:
            result.append("")
            pos += 1
    return result

def fixString(func, doAll = True):
    global functionList,fieldList
    
    if (doAll):
        allFunctions_orig = []
        allFunctions_fixd = []
        for x in functionList:
            allFunctions_orig.append(x.split(',')[0])
            allFunctions_fixd.append(x.split(',')[1])
        
        allFields_orig = []
        allFields_fixd = []
        for x in fieldList:
            allFields_orig.append(x.split(',')[0])
            allFields_fixd.append(x.split(',')[1])
        
        x = 0
        for i in allFunctions_orig:
            func = func.replace(allFunctions_orig[x],allFunctions_fixd[x])
            x += 1
        
        x = 0
        for i in allFields_orig:
            func = func.replace(allFields_orig[x],allFields_fixd[x])
            x += 1
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

getFunctionList()
getFieldList()
print()
if not SkipModUnzipping:
    pathlist = Path(src).glob('**/*.java')
    for path in pathlist:
        path_in_str = str(path)
        print("Correcting File: " + path_in_str)
        correct(path_in_str)

#This is for downloading the required forge version
def scanForTerm(lines,term):
    loops = 0
    for i in lines:
        if (term in lines[loops]):
            break
        loops += 1
    return loops

def downloadForgeVersion(forgeVersion,generatorType):
    print("\n\n\nRetrieving Forge download url for forge version: " + forgeVersion)
    rawData = requests.get('http://files.minecraftforge.net/maven/net/minecraftforge/forge/index_' + forgeVersion + '.html').text
    splitData = splitTextToLines(rawData)
    url = splitData[scanForTerm(splitData,'<i class="fa classifier-mdk">')-1].split('&url=')[1].split('"')[0]
    
    if(os.path.exists("C:/Temp/forgeVersion/")):
        shutil.rmtree("C:/Temp/forgeVersion/")
    time.sleep(1)
    os.mkdir("C:/Temp/forgeVersion/")
    time.sleep(1)
    
    print("Downloading Forge...")
    get_response = requests.get(url,stream=True)
    file_name  = url.split("/")[-1]
    with open('C:/Temp/forgeVersion/forge.zip', 'wb') as f:
        for chunk in get_response.iter_content(chunk_size=1024):
            if chunk: # filter out keep-alive new chunks
                f.write(chunk)
    
    print("Unzipping...")
    os.mkdir("C:/Temp/forgeVersion/forge")
    with zipfile.ZipFile('C:/Temp/forgeVersion/forge.zip', 'r') as zip_ref:
        zip_ref.extractall('C:/Temp/forgeVersion/forge/')

    print("Generating required files...")
    if (generatorType == "Eclipse"):
        generatorType = 'genEclipseRuns'
    elif (generatorType == "IntelliJ"):
        generatorType = 'genIntellijRuns'
    else:
        print("INVALID GENERATOR TYPE!")
        quit()
    os.system('cmd /c "cd C:/Temp/forgeVersion/forge/ & gradlew clean & gradlew setupDecompWorkspace & gradlew ' + generatorType + ' & gradlew eclipse"')
    shutil.rmtree("C:/Temp/forgeVersion/forge/src/main/java/com/")
    mergeForgeAndJar()
    
    createPOM("com.winglessentials","winglessential",forgeVersion)

#This is for merging the decompiled jar file with the forge file
def mergeForgeAndJar():
    modDir = "C:/Temp/procyon/" + os.listdir("C:/Temp/procyon/")[0] + "/"
    FrgDir = "C:/Temp/forgeVersion/forge/src/main/java/" + os.listdir("C:/Temp/procyon/")[0]
    shutil.copytree(modDir, FrgDir)
    
    #All that's left is to generate the plugin.yml file
    pathlist = Path(FrgDir).glob('**/*.java')
    result = ""
    for path in pathlist:
        with open(path) as f:
            for line in f.readlines():
                if (('public final class ' in line) and (' extends JavaPlugin' in line)):
                    result = str(path)[41:-5].replace('\\','.')
                    print(result)
    
    #Find the required data (The name of the mod and it's version) and fill in "plugin.yml"!
    fileContents = "main: " + result + "\n"
    fileContents += "name: " + findFilenameFromDirectory(directory) + "\n"
    fileContents += "version: 0.1\n"
    fileContents += "author: Techmokid's Jar Decompiler\n"
    
    with open('C:/Temp/forgeVersion/forge/src/main/resources/plugin.yml','w+') as f:
        f.write(fileContents)
    
    editClassPath()
    editSettings()

def editClassPath():
    fileContents = "    <classpathentry kind=\"lib\" path=\"C:/Users/aj200/.m2/repository/org/spigotmc/spigot-api/1.15.2-R0.1-SNAPSHOT/spigot-api-1.15.2-R0.1-SNAPSHOT.jar\" sourcepath=\"C:/Users/aj200/.m2/repository/org/spigotmc/spigot-api/1.15.2-R0.1-SNAPSHOT/spigot-api-1.15.2-R0.1-SNAPSHOT-sources.jar\">"
    fileContents += "        <attributes>"
    fileContents += "            <attribute name=\"maven.pomderived\" value=\"true\"/>"
    fileContents += "            <attribute name=\"maven.groupId\" value=\"org.spigotmc\"/>"
    fileContents += "            <attribute name=\"maven.artifactId\" value=\"spigot-api\"/>"
    fileContents += "            <attribute name=\"maven.version\" value=\"1.15.2-R0.1-SNAPSHOT\"/>"
    fileContents += "            <attribute name=\"maven.scope\" value=\"provided\"/>"
    fileContents += "        </attributes>"
    fileContents += "    </classpathentry>"
    fileContents += "    <classpathentry kind=\"lib\" path=\"C:/Users/aj200/.m2/repository/commons-lang/commons-lang/2.6/commons-lang-2.6.jar\" sourcepath=\"C:/Users/aj200/.m2/repository/commons-lang/commons-lang/2.6/commons-lang-2.6-sources.jar\">"
    fileContents += "        <attributes>"
    fileContents += "            <attribute name=\"maven.pomderived\" value=\"true\"/>"
    fileContents += "            <attribute name=\"maven.groupId\" value=\"commons-lang\"/>"
    fileContents += "            <attribute name=\"maven.artifactId\" value=\"commons-lang\"/>"
    fileContents += "            <attribute name=\"maven.version\" value=\"2.6\"/>"
    fileContents += "            <attribute name=\"maven.scope\" value=\"provided\"/>"
    fileContents += "        </attributes>"
    fileContents += "    </classpathentry>"
    fileContents += "</classpath>"
    
    #Remove the last line of the file
    try:
        with open("C:/Temp/forgeVersion/forge/.classpath") as f:
            lines = f.readlines()
        with open("C:/Temp/forgeVersion/forge/.classpath",'w+') as f:
            f.writelines([item for item in lines[:-1]])
    except:
        print("Could not open classpath")
    
    #Write the extra data to the file and finish
    with open("C:/Temp/forgeVersion/forge/.classpath",'a') as f:
        f.write(fileContents)

def editSettings():
    fileContents = "eclipse.preferences.version=1"
    fileContents += "org.eclipse.jdt.core.compiler.codegen.inlineJsrBytecode=enabled"
    fileContents += "org.eclipse.jdt.core.compiler.codegen.targetPlatform=1.7"
    fileContents += "org.eclipse.jdt.core.compiler.codegen.unusedLocal=preserve"
    fileContents += "org.eclipse.jdt.core.compiler.compliance=1.7"
    fileContents += "org.eclipse.jdt.core.compiler.debug.lineNumber=generate"
    fileContents += "org.eclipse.jdt.core.compiler.debug.localVariable=generate"
    fileContents += "org.eclipse.jdt.core.compiler.debug.sourceFile=generate"
    fileContents += "org.eclipse.jdt.core.compiler.problem.assertIdentifier=error"
    fileContents += "org.eclipse.jdt.core.compiler.problem.enumIdentifier=error"
    fileContents += "org.eclipse.jdt.core.compiler.source=1.7"

    os.mkdir("C:/Temp/forgeVersion/forge/.settings/")
    with open("C:/Temp/forgeVersion/forge/.settings/org.eclipse.jdt.core.prefs",'w+') as f:
        f.write(fileContents)

def createPOM(groupID, artifactID, mc_version, mod_version="1.0"):
    fileContents = "<project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd\">"
    fileContents += "\n    <modelVersion>4.0.0</modelVersion>"
    fileContents += "\n    <groupId>" + groupID + "</groupId>"
    fileContents += "\n    <artifactId>" + artifactID + "</artifactId>"
    fileContents += "\n    <version>" + mod_version + "</version>"
    
    fileContents += "\n    <build>"
    fileContents += "\n        <plugins>"
    fileContents += "\n            <plugin>"
    fileContents += "\n                <groupId>org.apache.maven.plugins</groupId>"
    fileContents += "\n                <artifactId>maven-compiler-plugin</artifactId>"
    fileContents += "\n                <configuration>"
    fileContents += "\n                    <source>1.8</source>"
    fileContents += "\n                    <target>1.8</target>"
    fileContents += "\n                </configuration>"
    fileContents += "\n            </plugin>"
    fileContents += "\n        </plugins>"
    fileContents += "\n    </build>"
	
    fileContents += "\n    <repositories>"
    fileContents += "\n        <repository>"
    fileContents += "\n            <id>spigot-repo</id>"
    fileContents += "\n            <url>https://hub.spigotmc.org/nexus/content/repositories/public/</url>"
    fileContents += "\n        </repository>"
    fileContents += "\n    </repositories>"
	
    fileContents += "\n    <dependencies>"
    fileContents += "\n        <dependency>"
    fileContents += "\n            <groupId>org.bukkit</groupId>"
    fileContents += "\n            <artifactId>bukkit</artifactId>"
    fileContents += "\n            <version>" + mc_version + "-R0.1-SNAPSHOT</version><!--change this value depending on the version or use LATEST-->"
    fileContents += "\n            <type>jar</type>"
    fileContents += "\n            <scope>provided</scope>"
    fileContents += "\n        </dependency>"
    fileContents += "\n        <dependency>"
    fileContents += "\n            <groupId>org.spigotmc</groupId>"
    fileContents += "\n            <artifactId>spigot-api</artifactId>"
    fileContents += "\n            <version>" + mc_version + "-R0.1-SNAPSHOT</version><!--change this value depending on the version-->"
    fileContents += "\n            <type>jar</type>"
    fileContents += "\n            <scope>provided</scope>"
    fileContents += "\n            </dependency>"
    fileContents += "\n    </dependencies>"
    fileContents += "\n</project>"
    
    with open("C:/Temp/forgeVersion/forge/pom.xml",'w+') as f:
        f.write(fileContents)

def findFilenameFromDirectory(directory):
    result = ""
    loops = 1
    nextLetter = directory[len(directory) - loops]
    while (nextLetter != '/'):
        result = nextLetter + result
        loops += 1
        nextLetter = directory[len(directory) - loops]
    return result

downloadForgeVersion(endingMCVersion,'Eclipse')

#Perform naive conversion to minecraft version
#print("Performing naive version conversion")
#pathlist = Path(src).glob('**/*.java')

#for path in pathlist:
#    path_in_str = str(path)
#    print("Performing naive correction on file: " + path_in_str)
#
#    dataArr = []
#    with open(path_in_str, "r") as f:
#        data = f.readlines()
#        
#        for i in data:
#            if not (i == i.replace(startingMCVersion,endingMCVersion)):
#                print("Discovered version information")
#            dataArr.append(str(i.replace(startingMCVersion,endingMCVersion)))
#    with open(path_in_str, "w+") as f:
#        f.writelines(dataArr)

#Finally recompile the mod
#input("Mod successfully decompiled and naive converted. \nHit enter to attempt recompile\n\n")
#os.system('cmd /c "C:/Temp/forgeVersion/forge/gradlew.bat build && pause"')

#x = check_output("C:/Temp/forgeVersion/forge/gradlew.bat build", shell=True).decode("utf-8")
#print(x)

print("Done!")





































