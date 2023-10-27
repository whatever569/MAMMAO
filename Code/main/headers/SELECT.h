#ifndef SELECT_H
#define SELECT_H

#include "DATA.h"

int buttonState;
int prev = 1;

void modeSelection()
{
  buttonState = digitalRead(modeSelectorButton);
  if(buttonState == 0 && prev == 1)
  {
    modeCounter++;
    if (modeCounter > 2)
    {
      modeCounter = 0;
    }
    Serial.println("Button pressed");
    prev = buttonState;
  }
  if (buttonState == 1)
  {
    prev = buttonState;
  }

  switch (modeCounter)
  {
    case 0:
      mode = AUTOMATED;
      break;
    case 1: 
      mode = LINE_TRACKING;
      break;  
    case 2:
      mode = REMOTE;
      break;
    default:
      mode = AUTOMATED;
      break;
  }
}

#endif