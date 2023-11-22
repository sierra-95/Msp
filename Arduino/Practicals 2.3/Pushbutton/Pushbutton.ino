#define RED 8
#define PUSH 7
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(7,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(PUSH)==HIGH)
  {
    digitalWrite(RED,HIGH);
  }
  else
  {
    digitalWrite(RED,LOW);
  }

}
