#ifndef MOTOR_H
#define MOTOR_H

// Motor 1 Pins
const int motor1IN1 = 3; // IN1 pin of L293D for Motor 1
const int motor1IN2 = 5; // IN2 pin of L293D for Motor 1
const int motor1EN = 11;  // Enable pin for Motor 1 (PWM)

// Motor 2 Pins
const int motor2IN3 = 6; // IN3 pin of L293D for Motor 2
const int motor2IN4 = 9; // IN4 pin of L293D for Motor 2
const int motor2EN = 10; // Enable pin for Motor 2 (PWM)

int power = 255;         // 0-255
int maxPower = 255;
int minPower = 102;
int interval = 17;
int powerMode = 10;      // Currently there are 10 power modes

void motorSetup();
void forward();
void backward();
void left();
void forwardLeft();
void right();
void forwardRight();
void stop();

#endif