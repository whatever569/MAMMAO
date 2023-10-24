int mode_to_be_activated = 1;
void setup() {
  Serial.begin(19200);
  // remote_setup();
  // motor_setup();
  ultrasonic_sensors_setup(trig_ultrasonic_sensor, echo_ultrasonic_sensor, num_ultrasonic_sensors);
}

void loop() {  
activate_automated_mode();
}