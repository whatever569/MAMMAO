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
      if (speedMode < 10)
      {
        speedMode++;
      }
      break;
    }
    case 'X':
    {
      if (speedMode >= 0)
      {
        speedMode--;
      }
      break;
    }
  }
}