<<<<<<< Updated upstream
#include "headers/IR.h"
#include "headers/PINS.h"
#include "headers/AUTOMATED.h"
#include "headers/REMOTE.h"
#include "headers/SELECT.h"
#include "headers/STORAGE.h"
#include "headers/LCD.h"

void setup() {
  Serial.begin(19200);

  remoteSetup();

  motorSetup();
  pinMode(modeSelector);
  LCDSetup();

  
}

void loop() {  
modeSelection();
switch (mode)
{
  case AUTOMATED:
    activate_automated_mode();
  case LINE_TRACKING:
    lineTracking();
  case REMOTE:
    remote();
}
}