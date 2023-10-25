//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

// Define the speed of sound in cm/microsecond. This constant is used for
// distance calculations using the time taken for the ultrasonic wave to
// reflect back.
#define SPEED_OF_SOUND_IN_CM_PER_MICROSECOND 0.0343

/**
 * Calculates the distance of obstacles in front of each ultrasonic sensor
 * and updates the results array with the respective distances in centimeters.
 *
 * This function sends an ultrasonic pulse, waits for the echo and then
 * calculates the distance based on the time taken for the echo to return.
 *
 * @param results: An array that will store the distance calculated for each
 *        sensor. The array should be initialized with the same length as
 *        the number of sensors.
 * @param ultrasonicSensorsPins: An array of pins used to trigger and echo
 *        the ultrasonic sensors.
 * @param numSensors: The number of ultrasonic sensors being used.
 * @param numSamples: The number of samples per sensor, to reduce noise.
 * TIP:  To use this, create an array of results with the number of sensors you are using, this function will then edit that array everytime it gets called.
 */

void ultrasonicSensorsCheck(float results[],
                              const int ultrasonicSensorsPins[],
                              const int numSensors, const int numSamples)
{
    for(int i = 0; i < numSensors; i++)
    {
        float tempResult = 0;
        for(int j = 0; j < numSamples; j++)
        {
            //To use the same pins, change the mode of the pin in the middle of the operation.
            pinMode(ultrasonicSensorsPins[i], OUTPUT);
            // Reset the sensor by setting the trigger pin to low
            digitalWrite(ultrasonicSensorsPins[i], LOW);
            delayMicroseconds(2);

            // Send an ultrasonic pulse by setting the trigger pin to high for 10 microseconds
            digitalWrite(ultrasonicSensorsPins[i], HIGH);
            delayMicroseconds(10);
            digitalWrite(ultrasonicSensorsPins[i], LOW);

            pinMode(ultrasonicSensorsPins[i], INPUT);
            // Measure the time (in microseconds) taken for the echo to return
            float duration = pulseIn(ultrasonicSensorsPins[i], HIGH, 20000);
            // Calculate the distance in centimeters based on the duration of the echo
            // The distance is half of the total travel distance of the sound wave
            // (to the obstacle and back)
            float distance = (duration * SPEED_OF_SOUND_IN_CM_PER_MICROSECOND) / 2;

            tempResult += distance;

        }
        // Update the results array with the average of the calculated for sensor i distance
        results[i] = tempResult/numSamples;
        delay(10);
    }
}

#endif