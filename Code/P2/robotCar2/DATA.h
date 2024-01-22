#ifndef DATA_H_
#define DATA_H_
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

typedef enum { FORWARD, LEFT, RIGHT, BACKWARD, SOFTLEFT, SOFTRIGHT, STOPPED } Direction;
	
#define irR DDB4
#define irL DDB5

#define LED_right DDC1
#define LED_left DDC2
#define NUMBER_OF_USS 3
#define CORRECTION_USS 40
#define MORETHANRANGE 100
#define LESSTHANRANGE 10

volatile double distance[NUMBER_OF_USS];
volatile double duration;
double endTimer;
double startTimer;
volatile uint32_t ms;
volatile int currentSensor;

const int ultrasonicPins[NUMBER_OF_USS] = {2, 4, 5};

typedef enum {
	trigger,
	echoUp,
	echoDown,
	restUltrasonicTimer
}ultrasonicSensorState_e;

ultrasonicSensorState_e ultrasonicState = trigger;

extern uint8_t speed;

typedef enum {
	false,
	true
}bool;

bool areSensorsTooClose[3];
unsigned long previousMillis = 0;
long sensorCheckInterval = 250;  // sensor_checksensor_check_interval to check sensors (in milliseconds)
bool isMovingBackwardsAndTurning180 = false;
unsigned long previousMillisTurn = 0;

#define FRONT_THRESHOLD_DISTANCE 25
#define SIDE_THRESHOLD_DISTANCE 25

typedef enum {
	backwar,
	lef
}State;

State currentState = backwar;

Direction direction = STOPPED;
uint8_t speed = 255;  //max speed

#define SOFT_SPEED 75 //speed for the slower side when doing soft left and right
#define DIR_FORWARD 0
#define DIR_BACKWARD 1
#define OFF 0

volatile double distance[NUMBER_OF_USS] = {0, 0, 0};
volatile double duration = 0;
double endTimer = 0;
double startTimer = 0;
volatile uint32_t ms = 0;
volatile int currentSensor = 0;

#endif