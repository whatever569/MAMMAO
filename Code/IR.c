<<<<<<< Updated upstream
#include "headers/IR.h"
#include "headers/MOTOR.h"
#include "headers/PINS.h"
void irSetup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}

void lineTracking()
{
  ultrasonicSensorsCheck(results, ultrasonic_sensors_pins[], num_ultrasonic_sensors, num_ultrasonic_samples);
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
=======
<<<<<<< HEAD
#define irL 5
#define irR 12
#include "ULTRASONIC.c"
#include "headers/MOTOR.h"

void irSetup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}

void lineTracking()
{
  if (close(results[0], results[1], results[2]))
  {
    stop();
  }
  else if (!close(results[0], results[1], results[2]) && digitalRead(irL) == HIGH)
  {
    left();
  }
  else if (!close(results[0], results[1], results[2]) && digitalRead(irR) == HIGH)
  {
    right();
  }
  else
  {
    forward();
  }
}

bool close(float a, float b, float c)
{
  if (a > 10 && b > 10 && c > 10)
  {
    return false;
  }
  else
    return true;
=======
#include "headers/IR.h"
#include "headers/MOTOR.h"
#include "headers/PINS.h"
void irSetup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}

void lineTracking()
{
  ultrasonicSensorsCheck(results, ultrasonicSensorsPins[], numUltrasonicSensors, numUltrasonicSamples);
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
>>>>>>> e894b15f5837957dc11c5f7fb9940c41308f94c3
>>>>>>> Stashed changes
}