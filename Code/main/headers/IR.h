#ifndef IR_H
#define IR_H

#define irL 5
#define irR 12
#include "ULTRASONIC.h"
#include "MOTOR.h"
#include "PINS.h"
float results[numUltrasonicSensors];

bool isClose(float a, float b, float c);

void irSetup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}

void lineTracking()
{
  motorSpeed = MINSPEED;
  carSpeed = 0;
  ultrasonicSensorsCheck(results, ultrasonicSensorsPins, numUltrasonicSensors, numUltrasonicSamples);
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

bool isClose(float a, float b, float c)
{
  if (a > 10 && b > 10 && c > 10)
  {
    return false;
  }
  else
    return true;
}

#endif