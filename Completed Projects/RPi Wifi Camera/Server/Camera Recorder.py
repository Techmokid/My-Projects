from picamera import PiCamera
import datetime as dt
import time

destination = '/home/pi/Desktop/Recordings/'
camera = PiCamera()
camera.rotation = 180

def recordSection(timeToRecord):
    path = destination + dt.datetime.now().strftime("%Y-%m-%d_%H,%M,%S.h264")
    
    #camera.start_preview()
    camera.start_recording(path)
    time.sleep(timeToRecord)
    camera.stop_recording()
    #camera.stop_preview()
    
    f = open(path + ".IP-Access-list","w+")
    f.close()

while(True):
    recordSection(30)
