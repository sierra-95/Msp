#include "DHT.h"
#include <ArduinoJson.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initiating test"));

  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Create a JSON object for DHT11 sensor data
  StaticJsonDocument<100> jsonDoc;
  jsonDoc["Humidity"] = h;
  jsonDoc["TemperatureC"] = t;
  jsonDoc["TemperatureF"] = f;
  jsonDoc["HeatIndexC"] = dht.computeHeatIndex(t, h, false);
  jsonDoc["HeatIndexF"] = dht.computeHeatIndex(f, h);

  // Serialize JSON data and send it to Serial
  serializeJson(jsonDoc, Serial);
  Serial.println(); // Add a newline for clarity
}
