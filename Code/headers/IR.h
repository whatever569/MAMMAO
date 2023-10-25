#ifndef IR_H
#define IR_H

//define IR pins constants
#define irL 5
#define irR 12

#define THRESHOLD 10

// Include header file for the ultrasonic to check the distance and Motor file for the directions and pins
#include "ULTRASONIC.h"
#include "MOTOR.h"
#include "PINS.h"

//Decleare an array to store the reading sof the ultrasonic sensors
int results[numUltrasonicSensors];

//decleare IR sensor setup function
void irSetup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}

//Function for performing the Line Tracking using the Ultrasonic and IR sesnsors simultaneously 
void lineTracking()
{
  //Getting the ultrasonic sesnsor readings
  ultrasonicSensorsCheck(results, ultrasonicSensorsPins[], numUltrasonicSensors, numUltrasonicSamples);
  //Check If any object is close based on the ultrasonic sensor readings
  if (isClose(results[0], results[1], results[2]))
  {
    stop();
  }
  else if (!isClose(results[0], results[1], results[2]) && digitalRead(irL) == HIGH)
  {
    left();
  }
  else if (!isClose(results[0], results[1], results[2]) && digitalRead(irR) == HIGH)
  {
    right();
  }
  else
  {
    forward();
  }
}
//Function to check if theres any object close to the car based on the ultrasonic sensor readings
bool isClose(float a, float b, float c)
{
  if (a > THRESHOLD && b > THRESHOLD && c > THRESHOLD)
  {
    return false;
  }
  else
    return true;
}

#endif
