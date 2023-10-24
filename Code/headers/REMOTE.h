#ifndef REMOTE_H
#define REMOTE_H
#include <SoftwareSerial.h>
#include "MOTOR.h"

SoftwareSerial BT(7, 8);  // TXD to 7, RXD to 8 in this case
int input;
<<<<<<< Updated upstream
void remoteSetup();
void remote();
=======
<<<<<<< HEAD

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
      if (power < maxPower)
      {
        power += interval;
        powerMode++;
      }
      break;
    }
    case 'X':
    {
      if (power > minPower)
      {
        power -= interval;
        powerMode--;
      }
      break;
    }
  }
}
=======
void remoteSetup();
void remote();
>>>>>>> e894b15f5837957dc11c5f7fb9940c41308f94c3
>>>>>>> Stashed changes

#endif