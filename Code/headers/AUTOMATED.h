//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11

#ifndef AUTOMATED_H
#define AUTOMATED_h

#define FRONT_THRESHOLD_DISTANCE 20 
#define SIDE_THRESHOLD_DISTANCE 10 

// Global Variables
float results[3];
bool areSensorsTooClose[3];
unsigned long previousMillis = 0;
long sensorCheckInterval = 500;  // sensor_checksensor_check_interval to check sensors (in milliseconds)
bool isMovingBackwardsAndTurning180 = false;
unsigned long previousMillisTurn = 0;

enum State
{
    BACKWARD,
    LEFT
};

State currentState = BACKWARD;

// Function Prototypes
void checkUltrasonicSensors();
void decideMovement();
#endif