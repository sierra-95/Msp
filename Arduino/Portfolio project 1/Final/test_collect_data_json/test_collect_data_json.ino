const int potentiometerPin = A0; // Analog pin where the potentiometer is connected

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(potentiometerPin); // Read analog value
  Serial.println(sensorValue); // Print the value to the serial monitor
  delay(1000); // Delay for one second (adjust as needed)
}
