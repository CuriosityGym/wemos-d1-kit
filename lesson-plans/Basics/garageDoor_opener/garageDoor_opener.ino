a#include <Servo.h>
Servo myservo;  // create servo object to control a servo

// digital pin 2 has a pirSensor attached to it. Give it a name:
int pirSensor = 12;
// digital pins D1,D2,D3 are connected to RGB led.
int redPin= 5;
int greenPin = 4;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
   myservo.attach(13);  // attaches the servo on GIO2 to the servo object
  // make the pirSensor's pin an input:
  pinMode(pirSensor, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int pirState = digitalRead(pirSensor);
  // print out the state of the button:
  Serial.println(pirState);
  delay(1);        // delay in between reads for stability
  if(pirState == 1){
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    myservo.write(90);
  }
  else{
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    myservo.write(0);
  }
}
