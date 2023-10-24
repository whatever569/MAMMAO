#include "headers/MOTOR.h"

void motor_setup() {
  // Initialize the motor control pins as outputs
  pinMode(motor1IN1, OUTPUT);   // Left wheels forward
  pinMode(motor1IN2, OUTPUT);   // Left wheels backward
  pinMode(motor1EN, OUTPUT);    // Left wheels enable pin

  pinMode(motor2IN3, OUTPUT);   // Right wheels forward
  pinMode(motor2IN4, OUTPUT);   // Right wheels backward
  pinMode(motor2EN, OUTPUT);    // Right wheels enable pin
}

void forward() {
  digitalWrite(motor1IN1, HIGH);
  analogWrite(motor1EN, power);
  digitalWrite(motor2IN4, HIGH);
  analogWrite(motor2EN, power);
}

void backward() {
  digitalWrite(motor1IN2, HIGH);
  analogWrite(motor1EN, power);
  digitalWrite(motor2IN3, HIGH);
  analogWrite(motor2EN, power);
}

void left() {
  digitalWrite(motor1IN2, HIGH);
  analogWrite(motor1EN, power);
  digitalWrite(motor2IN4, HIGH);
  analogWrite(motor2EN, power);
}

void forward_left() {
  digitalWrite(motor1IN1, HIGH);
  analogWrite(motor1EN, 64 * (power / max_power));
  digitalWrite(motor2IN4, HIGH);
  analogWrite(motor2EN, power);
}

void right() {
  digitalWrite(motor1IN1, HIGH);
  analogWrite(motor1EN, power);
  digitalWrite(motor2IN3, HIGH);
  analogWrite(motor2EN, power);
}

void forward_right() {
  digitalWrite(motor1IN1, HIGH);
  analogWrite(motor1EN, power);
  digitalWrite(motor2IN4, HIGH);
  analogWrite(motor2EN, 64 * (power / max_power));
}

void stop() {
  digitalWrite(motor1IN1, LOW);
  digitalWrite(motor1IN2, LOW);
  digitalWrite(motor2IN3, LOW);
  digitalWrite(motor2IN4, LOW);
  analogWrite(motor1EN, 0);  // Stop the motor
  analogWrite(motor2EN, 0);
}
