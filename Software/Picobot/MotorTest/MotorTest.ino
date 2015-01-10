/*
  Motors 01
  Basic motor test for the Picobot ATMega328 Robot
  
  Moves the Lumino forwards, backwards, right rotate, left rotate, halt.
  No speed control is used
  
  Purpose: Basic test to ensure correct connections
 
  This example code is in the public domain.
 */

int L1 = 3, L2 = 2, L3 = 5, L4 =4; // Pins connected to Motor driver L298N H-Bridge module
#define LED 13  // Blue LED pin

// the setup routine runs once when you press reset:
void setup()
{                
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

//  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
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
  digitalWrite(L1, l1);
  digitalWrite(L2, l2);
  digitalWrite(L3, r1);
  digitalWrite(L4, r2);  
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


