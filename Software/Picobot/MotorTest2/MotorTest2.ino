/*
  MotorTest
  Basic motor test for the Picobot ATMega328 Robot
  
  Moves the Picobot forwards, backwards, right rotate, left rotate, halt.
  No speed control is used
  
  Purpose: Basic test to ensure correct connections
 
  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
 */

#include "FastSPI_LED2.h"

int L1 = 2, L2 = 3, L3 = 4, L4 =5; // Pins connected to Motor driver L298N H-Bridge module
#define LED 13  // Blue LED pin

// WS2812B definitions
#define NUM_LEDS 2
#define DATA_PIN 9
CRGB leds[NUM_LEDS];


// the setup routine runs once when you press reset:
void setup()
{                
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  allOff();
  // initialize the digital pins we will use as an output.
  pinMode(L1, OUTPUT);     
  pinMode(L2, OUTPUT);     
  pinMode(L3, OUTPUT);     
  pinMode(L4, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop()
{
  ledOn();
  forward(2000);  // parameter is delay in ms after performing operation
  ledOff();
  halt(500);
  ledOn();
  reverse(2000);
  ledOff();
  halt(500);
  ledOn();
  leftSpin(2000);
  ledOff();
  halt(500);
  ledOn();
  rightSpin(2000);
  ledOff();
  halt(1000);
}

void ledOn()
{
  digitalWrite(LED, HIGH);
}

void ledOff()
{
  digitalWrite(LED, LOW);
}


// robMove routine switches the correct inputs to the L298N for the direction selected.
void robMove(int l1, int l2, int r1, int r2)
{
  digitalWrite(L2, l1);
  digitalWrite(L1, l2);
  digitalWrite(L4, r1);
  digitalWrite(L3, r2);  
}

void reverse(int wait)
{
  Serial.println("Moving backward");
  robMove(LOW, HIGH, HIGH, LOW);
  delay(wait);
}

void forward(int wait)
{
  Serial.println("Moving forward");
  robMove(HIGH, LOW, LOW, HIGH);
  delay(wait);
}

void rightSpin(int wait)
{
  Serial.println("Spinning right");
  robMove(HIGH, LOW, HIGH, LOW);
  delay(wait);
}

void leftSpin(int wait)
{
  Serial.println("Spinning left");
  robMove(LOW, HIGH, LOW, HIGH);
  delay(wait);
}

void halt(int wait)
{
  Serial.println("Stopping");
  robMove(LOW, LOW, LOW, LOW);
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



