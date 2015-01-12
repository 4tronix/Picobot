// Picobot Ultrasonic Test
// This code is designed for the 4tronix Picobot
// Using an HC-SR04 Ultrasonic Sensor
//
// Purpose: Demonstrate use of the ultrasonic sensor 
//
// This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/

#include <Servo.h> // need the standard Arduino servo library


int trigPin = A4;   // Analog pin 0 used for the Ping Pin (Trig)
int echoPin = A5;   // Analog pin 1 used for the Echo Pin (Echo)
unsigned long duration, inches;
int indec, cmdec;
int inchconv = 147; // ratio between pulse width and inches
int cmconv = 59;    // ratio between pulse width and cm

void setup()
{
  Serial.begin(115200);
 
  // initialize the ultrasonic sensor pins and centre the servos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  int cm, lcm, rcm;
  cm = getDistance();
  Serial.println(cm);
  delay(1000);
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



