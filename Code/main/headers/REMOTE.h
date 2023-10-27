#ifndef REMOTE_H
#define REMOTE_H
#include <SoftwareSerial.h>
#include "MOTOR.h"

SoftwareSerial BT(7, 8);  // TXD to 7, RXD to 8 in this case
int input;

void remoteSetup() {
  BT.begin(9600); // Initialize the bt serial connection
}

void remote() {
  if (remoteStart == false)
  {
    stop();
    remoteStart = true;
  }
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
      if (carSpeed < 9)
      {
        carSpeed++;
        speed();
      }
      break;
    }
    case 'X':
    {
      if (carSpeed >= 0)
      {
        carSpeed--;
        speed();
      }
      break;
    }
  }
}

#endif