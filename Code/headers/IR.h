#ifndef IR_H
#define IR_H

#define irL 5
#define irR 12
#include "headers/ULTRASONIC.h"
#include "headers/MOTOR.h"
#include "headers/PINS.h"
int results[num_ultrasonic_sensors];

void ir_setup();
void line_tracking();
bool isClose();

#endif