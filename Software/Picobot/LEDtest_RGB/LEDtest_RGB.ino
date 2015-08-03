#include "FastSPI_LED2.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Testing the LEDs on Picobot 1.3 & later
// Sets Red, Green, Blue, White in turn
//    
///////////////////////////////////////////////////////////////////////////////////////////
 

// WS2812B definitions
#define NUM_LEDS 2
#define DATA_PIN 9
CRGB leds[NUM_LEDS];

int blue = 13;
int white = 6;

// This function sets up the ledsand tells the controller about them
void setup()
{
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  allOff();
  pinMode(blue, OUTPUT);     
  pinMode(white, OUTPUT);     
}

int wait = 500;

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop()
{
  allOff();
  digitalWrite(blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(wait);
  digitalWrite(blue, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(white, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(wait);
  digitalWrite(white, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(wait);
  setAll(40,0,0);
  delay(wait);
  setAll(0,40,0);
  delay(wait);
  setAll(0,0,40);
  delay(wait);
  setAll(40,40,40);
  delay(wait);
}

void allOff()
{
  for (int i=0; i<NUM_LEDS; i++)
    leds[i] = 0;
  FastLED.show();
}

void setAll(int red, int green, int blue)
{
  for (int i=0; i<NUM_LEDS; i++)
  {
    leds[i].g = red;
    leds[i].r = green;
    leds[i].b = blue;
  }
  FastLED.show();
}


void pulse(int del, int maxBright, int red, int green, int blue)
{
  for (int i = 0; i<maxBright; i++)
  {
    for (int j=0; j<NUM_LEDS; j++)
    {
      leds[j].g = (i*red) >> 8;
      leds[j].r = (i*green) >> 8;
      leds[j].b = (i*blue) >> 8;
    }
    FastLED.show();
    delay(del);
  }
  for (int i = maxBright; i>=0; i--)
  {
    for (int j=0; j<NUM_LEDS; j++)
    {
      leds[j].g = (i*red) >> 8;
      leds[j].r = (i*green) >> 8;
      leds[j].b = (i*blue) >> 8;
    }
    FastLED.show();
    delay(del);
  }
}

void flicker()
{
   int i;
   // Move a single white led 
   for(i = 0; i < NUM_LEDS; i++)
   {
      // Turn our current led on to white, then show the leds
      leds[i] = CRGB::Red;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(100);

      // Turn our current led back to black for the next loop around
      leds[i] = CRGB::Green;
      if(i>0)
        leds[i-1] = CRGB::Black;
   }
   for(--i; i>=0; i--)
   {
     leds[i] = CRGB::Blue;
     FastLED.show();
     delay(100);
     leds[i] = CRGB::Green;
     if(i<NUM_LEDS-1)
       leds[i+1] = CRGB::Black;
   }

}
