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
  pinMode(modeSelectorButton, INPUT_PULLUP);
  LCDSetup();
}

void loop() {  
  modeSelection();
  switch (mode)
  {
    case AUTOMATED:
      activateAutomatedMode();
      break;
    case LINE_TRACKING:
      lineTracking();
      break;
    case REMOTE:
      remote();
      break;
  }
  ledBlink(250);
}