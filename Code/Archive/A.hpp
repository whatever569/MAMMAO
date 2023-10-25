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
void activateAutomatedMode()
{
    float results[3];
    bool areSensorsTooClose[num_ultrasonic_sensors];
    if(currenttime + delay < milli()) ultrasonicSensorsCheck(results, trig_ultrasonic_sensor, echo_ultrasonic_sensor, num_ultrasonic_sensors);

    //Implementing the logic as described in 4.1.2:
    if(results[0] <= SIDE_THRESHOLD_DISTANCE) areSensorsTooClose[0] = true;
    else areSensorsTooClose[0] = false;
    if(results[1] <= FRONT_THRESHOLD_DISTANCE) areSensorsTooClose[1] = true;
    else areSensorsTooClose[1] = false;
    if(results[2] <= SIDE_THRESHOLD_DISTANCE) areSensorsTooClose[2] = true;
    else areSensorsTooClose[2] = false;


if (areSensorsTooClose[0] && !areSensorsTooClose[1] && !areSensorsTooClose[2]) {
   // Turn Soft left, <TODO> tweaking the seconds parameter to do the desired behavior.
   currenttime = millis();
   delay = 3000;
   forward_right();
}
else if(!areSensorsTooClose[0] && !areSensorsTooClose[1] && areSensorsTooClose[2])
{
    // Turn Soft Right, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, forward_left);
}
else if (areSensorsTooClose[0] && areSensorsTooClose[1] && !areSensorsTooClose[2]) {
    // Turn left, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, left);
}
else if(!areSensorsTooClose[0] && areSensorsTooClose[1] && areSensorsTooClose[2])
{
     // Turn Right, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, right);
}
else if ((!areSensorsTooClose[0] && areSensorsTooClose[1] && !areSensorsTooClose[2]) || 
         (areSensorsTooClose[0] && areSensorsTooClose[1] && areSensorsTooClose[2])) {
    // Turn 180 degrees, <TODO> tweaking the seconds parameter to do the desired behavior.
   activate_function_for_seconds(3, left);
}
else if (areSensorsTooClose[0] && !areSensorsTooClose[1] && areSensorsTooClose[2]) {
   // Go back, <TODO> tweaking the seconds parameter to do the desired behaviors
   
}
else {
    // Default behavior
    forward();
}

}
