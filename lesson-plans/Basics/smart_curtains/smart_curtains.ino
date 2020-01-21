#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int lowLight = 900;
int ldrValue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(13);  // attaches the servo on GIO2 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:
  ldrValue = analogRead(A0);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if(ldrValue > lowLight){
      myservo.write(120);
  }
  else{
    myservo.write(0);
  }
}
