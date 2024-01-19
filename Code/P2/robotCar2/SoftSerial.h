/*
 * SoftSerial.h
 *
 * Created: 21-9-2021 20:07:38
 *  Author: Hugo Arends
 */ 
#ifndef SOFTSERIAL_H_
#define SOFTSERIAL_H_

/* Prototypes */
void SoftSerialInit(void);
char SoftSerialReceiveByte(void);
void SoftSerialTransmitByte(char data);
void SoftSerialReceiveString(char *str);
void SoftSerialTransmitString(char *str);
unsigned char SoftSerialUnread(void);

#endif /* SOFTSERIAL_H_ */