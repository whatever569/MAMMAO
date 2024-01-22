#ifndef IR_H
#define IR_H
#include "MOTOR.h"

void irSetup();
void lineTracking();

void irSetup()
{
	DDRB &= ~(1 << irR);
	DDRB &= ~(1 << irL);
}

void lineTracking()
{
	if (PORTB |= (PORTB4))
		right();
	else if (PORTB |= (PORTB5))
		left();
	else
		forward();
}
#endif