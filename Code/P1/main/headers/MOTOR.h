#ifndef MOTOR_H
#define MOTOR_H

#include "DATA.h"
#include "PINS.h"

bool remoteStart = false;

//Led blink delay and state
int time;
int blinkState;
int delayMs = 250;
bool ledLeft = false;
bool ledRight = false;
void speed()
{
  motorSpeed = map(carSpeed, 0, 9, MINSPEED, MAXSPEED);
  turningSpeed = motorSpeed * 1.5;
  softTurnSpeed = motorSpeed / 2;
}
// Function to set up the motor pins
void motorSetup() {
  pinMode(motor1IN1, OUTPUT);   // Left wheels forward
  pinMode(motor1IN2, OUTPUT);   // Left wheels backward
  pinMode(motor2IN3, OUTPUT);   // Right wheels forward
  pinMode(motor2IN4, OUTPUT);   // Right wheels backward           
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}
// Function to move forward
void forward(){
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);  
  digitalWrite(motor2IN4, 0); 
  analogWrite(motor2IN3, motorSpeed);
  ledLeft = false;
  ledRight = false;
  direction = FORWARD;
}
// Function to move backward
void backward(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed);  
  digitalWrite(motor2IN3, 0); 
  analogWrite(motor2IN4, motorSpeed);
  ledLeft = true;
  ledRight = true;
  direction = BACK;
}
// Function to turn left
void left(){
  analogWrite(motor1IN2, turningSpeed);
  analogWrite(motor1IN1, 0);
  analogWrite(motor2IN4, 0);
  analogWrite(motor2IN3, motorSpeed);
  ledLeft = true;
  ledRight = false;
  direction = NOT_RIGHT;
}
// Function to turn right
void right(){
  analogWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);
  analogWrite(motor2IN4, turningSpeed);
  analogWrite(motor2IN3, 0);
  ledLeft = false;
  ledRight = true;
  direction = RIGHT;
}
// Function to move backward and turn left
void backwardLeft(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, softTurnSpeed);  
  digitalWrite(motor2IN3, 0); 
  analogWrite(motor2IN4, motorSpeed);
  ledLeft = true;
  ledRight = false;
  direction = NOT_RIGHT;
}
// Function to move backward and turn right
void backwardRight(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed);  
  digitalWrite(motor2IN3, 0);                                                                                                          
  analogWrite(motor2IN4, softTurnSpeed);
  ledLeft = false;
  ledRight = true;
  direction = RIGHT;
}
// Function to move forward and turn left
void forwardLeft(){
  analogWrite(motor1IN1, softTurnSpeed);
  analogWrite(motor1IN2, 0); 
  analogWrite(motor2IN3, motorSpeed);
  digitalWrite(motor2IN4, 0);
  ledLeft = true;
  ledRight = false;
  direction = NOT_RIGHT;
}
// Function to move forward and turn right
void forwardRight(){
  analogWrite(motor1IN1, motorSpeed);
  analogWrite(motor1IN2, 0);
  analogWrite(motor2IN3, softTurnSpeed);
  analogWrite(motor2IN4, 0);
  ledLeft = false;
  ledRight = true;
  direction = RIGHT;
}

void stop()
{
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, 0);  
  digitalWrite(motor2IN4, 0); 
  analogWrite(motor2IN3, 0);
  ledLeft = false;
  ledRight = false;
  direction = STOP;
}

void ledBlink(){
  //blink with milles delay
  if (millis() > time + delayMs){
    time = millis();
    // switch on off state
    if (blinkState == 0){           
      blinkState = 1;
    }else {
      blinkState = 0;
    }
  }
  // what lights need to blink
  if (ledLeft == true and ledRight == true){
      digitalWrite(ledL, blinkState);
      digitalWrite(ledR, blinkState);
    }else if (ledLeft == true and ledRight == false){
      digitalWrite(ledL, blinkState);
      digitalWrite(ledR, 0);
    }else if (ledLeft == false and ledRight == true){
      digitalWrite(ledL, 0);
      digitalWrite(ledR, blinkState);
    }else {
      digitalWrite(ledL, 0);
      digitalWrite(ledR, 0);
    }
}

#endif