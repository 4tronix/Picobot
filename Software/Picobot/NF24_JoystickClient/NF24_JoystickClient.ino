/* YourDuinoStarter Example: nRF24L01 Receive Joystick values
 
 - WHAT IT DOES: Receives data from another transceiver with
 2 Analog values from a Joystick or 2 Potentiometers
 Displays received values on Serial Monitor
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
 1 - GND
 2 - VCC 3.3V !!! NOT 5V
 3 - CE to Arduino pin 9
 4 - CSN to Arduino pin 10
 5 - SCK to Arduino pin 13
 6 - MOSI to Arduino pin 11
 7 - MISO to Arduino pin 12
 8 - UNUSED
 
 - V1.00 11/26/13
 Based on examples at http://www.bajdi.com/
 Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   8
#define CSN_PIN 7

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
int motor1a = 2;
int motor1b = 3;
int motor2a = 4;
int motor2b = 5;

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[2];  // 2 element array holding Joystick readings

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode(motor1a, OUTPUT); 
  pinMode(motor1b, OUTPUT); 
  pinMode(motor2a, OUTPUT); 
  pinMode(motor2b, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  ;

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    digitalWrite(motor1a, LOW);
    digitalWrite(motor2a, LOW);
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.print(joystick[0]);
      Serial.print(" Y = ");      
      Serial.println(joystick[1]);
      if ( joystick[0] < 200 ) {
        digitalWrite(motor1b, HIGH);
      } 
      else {
        digitalWrite(motor1b, LOW);
      }
      if ( joystick[1] < 200 ) {
        digitalWrite(motor2b, HIGH);
      } else {
        digitalWrite(motor2b, LOW);
      }
    }
  }
  else
  {    
    Serial.println("No radio available");
  }

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********

