void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12,HIGH);
  digitalWrite(11,LOW);
  delay(1000);
  digitalWrite(12,LOW);
  digitalWrite(11,HIGH);
  delay(1000);

}
