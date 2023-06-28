import pyttsx3,wave,os,subprocess,math,struct,pygame
import matplotlib.pyplot as plt
import numpy as np
from pydub import AudioSegment

#msg = input("What would you like AUTO to say: ")
msg = "Greetings captain. I am here to inform you that specimen 4 has returned positive. Please give me the plant captain"
sineFrequency = 80

filedir = "C:/Users/aj200/Documents/GitHub/My-Projects/Active Projects/AUTO TTS/"
durationMultiplier = .7

if(os.path.exists(filedir + "TTS Orig.wav")):
    os.unlink(filedir + "TTS Orig.wav")

engine = pyttsx3.init()
engine.say(msg)
engine.save_to_file(msg,filedir + "TTS Orig.wav")
engine.runAndWait()
engine.stop()

audio = wave.open(filedir + "TTS Orig.wav",'rb')
print("Number of channels:", audio.getnchannels())
print("Sample width:", audio.getsampwidth())
print("Framerate:", audio.getframerate())
print("Framecount:", audio.getnframes())
#print("Parameters", audio.getparams())

audioDuration = audio.getnframes() / audio.getframerate()
print("Duration:",round(audioDuration,2),"secs")

channels = audio.getnchannels()
sampleWidth = audio.getsampwidth()
framerate = audio.getframerate()*durationMultiplier
frames = audio.readframes(-1)
audio.close()

if (os.path.exists(filedir + "TTS Pitched.wav")):
    os.unlink(filedir + "TTS Pitched.wav")
audio = wave.open(filedir + "TTS Pitched.wav", "wb")
audio.setnchannels(channels)
audio.setsampwidth(sampleWidth)
audio.setframerate(framerate)
audio.writeframes(frames)
audio.close()

wavefile = wave.open(filedir + "TTS Pitched.wav",'r')
length = wavefile.getnframes()
sineFrequency = audio.getnframes() / (audioDuration * 3.14159 * 2 * sineFrequency)

w = wave.open(filedir + "TTS Result.wav",'w')
w.setnchannels(channels)
w.setsampwidth(sampleWidth)
w.setframerate(framerate)

def SineFunc(theta,depth):
    return 4*math.sin((depth*2-1)*theta/math.pi) / ((depth*2-1)*math.pi)

x = []
yOrig = []
sine = []
yFinal = []
for i in range(0,length):
    wavedata = wavefile.readframes(1)
    data = struct.unpack("<h", wavedata)
    x.append(i)
    
    currentVol = int(data[0])
    
    yOrig.append(currentVol)

    dT = i/sineFrequency
    #sineFunction = math.sin(dT)                        #Sine wave
    #sineFunction = 2*math.pow(math.sin(dT/2),2) - 1    #Dephased sinewave
    #sineFunction = int(math.sin(dT) > 0)               #Square wave
    #sineFunction = 2*math.pow(math.sin(dT/2),8) - 1
    #sineFunction = math.sin(dT) * math.sin(dT) * math.sin(2*dT)
    sineFunction = (SineFunc(dT,1) + SineFunc(dT,2) + SineFunc(dT,3) + SineFunc(dT,4) + SineFunc(dT,5) + SineFunc(dT,6)) * (1 - math.pi/8)
    
    sine.append(sineFunction)
    yFinal.append(sineFunction*currentVol)
    
    data = struct.pack('<h', round(sineFunction*currentVol))
    w.writeframesraw(data)
w.close()

#Here we take the resulting audio and convert it into dual channel
left_channel = AudioSegment.from_wav(filedir + "TTS Result.wav")
right_channel = AudioSegment.from_wav(filedir + "TTS Result.wav")
stereo_sound = AudioSegment.from_mono_audiosegments(left_channel, right_channel)
stereo_sound.export(filedir + "TTS Stereo Result.wav", format = 'wav')

figure, axis = plt.subplots(2,2)
print("Plotting original audio")
axis[0,0].plot(x,yOrig)
axis[0,0].set_title("Original Audio")

print("Plotting Sine wave")
axis[1,1].plot(x,sine)
axis[1,1].set_title("Sine Wave")

print("Plotting resulting audio")
axis[1,0].plot(x,yFinal)
axis[1,0].set_title("Resulting Audio")
plt.show()

pygame.init()
sound = pygame.mixer.Sound(filedir + "TTS Result.wav")
sound.play()

#w.writeframes(frames)
