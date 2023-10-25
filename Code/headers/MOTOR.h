#ifndef MOTOR_H
#define MOTOR_H

#include "PINS.h"
#define MINSPEED 0
#define MAXSPEED 255

int speed = 0;
int motorSpeed = 0;
int turningSpeed = 0;

void speed(){
  motorSpeed = map(speed, 0, 9, MINSPEED, MAXSPEED);
	turningSpeed = motorSpeed / 4;
}
// Function to set up the motor pins
void motorSetup() {
  pinMode(motor1IN1, OUTPUT);   // Left wheels forward
  pinMode(motor1IN2, OUTPUT);   // Left wheels backward
  pinMode(motor2IN3, OUTPUT);   // Right wheels forward
  pinMode(motor2IN4, OUTPUT);   // Right wheels backward           
}
// Function to move forward
void forward(){
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);  
  digitalWrite(motor2IN4, 0); 
  analogWrite(motor2IN3, motorSpeed);
}
// Function to move backward
void backward(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed);  
  digitalWrite(motor2IN3, 0); 
  analogWrite(motor2IN4, motorSpeed);
}
// Function to turn left
void left(){
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, turningSpeed);
  digitalWrite(motor2IN4, 0);
  analogWrite(motor2IN3, motorSpeed);
}
// Function to turn right
void right(){
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);
  digitalWrite(motor2IN4, 0);
  analogWrite(motor2IN3, turningSpeed);  
}
// Function to move backward and turn left
void backwardLeft(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed);  
  digitalWrite(motor2IN3, 0); 
  analogWrite(motor2IN4, turningSpeed);  
}
// Function to move backward and turn right
void backwardRight(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, turningSpeed);  
  digitalWrite(motor2IN3, 0);                                                                                                          
  analogWrite(motor2IN4, motorSpeed); 
}
// Function to move forward and turn left
void forwardLeft(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed); 
  analogWrite(motor2IN3, motorSpeed);
  digitalWrite(motor2IN4, 0);
}
// Function to move forward and turn right
void forwardRight(){
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);
  analogWrite(motor2IN4, motorSpeed);
  digitalWrite(motor2IN3, 0);
}

#endif