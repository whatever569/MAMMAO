#include "headers/ULTRASONIC.h"

void ultrasonic_sensors_check(float results[],
                              const int ultrasonic_sensors_pins[],
                              const int num_sensors, const int num_samples)
{
    for(int i = 0; i < num_sensors; i++)
    {
        float temp_result = 0;
        for(int j = 0; j < num_samples; j++)
        {
            //To use the same pins, change the mode of the pin in the middle of the operation.
            pinMode(ultrasonic_sensors_pins[i], OUTPUT);
            // Reset the sensor by setting the trigger pin to low
            digitalWrite(ultrasonic_sensors_pins[i], LOW);
            delayMicroseconds(2);

            // Send an ultrasonic pulse by setting the trigger pin to high for 10 microseconds
            digitalWrite(ultrasonic_sensors_pins[i], HIGH);
            delayMicroseconds(10);
            digitalWrite(ultrasonic_sensors_pins[i], LOW);

            pinMode(ultrasonic_sensors_pins[i], INPUT);
            // Measure the time (in microseconds) taken for the echo to return
            float duration = pulseIn(ultrasonic_sensors_pins[i], HIGH, 20000);

            // Calculate the distance in centimeters based on the duration of the echo
            // The distance is half of the total travel distance of the sound wave
            // (to the obstacle and back)
            float distance = (duration * SPEED_OF_SOUND_IN_CM_PER_MICROSECOND) / 2;
            temp_result += distance;

        }
        // Update the results array with the average of the calculated for sensor i distance
        results[i] = temp_result/num_samples;
        delay(10);
    }
}