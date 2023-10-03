import serial
import json
import time
import schedule

def main_func():
    arduino = serial.Serial('com6', 9600)
    print('Established serial connection to Arduino')
    arduino_data = arduino.readline()

    try:
        decoded_data = arduino_data.decode("utf-8").strip()
        json_data = json.loads(decoded_data)

        print(f'Collected JSON data from Arduino: {json_data}')
    except json.JSONDecodeError as e:
        print(f'Error decoding JSON data: {e}')

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
