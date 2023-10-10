// Define the speed of sound in cm/microsecond. This constant is used for
// distance calculations using the time taken for the ultrasonic wave to
// reflect back.
#define SPEED_OF_SOUND_IN_CM_PER_MICROSECOND 0.0343

/**
 * Initializes the ultrasonic sensors by setting up the specified pins as
 * input or output pins. This function needs to be called in the Arduino's
 * setup function.
 *
 * @param trig_ultrasonic_sensors_pins: An array of pins used to trigger
 *        the ultrasonic sensors.
 * @param echo_ultrasonic_sensors_pins: An array of pins used to receive
 *        the echo signal from the ultrasonic sensors.
 * @param num_sensors: The number of ultrasonic sensors being used.
 *
 */
void ultrasonic_sensors_setup(const int trig_ultrasonic_sensors_pins[],
                              const int echo_ultrasonic_sensors_pins[],
                              const int num_sensors)
{
    for(int i = 0; i < num_sensors; i++)
    {
        pinMode(trig_ultrasonic_sensors_pins[i], OUTPUT);
        pinMode(echo_ultrasonic_sensors_pins[i], INPUT);
    }
}

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
 * @param trig_ultrasonic_sensors_pins: An array of pins used to trigger
 *        the ultrasonic sensors.
 * @param echo_ultrasonic_sensors_pins: An array of pins used to receive
 *        the echo signal from the ultrasonic sensors.
 * @param num_sensors: The number of ultrasonic sensors being used.
 * @param num_samples: The number of samples per sensor, to reduce noise.
 * TIP:  To use this, create an array of results with the number of sensors you are using, this function will then edit that array everytime it gets called.
 */
void ultrasonic_sensors_check(float results[],
                              const int trig_ultrasonic_sensors_pins[],
                              const int echo_ultrasonic_sensors_pins[],
                              const int num_sensors, const int num_samples)
{
    for(int i = 0; i < num_sensors; i++)
    {
        float temp_result = 0;
        for(int j = 0; j < num_samples; j++)
        {
            // Reset the sensor by setting the trigger pin to low
            digitalWrite(trig_ultrasonic_sensors_pins[i], LOW);
            delayMicroseconds(2);

            // Send an ultrasonic pulse by setting the trigger pin to high for 10 microseconds
            digitalWrite(trig_ultrasonic_sensors_pins[i], HIGH);
            delayMicroseconds(10);
            digitalWrite(trig_ultrasonic_sensors_pins[i], LOW);
        
            // Measure the time (in microseconds) taken for the echo to return
            float duration = pulseIn(echo_ultrasonic_sensors_pins[i], HIGH);

            // Calculate the distance in centimeters based on the duration of the echo
            // The distance is half of the total travel distance of the sound wave
            // (to the obstacle and back)
            float distance = (duration * SPEED_OF_SOUND_IN_CM_PER_MICROSECOND) / 2;
            temp_result += distance;
            
        }
        // Update the results array with the average of the calculated for sensor i distance
        results[i] = temp_result/num_samples;
    }
}
