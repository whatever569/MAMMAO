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
int max_power = 255;
int min_power = 102;
int interval = 17;
int power_mode = 10;      // Currently there are 10 power modes

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

#endif