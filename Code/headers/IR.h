#ifndef IR_H
#define IR_H

#define irL 5
#define irR 12
#include "headers/ULTRASONIC.h"
#include "headers/MOTOR.h"
#include "headers/PINS.h"
int results[numUltrasonicSensors];

void irSetup();
void lineTracking();
bool isClose();

#endif