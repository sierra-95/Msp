import serial
import time
import schedule
import json

def main_func():
    arduino = serial.Serial('com6', 9600)
    print('Established serial connection to Arduino')
    arduino_data = arduino.readline().decode("utf-8").strip()

    try:
        json_data = json.loads(arduino_data)
        with open('data.txt', 'a') as file:
            json.dump(json_data, file)
            file.write('\n')

        print(f'Collected JSON data from Arduino: {json_data}')
    except json.JSONDecodeError:
        print(f'Invalid JSON data received: {arduino_data}')

    arduino.close()
    print('Connection closed')
    print('<----------------------------->')

# ----------------------------------------Main Code------------------------------------
print('Program started')

# Setting up the Arduino
schedule.every(10).seconds.do(main_func)

while True:
    schedule.run_pending()
    time.sleep(1)
