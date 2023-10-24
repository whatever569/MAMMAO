#include "headers/AUTOMATED.h"

void backward_and_turn_180_non_blocking() {
    unsigned long currentMillis = millis();
    switch(current_state)
    {
        case BACKWARD:
            backward();
            if(currentMillis - previousMillisTurn >= sensor_check_interval)
            {
                stop();
                previousMillisTurn = currentMillis;
                current_state = LEFT;
                is_moving_backwards_and_turning_180 = true;

            }
            break;
        case LEFT:
            left();
            if(currentMillis - previousMillisTurn >= sensor_check_interval)
            {
                stop();
                previousMillisTurn = currentMillis;
                current_state = BACKWARD;
                is_moving_backwards_and_turning_180 = false;
            }
            break;
    }
}
void activate_automated_mode() {
    unsigned long currentMillis = millis();

    // Non-blocking check of ultrasonic sensors
    if (currentMillis - previousMillis >= sensor_check_interval) {
        previousMillis = currentMillis;
        check_ultrasonic_sensors();
        decide_movement();
    }
}

void check_ultrasonic_sensors() {
    ultrasonic_sensors_check(results, trig_ultrasonic_sensor, echo_ultrasonic_sensor, num_ultrasonic_sensors, 2);
    
    // Logging
    Serial.print(results[0]); Serial.print(" "); Serial.print(results[1]); Serial.print(" "); Serial.println(results[2]);
    
    // Threshold checks
    are_sensors_too_close[0] = results[0] <= SIDE_THRESHOLD_DISTANCE;
    are_sensors_too_close[1] = results[1] <= FRONT_THRESHOLD_DISTANCE;
    are_sensors_too_close[2] = results[2] <= SIDE_THRESHOLD_DISTANCE;
}

void decide_movement() {
//continue the manuever
if (is_moving_backwards_and_turning_180)
{
    backward_and_turn_180_non_blocking();
}
if (are_sensors_too_close[0] && !are_sensors_too_close[1] && !are_sensors_too_close[2]) {
   // Turn Soft left
   forward_left();
   Serial.println("1");
}
else if(!are_sensors_too_close[0] && !are_sensors_too_close[1] && are_sensors_too_close[2])
{
    // Turn Soft Right
   forward_right();
   Serial.println("2");
}
else if (are_sensors_too_close[0] && are_sensors_too_close[1] && !are_sensors_too_close[2]) {
    // Turn left
   left();
   Serial.println("3");
}
else if(!are_sensors_too_close[0] && are_sensors_too_close[1] && are_sensors_too_close[2])
{
    right();
    Serial.println("4");
}
else if ((!are_sensors_too_close[0] && are_sensors_too_close[1] && !are_sensors_too_close[2]) || 
         (are_sensors_too_close[0] && are_sensors_too_close[1] && are_sensors_too_close[2])) {
backward_and_turn_180_non_blocking();
Serial.println("5");
}
else if (are_sensors_too_close[0] && !are_sensors_too_close[1] && are_sensors_too_close[2]) {
backward_and_turn_180_non_blocking();
Serial.println("6");
}
else {
    // Default behavior
    forward();
    
    Serial.println("7");
}
}