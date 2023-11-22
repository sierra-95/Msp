#include <Servo.h>
Servo myservo; //creates a servo object used to control the servo
#define POT A0 //specified analog to connect the pot
int potvalue; //reads value from analog pin
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);//servo connected to pin 9(digital) RED-power,Brown-grnd, yellow-info

}

void loop() {
  // put your main code here, to run repeatedly:
  potvalue=analogRead(POT);
  int servo=map(potvalue,0,1023,0,180);
  myservo.write(servo);
  delay(1000);
  potvalue=analogRead(POT);
  servo=map(potvalue,0,1023,180,0);
  myservo.write(servo);
  delay(1000);

  

}
