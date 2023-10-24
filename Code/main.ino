<<<<<<< Updated upstream
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
  remoteSetup();
}

void loop() {  
=======
<<<<<<< HEAD
#include "ULTRASONIC.c"

int modeToBeActivated = 1;
void setup() {
  Serial.begin(19200);
  // remoteSetup();
  // motorSetup();
  ultrasonic_sensors_setup(trig_ultrasonic_sensor, echo_ultrasonic_sensor, numUltrasonicSensors);
}

void loop() {  
activateAutomatedMode();
=======
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
  remoteSetup();
}

void loop() {  
>>>>>>> Stashed changes

switch (mode)
{
  case AUTOMATED:
    activate_automated_mode();
  case LINE_TRACKING:
    lineTracking();
  case REMOTE:
    remote();
}
<<<<<<< Updated upstream
=======
>>>>>>> e894b15f5837957dc11c5f7fb9940c41308f94c3
>>>>>>> Stashed changes
}