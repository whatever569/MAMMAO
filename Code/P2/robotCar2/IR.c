#include <avr/io.h>
#define irR DDB4
#define irL DDB5
#include "MOTOR.h"
#include "IR.h"

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