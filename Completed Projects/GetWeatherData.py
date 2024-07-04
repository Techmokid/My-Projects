import requests
from datetime import datetime

LATITUDE = -31.89283
LONGITUDE = 116.01652

# URL for the Open-Meteo API
weather_url = f'https://api.open-meteo.com/v1/forecast?latitude={LATITUDE}&longitude={LONGITUDE}&daily=temperature_2m_max,temperature_2m_min,precipitation_sum&current_weather=true&timezone=Australia/Perth'

def get_weather_data():
    response = requests.get(weather_url)
    if response.status_code == 200:
        data = response.json()
        return data
    else:
        print(f"Error fetching weather data: {response.status_code}")
        return None

def display_current_weather(data):
    current_temp = data['current_weather']['temperature']
    weather_description = data['current_weather']['weathercode']
    print(f"Current temperature: {current_temp}°C")
    print(f"Weather description code: {weather_description}")

def display_forecast(data):
    print("\nWeekly Forecast:")
    for i, daily in enumerate(data['daily']['time']):
        date = datetime.strptime(daily, '%Y-%m-%d')
        temp_max = data['daily']['temperature_2m_max'][i]
        temp_min = data['daily']['temperature_2m_min'][i]
        precipitation = data['daily']['precipitation_sum'][i]

        print(f"{date.strftime('%A, %d %B %Y')}:")
        print(f"Max Temperature: {temp_max}°C")
        print(f"Min Temperature: {temp_min}°C")
        print(f"Precipitation: {precipitation} mm")
        print('-' * 20)

if __name__ == "__main__":
    weather_data = get_weather_data()
    if weather_data:
        print("Current Weather:")
        display_current_weather(weather_data)
        display_forecast(weather_data)
