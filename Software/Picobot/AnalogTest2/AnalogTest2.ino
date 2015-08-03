// Picobot Analog Inputs Test
// This code is designed for the 4tronix Picobot
// Reads values from the 2 LDRs and the 2 Line Follower Sensors
//
// Purpose: Demonstrate use of the analog sensors 
//
// This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/

#include "FastSPI_LED2.h"

int leftLDR = A0;
int rightLDR = A1;
int leftLine = A6;
int rightLine = A7;
int led = 13;

// WS2812B definitions
#define NUM_LEDS 2
#define DATA_PIN 9
CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  allOff();
  Serial.begin(115200);
  // Initialise pull downs on LDR inputs
  digitalWrite(leftLDR, HIGH);
  digitalWrite(rightLDR, HIGH);
  pinMode(led, OUTPUT);
}

void loop()
{
  int ldrL, ldrR, lineL, lineR;
  ldrL = analogRead(leftLDR);
  ldrR = analogRead(rightLDR);
  lineL = analogRead(leftLine);
  lineR = analogRead(rightLine);
  String s = "Left LDR: " + String(ldrL) + "  Right LDR: " + String(ldrR) + "  Left Line: " + String(lineL) + "  Right Line: " + String(lineR);
  Serial.println(s);
  delay(1000);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
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



