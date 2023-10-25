#ifndef MOTOR_H
#define MOTOR_H

#define MINSPEED 0
#define MAXSPEED 255

int speedMode = 0;
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