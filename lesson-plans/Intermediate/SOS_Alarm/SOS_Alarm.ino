

#include <ESP8266WiFi.h>

const char* ssid = "*******";  // change to your WiFi SSID
const char* password = "**********"; //password for WiFi SSID
const char* host = "maker.ifttt.com";
const char* apiKey = "******************";  // change to your IFTTT key

// digital pin D8 has a pushbutton attached to it. Give it a name:
int pushButton = 15;
int buttonState=0;
volatile int state = false;

const char* button_state = "closed";




void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("Preparing the Door Status Monitor project...");
    
    // make the pushbutton's pin an input:
    pinMode(pushButton, INPUT_PULLUP);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  

    Serial.print("connecting to ");
          Serial.println(host);
          
  
          
}

void loop() {
          WiFiClient client;
          const int httpPort = 80;
          buttonState = digitalRead(pushButton);
          Serial.print("Button State: ");
          Serial.println(buttonState);
          if(buttonState == 0){
            if (!client.connect(host, httpPort)) {
              Serial.println("connection failed");
              return;
            }
      
            String url = "/trigger/iot_workshop_3/with/key/";
            url += apiKey;
            
            Serial.print("Requesting URL: ");
            Serial.println(url);
            client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" + 
                         "Content-Type: application/x-www-form-urlencoded\r\n" + 
                         "Content-Length: 13\r\n\r\n" +
                         "value1=" + button_state + "\r\n");
  
             delay(30000); 
          }             

}
