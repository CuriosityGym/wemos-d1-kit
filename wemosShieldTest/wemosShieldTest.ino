#include "DHT.h"
#include <Servo.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display


#define DHTPIN 12     // Digital pin D6 connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE); //// create dht object to read values from dht senosr. 

Servo myservo;  // create servo object to control a servo

// defines pins numbers
// digital pin D4 and D0 are connected to trigger and echo pin respectively :
const int trigPin = 2;
const int echoPin = 16;

// digital pins D1,D2,D3 are connected to RGB led.
int redPin= 5;
int greenPin = 4;
int bluePin = 0;

// digital pin D8 has a pushbutton attached to it. Give it a name:
int pushButton = 15;

// digital pin D5 has a pushbutton attached to it. Give it a name:
int buzzerPin = 14;

// defines variables
long duration=0;
int distance=0;
int buttonState=0;
int ldrVal=0;
float h=0;
float t=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //set RGB led pins as Output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT); //set buzzer as Output
   // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT_PULLUP);
  
  myservo.attach(13);  // attaches the servo on GIO2 to the servo object

  dht.begin(); // to initialize the dht sensor
  
  //BUZZER TEST CODE
  for(int i=0; i<5; i++){
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }
  delay(1000);
  buzzer_TEST();
  delay(1000);

  //RGB LED TEST CODE
   digitalWrite(greenPin, LOW);
   digitalWrite(bluePin, LOW);
   for(int j=0; j<3; j++){
      digitalWrite(redPin, HIGH);
      delay(500);
      digitalWrite(redPin, LOW);
      delay(500);  
    }
   digitalWrite(redPin, LOW);
   digitalWrite(bluePin, LOW);
   for(int j=0; j<3; j++){
      digitalWrite(greenPin, HIGH);
      delay(500);
      digitalWrite(greenPin, LOW);
      delay(500);  
    }
   digitalWrite(greenPin, LOW);
   digitalWrite(redPin, LOW);
   for(int j=0; j<3; j++){
      digitalWrite(bluePin, HIGH);
      delay(500);
      digitalWrite(bluePin, LOW);
      delay(500);  
    } 
  
  // TEST CODE FOR SERVO
  for(int j=0; j<3; j++){   
   int pos;

    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }  

  
  u8g2.begin(); // initialize oled display

}

void loop() {
  // put your main code here, to run repeatedly:
  measureTemperature();
  ldrSensor();
  pushbutton();
  distanceSensor();
  displayOled();
}

//measure temperature
void measureTemperature(){
    // Wait a few seconds between measurements.
    //delay(2000);
  
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    
    // print out the state of the button:
    Serial.println();
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.println();
}

void ldrSensor(){
    ldrVal = analogRead(A0);
    Serial.print("LDR Value: ");
    Serial.println(ldrVal);
}

void pushbutton(){
    buttonState = digitalRead(pushButton);
    Serial.print("Button State: ");
    Serial.println(buttonState);
}


void distanceSensor(){
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

}

void displayOled(){
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10,"Distance: ");  // write something to the internal memory
  //u8g2.drawStr(55,10,distanceInCm);  // write something to the internal memory
  u8g2.setCursor(55,10);
  u8g2.print(distance);
  u8g2.drawStr(0,25,"Temperature: ");  // write something to the internal memory
  //u8g2.drawStr(80,25,temperature);  // write something to the internal memory
  u8g2.setCursor(80,25);
  u8g2.print(t);
  u8g2.drawStr(0,35,"Humidity: ");  // write something to the internal memory
  //u8g2.drawStr(63,35,humidity);  // write something to the internal memory
  u8g2.setCursor(63,35);
  u8g2.print(h);
  u8g2.drawStr(0,45,"Light: ");  // write something to the internal memory
  u8g2.setCursor(40,45);
  u8g2.print(ldrVal);  // write something to the internal memory
  u8g2.drawStr(0,58,"Button State: ");  // write something to the internal memory
  u8g2.setCursor(75,58);
  u8g2.print(buttonState);  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display 
}

void buzzer_TEST()
    { 
      
     // notes in the melody:
     int melody[]= {196, 196, 220, 196, 262, 247, 196, 196, 220, 196, 294, 262, 
                    196, 196, 392, 330, 262, 247, 220, 349, 349, 330, 262, 294, 262 };
     // note durations: 4 = quarter note, 8 = eighth note, etc.:
     int noteDurations[] = { 8,8,4,4,4,2,8,8,4,4,4,2,8,8,4,4,4,4,3,8,8,4,4,4,2 };

     // iterate over the notes of the melody: 
     for(byte thisNote = 0; thisNote < 26; thisNote++) 
        {
         // to calculate the note duration, take one second 
         // divided by the note type.
         //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
         int noteDuration = 1000/noteDurations[thisNote];
         tone(buzzerPin, melody[thisNote],noteDuration);
         // to distinguish the notes, set a minimum time between them.
         // the note's duration + 30% seems to work well:
         int pauseBetweenNotes = noteDuration * 1.60;
         delay(pauseBetweenNotes);
         // stop the tone playing:
         noTone(buzzerPin);
        }
    
    }
//
