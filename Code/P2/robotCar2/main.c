//#include <avr/io.h>
#include "REMOTE.h"

int main()
{
	motor_init();
	irSetup();
	SoftSerialInit();
	ultrasonicSetup();
	sei();
	
	while (1)
	{
		ultrasonicCheck();
	}
}

