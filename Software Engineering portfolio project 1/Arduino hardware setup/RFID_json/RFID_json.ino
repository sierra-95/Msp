#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h> // Include the ArduinoJson library

#define SS_PIN 10
#define RST_PIN 9
int led1 = A0;
int led2 = A1;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

#define beep_pin 8

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

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
  // Show UID on serial monitor
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

  // Create a JSON object
  StaticJsonDocument<128> jsonDoc;
  jsonDoc["UID"] = content.substring(1);

  // Check access and add "Message" field to the JSON object
  if (content.substring(1) == "C1 29 15 31") // Change here the UID of the card/cards that you want to give access
  {
    jsonDoc["Message"] = "Access granted";
    digitalWrite(beep_pin, HIGH);
    digitalWrite(led1, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(beep_pin, LOW);
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
    jsonDoc["Message"] = "Access denied";
    digitalWrite(beep_pin, HIGH);
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led2, LOW);
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    Serial.println(" Access denied");
    delay(1500);
  }

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Print the JSON data to the serial monitor
  Serial.println("RFID Data:");
  Serial.println(jsonString);
}
