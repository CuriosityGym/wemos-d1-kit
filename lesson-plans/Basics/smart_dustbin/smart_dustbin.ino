#include <Servo.h>

Servo myservo;  // create servo object to control a servo

// defines pins numbers
// digital pin D4 and D0 are connected to trigger and echo pin respectively :
const int trigPin = 2;
const int echoPin = 16;

// defines variables
long duration=0;
int distance=0;
int limit = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(13);  // attaches the servo on GIO2 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  int measureDistance = distanceSensor();
  if(measureDistance < limit){
    for(int i=0; i<=180; i++){
      myservo.write(i);
      delay(5);
    }
    delay(5000);
  }
  else{
    myservo.write(0);
  }
}
int distanceSensor(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    return distance;
}
