/*
  BlinkTest
  Blinks all Picobot LEDs repeatedly.
 
  This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/
 */
 

int blue = 13;
int white = 6;
int rgb_red = 9;
int rgb_green = A2;
int rgb_blue = A3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(blue, OUTPUT);     
  pinMode(white, OUTPUT);     
  pinMode(rgb_red, OUTPUT);     
  pinMode(rgb_green, OUTPUT);     
  pinMode(rgb_blue, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(white, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rgb_red, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(rgb_green, HIGH);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(rgb_blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);               // wait for a second
}
