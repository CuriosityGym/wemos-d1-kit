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

#define DHTPIN 12     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
// defines pins numbers

//const int ledPin = 16;
int redPin= 5;
int greenPin = 4;
int bluePin = 0;
// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 15;
int buzzerPin = 14;
const int trigPin = 2;
const int echoPin = 16;

// defines variables
long duration;
int distance;

void setup() {
   delay(1000);
   u8g2.begin();
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
   pinMode(buzzerPin, OUTPUT);
   // make the pushbutton's pin an input:
   pinMode(pushButton, INPUT_PULLUP);
   myservo.attach(13);  // attaches the servo on GIO2 to the servo object

   dht.begin();
   Serial.begin(9600);
  
   for(int i=0; i<5; i++){
     digitalWrite(buzzerPin, HIGH);
     delay(1000);
     digitalWrite(buzzerPin, LOW);
     delay(1000);
    }

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
  
  for(int j=0; j<3; j++){   
     int pos;
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
     for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
   }  
  u8g2.begin();  
}


void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void analogSensor(){
 // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print("LDR: ");
  Serial.print(sensorValue);
  Serial.print("   ");
  Serial.print("vlotage: ");
  Serial.println(voltage);
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
 
void loop() { 
  // Wait a few seconds between measurements.
  //delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
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
  analogSensor();
  int dist = distanceSensor();
  char distanceInCm[5]; 
  String distance1 = String(dist);
  distance1.toCharArray(distanceInCm,5);
  int temp = t;
  int hum = h;
  char temperature[4];
  char humidity[4];
  String tmp = String(temp);
  String hm = String(hum);
  tmp.toCharArray(temperature,4);
  hm.toCharArray(humidity,4);
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  int ldrVal = analogRead(A0);
  Serial.print("ButtonState: ");
  Serial.println(buttonState);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10,"Distance: ");  // write something to the internal memory
  u8g2.drawStr(55,10,distanceInCm);  // write something to the internal memory
  u8g2.drawStr(0,25,"Temperature: ");  // write something to the internal memory
  u8g2.drawStr(80,25,temperature);  // write something to the internal memory
  u8g2.drawStr(0,35,"Humidity: ");  // write something to the internal memory
  u8g2.drawStr(63,35,humidity);  // write something to the internal memory
  u8g2.drawStr(0,45,"Light: ");  // write something to the internal memory
  u8g2.setCursor(40,45);
  u8g2.print(ldrVal);  // write something to the internal memory
  u8g2.drawStr(0,58,"Button State: ");  // write something to the internal memory
  u8g2.setCursor(75,58);
  u8g2.print(buttonState);  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  //delay(1000);  
  //delay(1);        // delay in between reads for stability
   
}
