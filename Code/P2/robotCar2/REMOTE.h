#ifndef REMOTE_H
#define REMOTE_H
#include "SoftSerial.h"
#include "AUTOMATED.h"

//int main(void)
//{
//DDRB = (1<<DDB5);
//
//sei();
//SoftSerialInit();
//motorSetup();
//
//while (1)
//{
//if(SoftSerialUnread() > 0)
//{
//char data = SoftSerialReceiveByte();
//
//switch( data )
//{
//
//case 'F':
//forward();
//break;
//
//case 'S':
//stop();
//break;
//}
//
//}
//}
//}

void remoteSetup()
{
	DDRD |= (1<<DDD2);
	DDRB |= (1<<DDB0);
	usart0_init();
}

void remote()
{
	if (usart0_nUnread() > 0)
	{
		char data = usart0_receive();
		switch(data)
		{
			case 'F':
				forward();
				break;
			case 'E':
				softRight();
				break;
			case 'R':
				right();
				break;
			case 'G':
				backward();
				break;
			case 'L':
				left();
				break;
			case 'Q':
				softLeft();
				break;
			case 'S':
				stop();
				break;
		}
	}

}
#endif