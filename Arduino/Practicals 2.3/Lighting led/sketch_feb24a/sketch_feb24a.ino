int red=12;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12,HIGH);

}

