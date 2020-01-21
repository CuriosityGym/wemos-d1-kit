/* 
   Measure the distance using Ultrasonic sensor and see the value on OLED display
   You can use the onboard Pushbutton of Wemos D1 Kit to change the Units.
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

const int trigPin = 2;
const int echoPin = 16;

int buttonPin = 15;
int count = 0;
long duration;
int inches, cm, mm;

void setup() { 
   Serial.begin(9600);
   pinMode(buttonPin,INPUT);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   u8g2.begin(); // initialize oled display
   u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font   
} 


void loop(){
  
  duration = distanceSensor();
  inches = microsecondsToInches(duration); 
  cm = microsecondsToCentimeters(duration);
  mm = microsecondsToMillimeters(duration);
  Serial.print(inches); 
  Serial.print("in, "); 
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(mm);
  Serial.print(" mm");
  Serial.println();

  
   if(digitalRead(buttonPin) == HIGH) count++;
   if(cm<50 || mm<500 || inches<20){ 
     switch(count){
        Serial.println(count);
        case 0:
           u8g2.clearBuffer();          // clear the internal memory
           u8g2.setFont(u8g2_font_7Segments_26x42_mn); // choose a suitable font
           if(cm<10)u8g2.setCursor(30,50);
           else u8g2.setCursor(10,50);
           u8g2.print(cm);
           u8g2.setFont(u8g2_font_helvB14_te); // choose a suitable font
           if(cm<10) u8g2.drawStr(70,40,"cm");  // write something to the internal memory
           else u8g2.drawStr(85,40,"cm");  // write something to the internal memory
           u8g2.sendBuffer();          // transfer internal memory to the display
           break;
       case 1:
           u8g2.clearBuffer();          // clear the internal memory
           u8g2.setFont(u8g2_font_7Segments_26x42_mn); // choose a suitable font
           if(mm<10)u8g2.setCursor(30,50);
           else if(mm<100) u8g2.setCursor(10,50);
           else u8g2.setCursor(1,50);
           u8g2.print(mm);
           u8g2.setFont(u8g2_font_helvB14_te); // choose a suitable font
           if(mm<10) u8g2.drawStr(80,40,"mm");  // write something to the internal memory
           else if(mm<100) u8g2.drawStr(85,40,"mm");  // write something to the internal memory
           else u8g2.drawStr(95,40,"mm");  // write something to the internal memory
           u8g2.sendBuffer();          // transfer internal memory to the display
           break;
       case 2:
           u8g2.clearBuffer();          // clear the internal memory
           u8g2.setFont(u8g2_font_7Segments_26x42_mn); // choose a suitable font
           if(inches<10)u8g2.setCursor(30,50);
           else u8g2.setCursor(10,50);
           u8g2.print(inches);
           u8g2.setFont(u8g2_font_helvB14_te); // choose a suitable font
           if(inches<10) u8g2.drawStr(70,40,"in");  // write something to the internal memory
           else u8g2.drawStr(85,40,"in");  // write something to the internal memory;
           u8g2.sendBuffer();          // transfer internal memory to the display         
           break;
     }
    }
   else{
    u8g2.clearBuffer();          // clear the internal memory
     u8g2.setFont(u8g2_font_helvB14_te); // choose a suitable font
     u8g2.drawStr(10,30,"out of range");  // write something to the internal memory
     u8g2.sendBuffer();          // transfer internal memory to the display  
   }
   delay(100);   
}

long distanceSensor(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    //float distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance: ");
    //Serial.println(distance);
    return duration;
}

long microsecondsToInches(long microseconds){
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

long microsecondsToMillimeters(long microseconds){
  return microseconds / 2.9 / 2;
}
