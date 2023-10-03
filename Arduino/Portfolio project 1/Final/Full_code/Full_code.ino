#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include "DHT.h"

#define SS_PIN 10
#define RST_PIN 9
int led1 = A0;
int led2 = A1;
#define beep_pin 8
DHT dht(8, DHT11); // DHT sensor on pin 8
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600); // Initiate a serial communication

  pinMode(beep_pin, OUTPUT);
  digitalWrite(beep_pin, LOW);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(3, 1);
  lcd.print("Welcome!!");
  lcd.setCursor(0, 0);
  lcd.print("System all set");
  delay(1500);
  lcd.clear();

  SPI.begin();      // Initiate SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();

  dht.begin(); // Initialize DHT sensor
}

void loop()
{
  digitalWrite(beep_pin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put your card to");
  lcd.setCursor(0, 1);
  lcd.print("the reader......");
  delay(300);

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Show UID on the serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "C1 29 15 31") // Change here the UID of the card/cards that you want to give access
  {
    digitalWrite(beep_pin, HIGH);
    digitalWrite(led1, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(beep_pin, LOW);
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Authorized access");
    Serial.println("Authorized access");
    delay(3500);
  }
  else
  {
    digitalWrite(beep_pin, HIGH);
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led2, LOW);
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    Serial.println("Access denied");
    delay(1500);
  }

  // Reading temperature and humidity from DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (!isnan(h) && !isnan(t))
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.println("°C");
  }
  delay(5000); // Delay for 5 seconds before the next loop
}
