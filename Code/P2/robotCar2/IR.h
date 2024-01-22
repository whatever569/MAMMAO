#ifndef IR_H
#define IR_H
#include "MOTOR.h"

bool close()
{
	checkUltrasonicSensors();
	if (distance[0] < 25 || distance[1] < 25 || distance[2] < 25)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void lineTracking()
{
	int lineTrackingModeSet;
	
	
	/*if (PINB & (1<<PINB4))
	{	
		lineTrackingModeSet = 0;
	} 
	else if (PIND & (1<<PIND6))
	{
		lineTrackingModeSet = 1;
	}
	
	
	if (lineTrackingModeSet == 1)
	{
		softRight();
	} 
	else
	{
		softLeft();
	}*/
	
	if (PINB &(1<<PINB4))
	{
		speed = 255;
		right();
	}
	
	else if (PINB & (1<<PINB0))
	{
		speed = 255;
		left();
	}
	
	else
	{
		speed = 50;
		forward();
	}
		
}
#endif