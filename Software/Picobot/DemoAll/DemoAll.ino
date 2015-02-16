/*
  Demo All
  Shows a number of features of the PicoBot and uses the Mode switch to change Operation
  
  1) Flashing Lights
  2) Line Follower
  3) Light seeker
  4) Obstacle avoider (not every Picobot has ultrasonic)
  5) Constant distance (not every Picobot has ultrasonic)
  
  Purpose: Initial test program for shipping
 
  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
 */

int L1 = 2, L2 = 3, L3 = 4, L4 =5; // Pins connected to Motor driver L298N H-Bridge module
#define blue 13  // Blue LED pin
#define white 6  // Rear white LED
#define rgb_red 9  // Red RGB
#define rgb_green A2  // Green RGB
#define rgb_blue  A3  // Blue RGB
#define LEFTLINE   A6  // Left Line Sensor (Analog) - High values = Reflection (no line)
#define RIGHTLINE  A7  // Right Line Sensor (Analog)
#define SWITCH 10  // Mode button on D10
#define LEFTLDR A0 // Left light sensor
#define RIGHTLDR A1 // Right light sensor
int trigPin = A4;   // Analog pin 4 used for the Ping Pin (Trig)
int echoPin = A5;   // Analog pin 5 used for the Echo Pin (Echo)
unsigned long duration, inches;
int indec, cmdec;
int inchconv = 147; // ratio between pulse width and inches
int cmconv = 59;    // ratio between pulse width and cm



#define LEVEL 300  // level below which it must be over a line
#define HYSTERESIS 50  // difference in analog readings for LDR to make it turn in light follower

#define FLASH 1
#define LINE 2
#define LIGHT 3
#define AVOIDER 4
#define CONSTDIST 5
#define LASTPROG 5

int state = 1;  // initial state is 1) Line Follower
int lastButton = HIGH;  // Initial state of button is OFF

// the setup routine runs once when you press reset:
void setup()
{                
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  // delay(2000);

//  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // initialize the digital pins we will use as an output.
  pinMode(L1, OUTPUT);     
  pinMode(L2, OUTPUT);     
  pinMode(L3, OUTPUT);     
  pinMode(L4, OUTPUT);
  pinMode(blue, OUTPUT);     
  pinMode(white, OUTPUT);     
  pinMode(rgb_red, OUTPUT);     
  pinMode(rgb_green, OUTPUT);     
  pinMode(rgb_blue, OUTPUT);     
  pinMode(trigPin, OUTPUT);
  digitalWrite(SWITCH, HIGH);  // add pullup to mode button
  digitalWrite(LEFTLDR, HIGH);
  digitalWrite(RIGHTLDR, HIGH);
  Serial.begin(115200);
  FlashAll(200);  // Sign on with a slow flashing display
}

// the loop routine runs over and over again forever:
// runs one iteration of the relevant program, then checks the mode button
// moves to next state if mode button pressed and flashes LED correct number of times
void loop()
{
  switch (state)
  {
    case 1:
      flashLEDs();
      break;
    case 2:
      lineFollow();
      break;
    case 3:
      lightSeek();
      break;
    case 4:
      obstacleAvoid();
      break;
    case 5:
      constDistance();
      break;
  }
  if (getButton()==1)
  {
    halt(0);
    state++;
    if (state > LASTPROG)
      state = 1;
    flashCount(state);
    Serial.println("New state: " + String(state));
  }
}

void flashLEDs()  // State 1
{
  FlashAll(30);
}

void lineFollow()  // State 2
{
  if (analogRead(LEFTLINE) < LEVEL)
  {
    setColour(HIGH, LOW, LOW); // Red
    leftSpin(10);
  }
  else if (analogRead(RIGHTLINE) < LEVEL)
  {
    setColour(LOW, HIGH, LOW); // Green
    rightSpin(10);
  }
  else
  {
    setColour(LOW, LOW, HIGH);  // Blue
    forward(10);
  }
}

void lightSeek()  // State 3
{
  int ldrL = analogRead(LEFTLDR);
  int ldrR = analogRead(RIGHTLDR);
  if (ldrL < (ldrR - HYSTERESIS))
  {
    setColour(HIGH, LOW, LOW); // Red
    leftSpin(10);
  }
  else if (ldrR < (ldrL - HYSTERESIS))
  {
    setColour(LOW, HIGH, LOW); // Green
    rightSpin(10);
  }
  else
  {
    setColour(LOW, LOW, HIGH);  // Blue
    forward(10);
  }
}

void obstacleAvoid() // State 4
{
  int cm = getDistance();
  Serial.println("Distance: " + String(cm));
  if (cm  < 8)
  {
    setColour(HIGH, HIGH, LOW);  // Yellow
    reverse(1000);
    setColour(LOW, HIGH, LOW);  // Green
    rightSpin(1000);
  }
  else
  {
    setColour(LOW, LOW, HIGH);  // Blue
    forward(10);
  }
}

void constDistance()  // State 5
{
  int cm = getDistance();
  Serial.println("Distance: " + String(cm));
  if (cm  < 10)
  {
    setColour(HIGH, HIGH, LOW);  // Yellow
    reverse(10);
  }
  else if (cm > 10)
  {
    setColour(LOW, LOW, HIGH);  // Blue
    forward(10);
  }
  else
  {
    setColour(HIGH, HIGH, HIGH);  // White
    halt(10);
  }
}

void FlashAll(int rate)
{
  digitalWrite(blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(rate);               // wait for a second
  digitalWrite(blue, LOW);    // turn the LED off by making the voltage LOW
  delay(rate);               // wait for a second

  digitalWrite(white, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(rate);               // wait for a second
  digitalWrite(white, LOW);    // turn the LED off by making the voltage LOW
  delay(rate);               // wait for a second

  digitalWrite(rgb_red, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(rate);               // wait for a second
  digitalWrite(rgb_red, LOW);    // turn the LED off by making the voltage LOW
  delay(rate);               // wait for a second

  digitalWrite(rgb_green, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(rate);               // wait for a second
  digitalWrite(rgb_green, LOW);    // turn the LED off by making the voltage LOW
  delay(rate);               // wait for a second

  digitalWrite(rgb_blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(rate);               // wait for a second
  digitalWrite(rgb_blue, LOW);    // turn the LED off by making the voltage LOW
  delay(rate);               // wait for a second
}

void setColour(int r, int g, int b)
{
  digitalWrite(rgb_red, r);
  digitalWrite(rgb_green, g);
  digitalWrite(rgb_blue, b);
}


// robMove routine switches the correct inputs to the L298N for the direction selected.
void robMove(int l1, int l2, int r1, int r2)
{
//  return;  // uncomment the return; for desktop coding!
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

int getButton()
{
  int newB = digitalRead(SWITCH);
//  Serial.println("Button = " + String(newB));
  if (newB==LOW and lastButton==HIGH)
  {
    lastButton = LOW;
    return 1;
  }
  lastButton = newB;
  return 0;
}

void flashCount(int count)
{
  for (int i=0; i<count; i++)
  {
    setAllLEDs(HIGH);
    delay(300);
    setAllLEDs(LOW);
    delay(300);
  }
}

void setAllLEDs(int val)
{
  digitalWrite(blue, val);
  digitalWrite(white, val);
  setColour(LOW, val, LOW);
}

int getDistance()
{
  int rval;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 38000L);  // Set timeout to 38mS
  rval = microsecondsToCentimeters(duration);
  Serial.println(rval);
  return rval;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / cmconv;
}

