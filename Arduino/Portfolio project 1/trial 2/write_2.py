import serial
import json

# Define the serial port and baud rate
ser = serial.Serial('com7', 9600)

# Create a function to save data to a file
def save_data(data):
    with open('data.txt', 'a') as file:
        file.write(data + '\n')

while True:
    try:
        # Read data from the serial port
        line = ser.readline().decode("utf-8").strip()
        
        # Check if the received data is a valid JSON
        try:
            json_data = json.loads(line)
        except json.JSONDecodeError:
            print("Invalid JSON data received:", line)
            continue

        # Print the received JSON data for verification
        print("Received JSON data:", json_data)

        # Save the JSON data to the file
        save_data(line)

    except KeyboardInterrupt:
        # Exit the loop if Ctrl+C is pressed
        ser.close()
        break
