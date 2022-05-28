import os

try:
    import pyttsx3
except:
    os.system('python -m pip install pyttsx3')
    os.system('sudo apt-get install espeak')
os.system('chmod +x "/home/pbody/Desktop/uploadFromRPiToPC.sh"')
