import requests

def get_weather(api_key, city):
    base_url = "http://api.weatherstack.com/current"
    params = {
        'access_key': api_key,
        'query': city,
    }

    response = requests.get(base_url, params=params)

    if response.status_code == 200:
        weather_data = response.json()
        return weather_data
    else:
        return None

def format_weather(weather_data):
    if weather_data and 'current' in weather_data:
        description = weather_data['current']['weather_descriptions'][0]
        temperature = weather_data['current']['temperature']
        return f'Сейчас {description} с температурой {temperature}°C'
    else:
        return 'Не удалось получить данные о погоде'

# Замените 'YOUR_API_KEY' на свой API-ключ от Weatherstack
api_key = 'e267f120a8342928c0f0a410fa25d709'
city = 'Moscow'  # Замените на нужный город

# Пример использования
command = input("Введите команду: ")

if command.lower() == 'погода':
    weather_data = get_weather(api_key, city)
    print(format_weather(weather_data))
else:
    print('Неправильная команда')