//in centimeters
#define FRONT_THRESHOLD_DISTANCE 20 
#define SIDE_THRESHOLD_DISTANCE 10 
void activate_function_for_seconds(int seconds, void (*function)());

/**
 * Use this function within the loop()
 * 
 * 
 * Make sure to use ultrasonic_sensors_setup() before using this function to... well, setup the sensors
 *
*/

int delay = 0;
int currenttime = 0;
void activate_automated_mode()
{
    float results[3];
    bool are_sensors_too_close[num_ultrasonic_sensors];
    if(currenttime + delay < milli()) ultrasonic_sensors_check(results, trig_ultrasonic_sensor, echo_ultrasonic_sensor, num_ultrasonic_sensors);

    //Implementing the logic as described in 4.1.2:
    if(results[0] <= SIDE_THRESHOLD_DISTANCE) are_sensors_too_close[0] = true;
    else are_sensors_too_close[0] = false;
    if(results[1] <= FRONT_THRESHOLD_DISTANCE) are_sensors_too_close[1] = true;
    else are_sensors_too_close[1] = false;
    if(results[2] <= SIDE_THRESHOLD_DISTANCE) are_sensors_too_close[2] = true;
    else are_sensors_too_close[2] = false;


if (are_sensors_too_close[0] && !are_sensors_too_close[1] && !are_sensors_too_close[2]) {
   // Turn Soft left, <TODO> tweaking the seconds parameter to do the desired behavior.
   currenttime = millis();
   delay = 3000;
   forward_right();
}
else if(!are_sensors_too_close[0] && !are_sensors_too_close[1] && are_sensors_too_close[2])
{
    // Turn Soft Right, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, forward_left);
}
else if (are_sensors_too_close[0] && are_sensors_too_close[1] && !are_sensors_too_close[2]) {
    // Turn left, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, left);
}
else if(!are_sensors_too_close[0] && are_sensors_too_close[1] && are_sensors_too_close[2])
{
     // Turn Right, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, right);
}
else if ((!are_sensors_too_close[0] && are_sensors_too_close[1] && !are_sensors_too_close[2]) || 
         (are_sensors_too_close[0] && are_sensors_too_close[1] && are_sensors_too_close[2])) {
    // Turn 180 degrees, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, left);
}
else if (are_sensors_too_close[0] && !are_sensors_too_close[1] && are_sensors_too_close[2]) {
   // Go back, <TODO> tweaking the seconds parameter to do the desired behaviors
   
}
else {
    // Default behavior
    forward();
}

}
