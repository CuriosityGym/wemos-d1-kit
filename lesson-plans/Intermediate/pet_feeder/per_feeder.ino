/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "***************";  //replace with your blynk key

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "********";      // change to your WiFi SSID
char pass[] = "********";  // password for WiFi SSID

Servo servo;
int delayValue = 5000;
int angle = 90;
bool feedDog = false;
unsigned long currentMillis = 0;
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  servo.attach(13);
  servo.write(0);
}

//create virtual pin 1 and read value from that pin
BLYNK_WRITE(V1)
     {
       int value = param.asInt();
       if(value == 1)  //if button pressed on blynk app, start the servo
         {
           feedDog = true;
           currentMillis = millis();
           }     
      
     }    
void loop()
{
  Blynk.run();
   if(feedDog == true &&  millis()-currentMillis  < 5000){
         servo.write(angle);  // tell servo to go to particular positio     
         Serial.println("feed lEO");
       }
       else{
           feedDog = false;
           servo.write(0);    //rotate servo to initial position    
       }
}
