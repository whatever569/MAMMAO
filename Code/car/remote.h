#ifndef REMOTE_H
#define REMOTE_H
#include <SoftwareSerial.h>
#include "motor.h"

SoftwareSerial BT(7, 8);  // TXD to 7, RXD to 8 in this case
int input;

void remote() {
  if (BT.available() > 0)
  {
    input = BT.read();
  }
  switch (input)
  {
    case 'F':
    {
      forward();
      break;
    }
    case 'E':
    {
      forward_right();
      break;
    }
    case 'R':
    {
      right();
      break;
    }
    case 'G':
    {
      backward();
      break;
    }
    case 'L':
    {
      left();
      break;
    }
    case 'Q':
    {
      forward_left();
      break;
    }
    case 'S':
    {
      stop();
      break;
    }
    case 'Y':
    {
      if (power < max_power)
      {
        power += interval;
        power_mode++;
      }
      break;
    }
    case 'X':
    {
      if (power > min_power)
      {
        power -= interval;
        power_mode--;
      }
      break;
    }
  }
}

#endif