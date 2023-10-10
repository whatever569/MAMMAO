#include "remote.h"   // The motor header file does not need to be included in the main file since they do not interact directly
#include "PINS.hpp"
#include "S7_Ultrasonic_Sensor.hpp"
#include "motor.h"
#include "AUTOMATED_MODE.hpp"

//mode 0 automode, 1 remote, 2 line tracking, 3 default stop
int mode_to_be_activated = 1;
void setup() {
  remote_setup();
  motor_setup();
  ultrasonic_sensors_setup(trig_ultrasonic_sensor, echo_ultrasonic_sensor, num_ultrasonic_sensors);
}

void loop() {  
  Switch (mode_to_be_activated):
    case 0: activate_automated_mode();
    case 1: remote();
    case 2: ...
    case 3: stop();
}