#ifndef IR_H
#define IR_H

#define irL 5
#define irR 12
#include "ULTRASONIC.h"
#include "MOTOR.h"
#include "PINS.h"
float results[numUltrasonicSensors];
int irTime = 0;
int irDelay = 50;

bool isClose(float a, float b, float c);

void irSetup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}
void lineTracking()
{
  carSpeed = 0;
  ultrasonicSensorsCheck(results, ultrasonicSensorsPins, numUltrasonicSensors, numUltrasonicSamples);
  if (isClose(results[0], results[1], results[2]))
  {
    stop();
  }
  else if (!isClose(results[0], results[1], results[2]) && digitalRead(irL) == HIGH)
  {
    backward();
    delay(35);
    left();
  }
  else if (!isClose(results[0], results[1], results[2]) && digitalRead(irR) == HIGH)
  {
    backward();
    delay(35);
    right();
  }
  else
  {
    forward();
  }
  if (debugMode == true)
  {
    Serial.print(digitalRead(irL));
    Serial.print("  ");
    Serial.println(digitalRead(irR));
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