Picobot Released Files
======================

All files are Licensed under Creative Commons BY-SA
See creativecommons.org/licenses/by-sa/3.0/ for details


CP2102 programming cable requires drivers from: silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx

When using the Arduino IDE, select board type UNO. The Picobot is fully compatible with the UNO


Note - v1.3 and later Versions
==============================
Version 1.3 and 1.4 of the Picobot PCB use neopixel LEDs instead of standard RGB LEDs and this means that they
are individually addressable so you can have different colours on the left and the right.

The versions of the software below with the suffix '2' indicate that they are built for use with neopixels

You must install the Arduino library FastLED2 for these examples to work.



Picobot Software
================
DemoAll - Uses the Mode button to switch between 5 different demos. After pressing the button it flashes the LEDs the number of times for the following demos:
	1. Flash all the LEDs
	2. Line Follower
	3. Light Seeker
	4. Obstacle avoider
	5. Constant distance
AllLeds - Lights all the LEDs
BlinkTest - Flashes all the LEDs one at a time
AnalogTest - outputs analog values from light and line following sensors to Serial Monitor
MotorTest - Turns the motors Forwards, Reverse, Spin Left, Spin Right, Halt in turn
Utra - Outputs the distance reading from teh Ultrasonic sensor to the Serial Monitor
Runaway - Uses the Picobot library and ultrasonic sensor to avoid objects
LineFollower - Simple line follower script using the RGB LEDs to show direction

Picobot Schematics
==================
Picobot<xy>.sch is the Eagle schematic for version x.y
Picobot<xy>.brd is the Eagle board file for version x.y
