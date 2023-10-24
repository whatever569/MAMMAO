#include "headers/IR.h"
#include "headers/PINS.h"
#include "headers/AUTOMATED.h"
#include "REMOTE.h"

enum Mode{
  AUTOMATED,
  LINE_TRACKING,
  REMOTE
}

Mode mode = AUTOMATED;
void setup() {
  Serial.begin(19200);
  remote_setup();
}

void loop() {  

switch (mode)
{
  case AUTOMATED:
    activate_automated_mode();
  case LINE_TRACKING:
    line_tracking();
  case REMOTE:
    remote();
}
}