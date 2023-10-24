#include "motor.h"

void intializeIRModule(const int IR1, const int IR2) {
  // put your setup code here, to run once:
  pinMode(IR1, INPUT);    // Set sensor1 as INPUT
  pinMode(IR2, INPUT);   // Set sensor4 as INPUT  
}

void Linemode(const int IR1, const int IR2) {
  int val1 = 0; // Initialize val1 for sensor1
  int val4 = 0; // Initialize val4 for sensor4

  val1 = digitalRead(IR1); // Read sensor1
  val4 = digitalRead(IR2); // Read sensor4

  if (val1 == HIGH && val4 == HIGH) {  // Check if either of the sensors detects the line (HIGH)
    forward();
  }
  if (val1 == LOW && val4 == HIGH) {  // Check if sensor1 detects the line
    left(); // Turn left
  }
  if (val1 == HIGH && val4 == LOW) {  // Check if sensor4 detects the line  
    right(); // Turn right
  }
  if(val1 == LOW && val4 == LOW){
    forward();    
  }
}
