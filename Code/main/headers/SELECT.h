#ifndef SELECT_H
#define SELECT_H
enum Mode{
  AUTOMATED,
  LINE_TRACKING,
  REMOTE
};

int modeCounter = 1;
Mode mode = LINE_TRACKING;

void modeSelection()
{
  if(digitalRead(modeSelectorButton)==LOW)
  {
    modeCounter++;
    if (modeCounter > 2)
    {
      modeCounter = 0;
    }
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