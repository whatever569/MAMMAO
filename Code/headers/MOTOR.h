#ifndef MOTOR_H
#define MOTOR_H

int motorSpeed = 0;
int turningSpeed = 0;

void motorSetup();
int speed(int x);
void forward();
void backward();
void left();
void forwardLeft();
void right();
void forwardRight();
void stop();

#endif