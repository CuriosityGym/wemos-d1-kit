#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    12

// How many NeoPixels are attached to the Arduino?
#define PixelCount 8

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PixelCount, LED_PIN, NEO_GRB + NEO_KHZ800);
/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
byte gammatable[256];
void setup(void) {
  Serial.begin(9600);
   strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    gammatable[i] = x;      
  } 
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
   unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  // Figure out some basic hex code for visualization
  uint32_t sum = c;
  float red, green, blue;
  red = r; red /= sum;
  green = g; green /= sum;
  blue = b; blue /= sum;
  red *= 256; green *= 256; blue *= 256;
  Serial.print("\t");
  Serial.print((int)red, HEX); Serial.print((int)green, HEX); Serial.print((int)blue, HEX);
  Serial.println();

  Serial.print((int)red ); Serial.print(" "); Serial.print((int)green);Serial.print(" ");  Serial.println((int)blue );

 // Basic RGB color differentiation can be accomplished by comparing the values and the largest reading will be 
 // the prominent color

  if((r>b) && (r>g))
    Serial.println("detecting red");
  else if((g>b) && (g>r))
    Serial.println("detecting green");
  else if((b>r) && (b>g))
    Serial.println("detecting blue");
  else
    Serial.println("color not detectable");

 for(int i =0; i<PixelCount;i++){
 // strip.setPixelColor(0,r,g,b); 
  //strip.setPixelColor(i,gammatable[(int)r],gammatable[(int)g],gammatable[(int)b]);
  strip.setPixelColor(i, gammatable[(int)red],gammatable[(int)green],gammatable[(int)blue]);
 }
  strip.show();/*
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");*/
}
