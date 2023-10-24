#include "headers/REMOTE.h"

void remoteSetup() {
  BT.begin(9600); // Initialize the bt serial connection
}

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
      forwardRight();
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
      forwardLeft();
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