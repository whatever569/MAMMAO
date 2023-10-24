#define irL 5
#define irR 12
#include "ULTRASONIC.c"
#include "headers/MOTOR.h"

void ir_setup()
{
  pinMode(irL, INPUT);
  pinMode(irR, INPUT);
}

void line_tracking()
{
  if (close(results[0], results[1], results[2]))
  {
    Stop();
  }
  else if (!close(results[0], results[1], results[2]) && digitalRead(irL) == HIGH)
  {
    Left();
  }
  else if (!close(results[0], results[1], results[2]) && digitalRead(irR) == HIGH)
  {
    Right();
  }
  else
  {
    Forward();
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
}