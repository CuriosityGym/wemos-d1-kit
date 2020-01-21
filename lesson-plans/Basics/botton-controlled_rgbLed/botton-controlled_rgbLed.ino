

int buzzerPin = 14;
const byte buttonPin=15;
// digital pins D1,D2,D3 are connected to RGB led.
int redPin= 5;
int greenPin = 4;
int bluePin = 0;
int counter;

void setup()
    {
      Serial.begin(9600);
      pinMode(redPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
      pinMode(bluePin, OUTPUT);
      pinMode(buzzerPin, OUTPUT); //set buzzer as Output
      // make the pushbutton's pin an input:
      pinMode(buttonPin, INPUT_PULLUP);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, LOW);
    }
  
void loop()
    {  
       pushbutton();
       if(pushbutton())
       { 
         beep(250);
         counter++;
         Serial.println(counter);
         switch(counter) 
              { 
                case 1: color(127,0,255);
                break;
                  
                case 2: color(0,0,255);
                break;
                  
                case 3: color(0,255,0);
                break;
                  
                case 4: color(255,255,0);
                break;
                  
                case 5: color(255,128,0);
                break; 
                  
                case 6: color(255,0,0);
                break; 
                  
                case 7: color(255,255,255);
                break;
                  
                case 8: color(0,0,0);    
                break;    
              } 
       }
      if(counter==8) counter = 0; 
      
    }
//function to check input from pushbutton
int pushbutton()
   {
     int touched = digitalRead(buttonPin); 
     if(touched == HIGH)   // check if the input is HIGH 
     
     return true;
     else
     return false;
   }
   
void beep(int delayValue)
     {
       digitalWrite(buzzerPin,HIGH);
       delay(delayValue);
       digitalWrite(buzzerPin,LOW);
     }
void color(int r, int g, int b){
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
     
