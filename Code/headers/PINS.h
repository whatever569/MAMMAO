#ifndef PINS_H
#define PINS_H

//buttons
const int modeSelectorButton = A3;
const int saveButton = 20;

// ultrasonic
const int numUltrasonicSamples = 2;
const int numUltrasonicSensors = 3;
const int ultrasonicSensorsPins[] = {2, 3, 4};

// Define constants for motor pins
const int motor1IN1 = 11;
const int motor1IN2 = 10;
const int motor2IN3 = 6;
const int motor2IN4 = 9;

//flag to enable and disable debug mode, which sends out serial messages
bool debugMode = false;

#endif