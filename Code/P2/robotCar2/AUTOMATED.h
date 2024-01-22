#ifndef AUTOMATED_H
#define AUTOMATED_H
#include "IR.h"

//void backwardAndTurn180NonBlocking(void);
//void activateAutomatedMode(void);
//void checkUltrasonicSensors (void);
//void decideMovement (void);
//void ultrasonicSetup (void);
//void ultrasonicCheck (void);	// checks all ultrasonic sensors
//void millis_init (void);		// initialises millis

	void backwardAndTurn180NonBlocking() {
		uint32_t currentMillis = ms;
		switch(currentState)
		{
			case backwar:
				backward();
				if(currentMillis - previousMillisTurn >= sensorCheckInterval)
				{
					stop();
					previousMillisTurn = currentMillis;
					currentState = lef;
					isMovingBackwardsAndTurning180 = true;

				}
				break;
			case lef:
				left();
				if(currentMillis - previousMillisTurn >= sensorCheckInterval)
				{
					stop();
					previousMillisTurn = currentMillis;
					currentState = backwar;
					isMovingBackwardsAndTurning180 = false;
				}
				break;
		}
	}
	void activateAutomatedMode() {
		//remoteStart = false;
		uint32_t currentMillis = ms;
		speed = 2;
		// Non-blocking check of ultrasonic sensors
		if (currentMillis - previousMillis >= sensorCheckInterval) {
			previousMillis = currentMillis;
			checkUltrasonicSensors();
			decideMovement();
		}
	}

	void checkUltrasonicSensors() {
		ultrasonicCheck();
		
		// Threshold checks
		areSensorsTooClose[0] = distance[0] <= SIDE_THRESHOLD_DISTANCE;
		areSensorsTooClose[1] = distance[1] <= FRONT_THRESHOLD_DISTANCE;
		areSensorsTooClose[2] = distance[2] <= SIDE_THRESHOLD_DISTANCE;
	}

	void decideMovement() {
	//continue the manuever
	if (isMovingBackwardsAndTurning180)
	{
		backwardAndTurn180NonBlocking();
	}
	if (areSensorsTooClose[0] && !areSensorsTooClose[1] && !areSensorsTooClose[2]) {
	   // Turn Soft left
	   left();
	}
	else if(!areSensorsTooClose[0] && !areSensorsTooClose[1] && areSensorsTooClose[2])
	{
		// Turn Soft Right
	   right();
	}
	else if (areSensorsTooClose[0] && areSensorsTooClose[1] && !areSensorsTooClose[2]) {
		// Turn left
	   left();
	}
	else if(!areSensorsTooClose[0] && areSensorsTooClose[1] && areSensorsTooClose[2])
	{
		right();
	}
	else if ((!areSensorsTooClose[0] && areSensorsTooClose[1] && !areSensorsTooClose[2]) || 
			 (areSensorsTooClose[0] && areSensorsTooClose[1] && areSensorsTooClose[2])) {
		backwardAndTurn180NonBlocking();
	}
	else if (areSensorsTooClose[0] && !areSensorsTooClose[1] && areSensorsTooClose[2]) {
		backwardAndTurn180NonBlocking();
	}
	else {
		// Default behavior
		forward();
	}
}

ISR(PCINT2_vect) {
	if ((PIND && (1<<ultrasonicPins[currentSensor])) == 1) {
		ultrasonicState = echoUp;
	}
	
	else if ((PIND & (1<<ultrasonicPins[currentSensor])) == 0 && (ultrasonicState == echoUp)) {
		ultrasonicState = echoDown;
	}
}

ISR(TIMER1_OVF_vect) {
	currentSensor++;
	if (currentSensor == 3) {
		currentSensor = 0;
	}
	ultrasonicState = trigger;
	ms += 100;
}

void millis_init (void) {
	ms = 0;
	
	// set timer 1 to fast pwm with top of 25000, pre-scaler 64, frequency 10 Hz (to ensure it is within the HC-SRO4's 16.67 HZ cycle time), overflow interrupt on
	// T_event = T_CPU * N * (TOP+1)
	// [s]	   = [s] * N * (TOP+1)
	// 0.1	   = 16*10^-6 * 64 * 25000
	TCCR1A |= (1<<WGM11) ;
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	ICR1 = 24999;
	TIMSK1 |= (1<<TOIE1);
}

void ultrasonicSetup ()
{
	millis_init();
	
	// enable state change interrupt
	PCICR  |= (1<<PCIE2);
	for (int i = 0; i < NUMBER_OF_USS; i++) {
		PCMSK2 |= (1<<ultrasonicPins[i]);
	}
}

void ultrasonicCheck () {
	switch (ultrasonicState) {
		case trigger:
		DDRD  |=   (1<<ultrasonicPins[currentSensor]);		// ultrasonic sensor to trigger
		PORTD &=  ~(1<<ultrasonicPins[currentSensor]);		// make sure the ultrasonic sensor is off
		
		// turn on trigger for 10 microseconds
		PORTD |= (1<<ultrasonicPins[currentSensor]);
		_delay_us(12);
		PORTD &= ~(1<<ultrasonicPins[currentSensor]);
		
		DDRD &=  ~(1<<ultrasonicPins[currentSensor]);		// ultrasonic sensor to echo
		startTimer = TCNT1;									// start the timer
		break;
		
		case echoUp:
		break;
		
		case echoDown:											// at falling edge go here to stop timer and calculate distance
		endTimer = TCNT1;
		duration = (endTimer - startTimer) / 250000;		// to get duration in seconds
		
		if (duration < 0.06 && duration > 0.0006) {
			distance[currentSensor] = ((duration * 343) / 2 * 100) - CORRECTION_USS;	// to get distance in cm
		}
		else if (duration >= 0.06) {
			distance[currentSensor] = MORETHANRANGE;
		}
		else if (duration <= 0.0006) {
			distance[currentSensor] = LESSTHANRANGE;
		}
		ultrasonicState = restUltrasonicTimer;
		break;
		
		default:
		break;
	}
}
#endif