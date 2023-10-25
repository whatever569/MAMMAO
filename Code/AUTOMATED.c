//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11

#include "headers/AUTOMATED.h"
#include "headers/MOTOR.h"
#include "headers/PINS.h"
#include "ULTRASONIC.h"

void backwardAndTurn180NonBlocking() {
    unsigned long currentMillis = millis();
    switch(currentState)
    {
        case BACKWARD:
            backward();
            if(currentMillis - previousMillisTurn >= sensorCheckInterval)
            {
                stop();
                previousMillisTurn = currentMillis;
                currentState = LEFT;
                isMovingBackwardsAndTurning180 = true;

            }
            break;
        case LEFT:
            left();
            if(currentMillis - previousMillisTurn >= sensorCheckInterval)
            {
                stop();
                previousMillisTurn = currentMillis;
                currentState = BACKWARD;
                isMovingBackwardsAndTurning180 = false;
            }
            break;
    }
}
void activateAutomatedMode() {
    unsigned long currentMillis = millis();

    // Non-blocking check of ultrasonic sensors
    if (currentMillis - previousMillis >= sensorCheckInterval) {
        previousMillis = currentMillis;
        checkUltrasonicSensors();
        decideMovement();
    }
}

void checkUltrasonicSensors() {
    ultrasonicSensorsCheck(results, ultrasonicSensorsPins, numUltrasonicSensors, 2);
    
    // Logging
    Serial.print(results[0]); Serial.print(" "); Serial.print(results[1]); Serial.print(" "); Serial.println(results[2]);
    
    // Threshold checks
    areSensorsTooClose[0] = results[0] <= SIDE_THRESHOLD_DISTANCE;
    areSensorsTooClose[1] = results[1] <= FRONT_THRESHOLD_DISTANCE;
    areSensorsTooClose[2] = results[2] <= SIDE_THRESHOLD_DISTANCE;
}

void decideMovement() {
//continue the manuever
if (isMovingBackwardsAndTurning180)
{
    backwardAndTurn180NonBlocking();
}
if (areSensorsTooClose[0] && !areSensorsTooClose[1] && !areSensorsTooClose[2]) {
   // Turn Soft left
   forwardLeft();
   Serial.println("1");
}
else if(!areSensorsTooClose[0] && !areSensorsTooClose[1] && areSensorsTooClose[2])
{
    // Turn Soft Right
   forwardRight();
   Serial.println("2");
}
else if (areSensorsTooClose[0] && areSensorsTooClose[1] && !areSensorsTooClose[2]) {
    // Turn left
   left();
   Serial.println("3");
}
else if(!areSensorsTooClose[0] && areSensorsTooClose[1] && areSensorsTooClose[2])
{
    right();
    Serial.println("4");
}
else if ((!areSensorsTooClose[0] && areSensorsTooClose[1] && !areSensorsTooClose[2]) || 
         (areSensorsTooClose[0] && areSensorsTooClose[1] && areSensorsTooClose[2])) {
backwardAndTurn180NonBlocking();
Serial.println("5");
}
else if (areSensorsTooClose[0] && !areSensorsTooClose[1] && areSensorsTooClose[2]) {
backwardAndTurn180NonBlocking();
Serial.println("6");
}
else {
    // Default behavior
    forward();
    
    Serial.println("7");
}
}