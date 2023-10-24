//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11

#ifndef AUTOMATED_H
#define AUTOMATED_h

#define FRONT_THRESHOLD_DISTANCE 20 
#define SIDE_THRESHOLD_DISTANCE 10 

// Global Variables
float results[3];
bool are_sensors_too_close[3];
unsigned long previousMillis = 0;
long sensor_check_interval = 500;  // sensor_checksensor_check_interval to check sensors (in milliseconds)
bool is_moving_backwards_and_turning_180 = false;
unsigned long previousMillisTurn = 0;

enum State
{
    BACKWARD,
    LEFT
};

State current_state = BACKWARD;

// Function Prototypes
void check_ultrasonic_sensors();
void decide_movement();
#endif