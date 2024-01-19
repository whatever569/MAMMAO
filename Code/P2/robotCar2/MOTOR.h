#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

void motor_init();
void forward();
void backward();
void left();
void right();
void softLeft();
void softRight();
void stop();
void pwmSetup();
void set_in1(uint8_t speed_setting);
void set_in2(uint8_t speed_setting);
void set_in3(uint8_t speed_setting);
void set_in4(uint8_t speed_setting);
typedef enum direction { FORWARD, LEFT, RIGHT, BACKWARD, SOFTLEFT, SOFTRIGHT, STOPPED } Direction;
//extern uint8_t speed;
//extern Direction direction;
#endif