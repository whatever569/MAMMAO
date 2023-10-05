#include "remote.h"   // The motor header file does not need to be included in the main file since they do not interact directly

void setup() {
  remote_setup();
  motor_setup();
}

void loop() {  
  remote();
}