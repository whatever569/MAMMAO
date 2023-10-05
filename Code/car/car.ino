#include "remote.h"   // The motor header file does not need to be included in the main file since they do not interact directly

void setup() {
  BT.begin(9600); // Initialize the bt serial connection

  // Initialize the motor control pins as outputs
  pinMode(motor1IN1, OUTPUT);   // Left wheels forward
  pinMode(motor1IN2, OUTPUT);   // Left wheels backward
  pinMode(motor1EN, OUTPUT);    // Left wheels enable pin

  pinMode(motor2IN3, OUTPUT);   // Right wheels forward
  pinMode(motor2IN4, OUTPUT);   // Right wheels backward
  pinMode(motor2EN, OUTPUT);    // Right wheels enable pin
}

void loop() {  
  remote();
}