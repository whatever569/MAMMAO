#ifndef MOTOR_H
#define MOTOR_H

#include "PINS.h"
#define MINSPEED 70
#define MAXSPEED 255

//Led blink delay and state
int time;
int blinkState;
bool ledLeft = false;
bool ledRight = false;

int carSpeed = 0;
int motorSpeed = MINSPEED;
int turningSpeed = motorSpeed;

void speed(){
  motorSpeed = map(carSpeed, 0, 9, MINSPEED, MAXSPEED);
	turningSpeed = motorSpeed / 2;
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
}
// Function to move backward
void backward(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed);  
  digitalWrite(motor2IN3, 0); 
  analogWrite(motor2IN4, motorSpeed);
  ledLeft = true;
  ledRight = true;
}
// Function to turn left
void left(){
  analogWrite(motor1IN2, motorSpeed);
  analogWrite(motor1IN1, 0);
  analogWrite(motor2IN4, 0);
  analogWrite(motor2IN3, motorSpeed);
  ledLeft = true;
  ledRight = false;
}
// Function to turn right
void right(){
  analogWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);
  analogWrite(motor2IN4, motorSpeed);
  analogWrite(motor2IN3, 0);
  ledLeft = false;
  ledRight = true;
}
// Function to move backward and turn left
void backwardLeft(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, turningSpeed);  
  digitalWrite(motor2IN3, 0); 
  analogWrite(motor2IN4, turningSpeed);
  ledLeft = true;
  ledRight = false;
}
// Function to move backward and turn right
void backwardRight(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, turningSpeed);  
  digitalWrite(motor2IN3, 0);                                                                                                          
  analogWrite(motor2IN4, turningSpeed);
  ledLeft = false;
  ledRight = true;
}
// Function to move forward and turn left
void forwardLeft(){
  digitalWrite(motor1IN1, 0);
  analogWrite(motor1IN2, motorSpeed); 
  analogWrite(motor2IN3, motorSpeed);
  digitalWrite(motor2IN4, 0);
  ledLeft = true;
  ledRight = false;
}
// Function to move forward and turn right
void forwardRight(){
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, motorSpeed);
  analogWrite(motor2IN4, motorSpeed);
  digitalWrite(motor2IN3, 0);
  ledLeft = false;
  ledRight = true;
}

void stop()
{
  digitalWrite(motor1IN2, 0);
  analogWrite(motor1IN1, 0);  
  digitalWrite(motor2IN4, 0); 
  analogWrite(motor2IN3, 0);
}

void ledBlink(int delay){
  //blink with milles delay
  if (millis() > time + delay){
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
    }
    else {
      digitalWrite(ledL, 0);
      digitalWrite(ledR, 0);
    }
}

#endif