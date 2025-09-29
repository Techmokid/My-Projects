import time
import requests
import re
import Dates
from firebanInfo import firebanInfo
from datetime import datetime,date
from pyowm.owm import OWM

EMERGENCY_WA_WARNINGS = "https://www.emergency.wa.gov.au/data/message_warnings.json"
EMERGENCY_WA_TFB_PAGE = "https://www.emergency.wa.gov.au/total-fire-bans"
MY_BIRTHDAY           = date(2000,8,21)
ESTIMATED_LIFESPAN    = 78
LGA                   = "Helena Valley"

dt =        datetime.now()
year =      int(dt.strftime("%Y"))
month =     int(dt.strftime("%m"))
day =       int(dt.strftime("%d"))
dayOfYear = (dt.date() - date(year,1,1)).days

def GetDateDiff(now,then):
    time_difference = (then - now).days
    if (time_difference < 0):
        time_difference += 365
    return time_difference
    
def GetCurrentDateDiff(dt,day,month): # Australian formatting of day/month/year
    return GetDateDiff(dt.date(), date(int(dt.strftime("%Y")),month,day))

def printWithKnownSize(size,msg):
    return msg + " "*(size-len(msg))

def isFirebanInPlace(lga_name): #Add prohibited check using online info for my area
    return False

def getEasterDate():
    pass

ImportantDates = Dates.upcoming_wa_public_holidays()

# Basic date info
print(printWithKnownSize(26,"Todays date")            + ": " + str(dt.strftime("%d/%m/%Y")))
print(printWithKnownSize(26,"Day of the Year")        + ": " + str(dayOfYear) + "/365 = " + str(int(round(100*dayOfYear/365,0))) + " % through the year")

myAge = (dt.date() - MY_BIRTHDAY).days
print(printWithKnownSize(26,"You have lived through") + ": " + str(myAge) + " days, and are an estimated " + str(round(100*myAge/(ESTIMATED_LIFESPAN*365.25),1)) + " % of the way through your life")
print()

# Fireban info
status, msg = firebanInfo(LGA)
print("CURRENT FIREBAN INFO: " + msg)
print()

# Weather info
API_KEY = "af63d2a316f04d04c2cf43809dbdda71"
owm = OWM(API_KEY)
mgr = owm.weather_manager()
observation = mgr.weather_at_place("Perth,AU")
weather = observation.weather

temp = weather.temperature('celsius')
print("WEATHER DATA:")
print(printWithKnownSize(15,"Current temp")   + ": " + str(temp["temp"]) + "°C @ " + str(weather.humidity) + "% humidity")
print(printWithKnownSize(15,"Feels like")     + ": " + str(temp["feels_like"]) + "°C")
print(printWithKnownSize(15,"Air pressure")   + ": " + str(weather.pressure["press"]) + " hPa")
print(printWithKnownSize(15,"Cloud coverage") + ": " + str(weather.clouds) + "%")
print(printWithKnownSize(15,"Wind speed")     + ": " + str(weather.wind()["speed"]) + "m/s @ " + str(weather.wind()["deg"]) + "° with gusts up to " + str(weather.wind()["gust"]) + "m/s")
print(printWithKnownSize(15,"Todays temps")   + ": " + str(temp["temp_min"]) + "C -> " + str(temp["temp_max"]) + "C")
print()

# Forecast weather (next 7 days)
print("FORECAST DATA:")

# 1) Geocode Perth to lat/lon
g = owm.geocoding_manager().geocode(LGA, country="AU", limit=1)[0]

# 2) Hit One Call daily
oc = mgr.one_call(lat=g.lat, lon=g.lon, units="metric", exclude="minutely,hourly,alerts")

# 3) Print date, min/max, rain mm (and PoP) for the next 7 days
for w in oc.forecast_daily[:7]:
    dstr = w.reference_time('date').strftime('%a %d %b')
    
    t = w.temperature()  # keys: min, max, morn, day, eve, night
    tmin = t.get('min')
    tmax = t.get('max')

    # Daily rain in mm is provided on One Call daily as 'rain'; PyOWM maps that to weather.rain
    rain_mm = 0.0
    if w.rain:
        # PyOWM stores daily accumulation as {'all': mm} for daily entries
        rain_mm = w.rain.get('all', 0.0)

    # Probability of precipitation (0..1) if available
    pop = w.precipitation_probability
    pop_pct = f"{round(pop*100)}%" if pop is not None else "—"

    print(f"{printWithKnownSize(15, dstr)}: min {tmin:.1f}°C / max {tmax:.1f}°C | rain {rain_mm:.1f} mm | PoP {pop_pct}")
print()

# Important dates info
print("IMPORTANT DATE")
for date in ImportantDates:
    print("Days until " + printWithKnownSize(15,date[0]) + ": " + str(date[1]))
print()


































for i in range(5):
    print()
input("--- Press Enter to close ---")
