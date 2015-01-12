/*
  Line Follower
  Basic Line Follower for the Picobot ATMega328 Robot
  
  Simply goes forwards, then spins left or right if it senses a line
  Sets the RGB LEDs to Blue - Forwards, Red - LeftSpin, Green - RightSpin
  
  Purpose: Initial test program for shipping
 
  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
 */

int L1 = 2, L2 = 3, L3 = 4, L4 =5; // Pins connected to Motor driver L298N H-Bridge module
#define LED 13  // Blue LED pin
#define RED 9  // Red RGB
#define GREEN A2  // Green RGB
#define BLUE  A3  // Blue RGB
#define LEFTLINE   A6  // Left Line Sensor (Analog) - High values = Reflection (no line)
#define RIGHTLINE  A7  // Right Line Sensor (Analog)

#define LEVEL 300  // level below which it must be over a line

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
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
//  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop()
{
  setColour(LOW, LOW, HIGH); //Red, Green, Blue
  forward(50);  // parameter is delay in ms after performing operation
  while (analogRead(LEFTLINE) < LEVEL)
  {
    setColour(HIGH, LOW, LOW); // Red
    leftSpin(10);
  }
  while (analogRead(RIGHTLINE) < LEVEL)
  {
    setColour(LOW, HIGH, LOW); // Green
    rightSpin(10);
  }
}

void setColour(int r, int g, int b)
{
  digitalWrite(RED, r);
  digitalWrite(GREEN, g);
  digitalWrite(BLUE, b);
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


