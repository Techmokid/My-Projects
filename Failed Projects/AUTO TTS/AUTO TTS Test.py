import pyttsx3,wave,os,subprocess,math,struct
import matplotlib.pyplot as plt
import numpy as np
from pydub import AudioSegment

#msg = input("What would you like AUTO to say: ")
msg = "Greetings captain. I am here to inform you that specimen 4 has returned positive"
sineFrequency = 50

filename = "C:/Users/aj200/Desktop/AUTO.mp3"
filename = "C:/Users/aj200/Downloads/robot_voice-master/robot_voice-master/sample.wav"
durationMultiplier = .7

engine = pyttsx3.init()
engine.say(msg)
engine.save_to_file(msg,filename)
engine.runAndWait()
engine.stop()

audio = wave.open(filename,'rb')
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

if(os.path.exists(filename)):
    os.unlink(filename)

audio = wave.open(filename, "wb")
audio.setnchannels(channels)
audio.setsampwidth(sampleWidth)
audio.setframerate(framerate)
audio.writeframes(frames)
audio.close()

if (os.path.exists(filename + ".wav")):
    os.unlink(filename)
subprocess.call(['ffmpeg', '-i', filename,filename + '.wav'])
if (os.path.exists(filename)):
    os.unlink(filename)
filename += '.wav'

wavefile = wave.open(filename,'r')
length = wavefile.getnframes()
sineFrequency = audio.getnframes() / (audioDuration * 3.14159 * 2 * sineFrequency)

w = wave.open(filename + "_Result.wav",'w')
w.setnchannels(channels)
w.setsampwidth(sampleWidth)
w.setframerate(framerate)

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
    sineFunction = math.sin(i/sineFrequency)
    sine.append(sineFunction)
    yFinal.append(sineFunction*currentVol)
    
    data = struct.pack('<h', round(sineFunction*currentVol))
    w.writeframesraw(data)
w.close()

#Here we take the resulting audio and convert it into dual channel
left_channel = AudioSegment.from_wav(filename)
right_channel = AudioSegment.from_wav(filename)
stereo_sound = AudioSegment.from_mono_audiosegments(left_channel, right_channel)
stereo_sound.export(filename + "_STEREO.wav")

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


#w.writeframes(frames)
