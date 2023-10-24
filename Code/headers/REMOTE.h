#ifndef REMOTE_H
#define REMOTE_H
#include <SoftwareSerial.h>
#include "MOTOR.h"

SoftwareSerial BT(7, 8);  // TXD to 7, RXD to 8 in this case
int input;
void remote_setup();
void remote();

#endif