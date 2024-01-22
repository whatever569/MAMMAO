//#include <avr/io.h>
#define F_CPU (16000000UL)
#include "REMOTE.h"

int main()
{
	remoteSetup();
	motor_init();
	ultrasonicSetup();
	sei();
	
	while (1)
	{
		remote();
	}
}

