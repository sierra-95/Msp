#define RED 11
#define POT A0
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int value=analogRead(POT);
  int brightness=map(value,0,1023,0,255);
  analogWrite(RED,brightness);

}
