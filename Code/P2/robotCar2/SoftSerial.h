/*
 * SoftSerial.h
 *
 * Created: 21-9-2021 20:07:38
 *  Author: Hugo Arends
 */ 
#ifndef SOFTSERIAL_H_
#define SOFTSERIAL_H_

/*
 * SoftSerial.c
 *
 * Half duplex interrupt driven UART implementation.
 * Supports 9600 bps only.
 * RX pin is PD2
 * TX pin is PD3
 *
 * This SoftSerial driver combines the drivers as implemented in application
 * notes AVR304 and AVR306.
 *
 * Resources used by this driver are TC0 and INT0.
 *
 * Created: 21-9-2021 20:07:24
 *  Author: Hugo Arends
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

// SoftSerial Buffer Defines
#define SOFTSERIAL_RX_BUFFER_SIZE 32 // 2,4,8,16,32,64,128 or 256 bytes
#define SOFTSERIAL_TX_BUFFER_SIZE 32 // 2,4,8,16,32,64,128 or 256 bytes

#define SOFTSERIAL_RX_BUFFER_MASK (SOFTSERIAL_RX_BUFFER_SIZE - 1)
#if (SOFTSERIAL_RX_BUFFER_SIZE & SOFTSERIAL_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif

#define SOFTSERIAL_TX_BUFFER_MASK (SOFTSERIAL_TX_BUFFER_SIZE - 1)
#if (SOFTSERIAL_TX_BUFFER_SIZE & SOFTSERIAL_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

// Static Variables
static char SoftSerial_RxBuf[SOFTSERIAL_RX_BUFFER_SIZE];
static volatile char SoftSerial_RxHead;
static volatile char SoftSerial_RxTail;

static char SoftSerial_TxBuf[SOFTSERIAL_TX_BUFFER_SIZE];
static volatile char SoftSerial_TxHead;
static volatile char SoftSerial_TxTail;

#define TX_PIN          PD6
#define RX_PIN          PD2 // Must be INT0
//#define DBG_PIN         PD4

#define SOFTSERIAL_DDR  DDRD
#define SOFTSERIAL_PORT PORTD
#define SOFTSERIAL_PIN  PIND

#define SET_TX_PIN()    (SOFTSERIAL_PORT |= (1 << TX_PIN))
#define CLEAR_TX_PIN()  (SOFTSERIAL_PORT &= ~(1 << TX_PIN))
#define GET_RX_PIN()    (SOFTSERIAL_PIN & (1 << RX_PIN ))

// If debugging is enabled, use a logic analyzer or a scope to visualize the 
// time spent in the ISRs on the DBG_PIN
//#define DBG_ENABLE

typedef enum
{
    IDLE,              // Idle state, waiting to transmit or receive
    TRANSMIT,          // Transmitting a byte; progress is indicated by SoftSerialTXBitCount
    TRANSMIT_STOP_BIT, // Transmitting stop bit.
    RECEIVE,           // Receiving a byte; progress is indicated by SoftSerialRXBitCount

}SoftSerialStates_t;

static volatile SoftSerialStates_t state;           // Holds the state of the SoftSerial
static volatile unsigned char SoftSerialTXBits;     // Data to be transmitted.
static volatile unsigned char SoftSerialTXBitCount; // TX bit counter.
static volatile unsigned char SoftSerialRXBits;     // Storage for received bits.
static volatile unsigned char SoftSerialRXBitCount; // RX bit counter.

ISR(INT0_vect)
{

/*#ifdef DBG_ENABLE
    PORTD |= (1 << DBG_PIN);
#endif*/

    state = RECEIVE;

    // Disable interrupts while receiving bits
    EIMSK &= ~(1 << INT0);

    // Disable timer interrupts to update the registers
    TIMSK0 &= ~(1 << OCIE0A);

    // Reset the prescaler, stopping the timer/counter
    TCCR0B &= ~((1 << CS01) | ( 1 << CS00 ));

    // This ISR takes time to execute. Compensate for this time by starting 
    // from 1, which is equal to approximately 4 us ((1/16MHz) * 64)
    TCNT0 = 1;

    // Count 1.5 period in the future
    OCR0A = 39;

    // Set prescaler and start the timer/counter
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // Clear received bit counter
    SoftSerialRXBitCount = 0;
    SoftSerialRXBits = 0;
    
    // Clear the interrupt flag and enable timer/counter interrupt
    TIFR0 |= (1 << OCF0A);
    TIMSK0 |= (1 << OCIE0A);

#ifdef DBG_ENABLE
    PORTD &= ~(1 << DBG_PIN);
#endif

}

ISR(TIMER0_COMPA_vect)
{

#ifdef DBG_ENABLE
    PORTD |= (1 << DBG_PIN);
#endif

    switch (state) 
    {
    // Transmitting a byte
    case TRANSMIT:
    {
        // All bits not send?
        if(SoftSerialTXBitCount < 8 )
        {
            // Is the LSB logic 1?
            if(SoftSerialTXBits & 0x01) 
            {           
                SET_TX_PIN();
            }
            else 
            {
                CLEAR_TX_PIN();
            }

            // Select the next bit and count the number of transmitted bits
            // LSB first
            SoftSerialTXBits = SoftSerialTXBits >> 1;
            SoftSerialTXBitCount++;
        }
        else 
        {
            // All bits transmitted, send the stop bit
            SET_TX_PIN();

            state = TRANSMIT_STOP_BIT;
        }
    }
    break;

    // Transmitting stop bit
    case TRANSMIT_STOP_BIT:
    {
        // More data in the buffer for transmitting?
        if(SoftSerial_TxHead != SoftSerial_TxTail)
        {
            unsigned char tmptail;

            // Calculate buffer index
            tmptail = ( SoftSerial_TxTail + 1 ) & SOFTSERIAL_TX_BUFFER_MASK;
        
            // Store new index
            SoftSerial_TxTail = tmptail;
        
            // Start transmission
            state = TRANSMIT;
            
            // Clear the TX pin marking the beginning of the start bit
            PORTD &= ~(1 << TX_PIN);

            // Put the byte in the TX buffer
            SoftSerialTXBits = SoftSerial_TxBuf[tmptail];
            SoftSerialTXBitCount = 0;
        }
        else
        {
            // No more data in transmit buffer
            // Disable timer interrupts
            TIMSK0 &= ~(1 << OCIE0A);

            state = IDLE;
            
            // Reset external interrupt flag (if any) and enable external 
            // interrupt
            EIFR |= (1 << INTF0);
            EIMSK |= (1 << INT0);
        }
    }
    break;

    // Receiving a byte
    case RECEIVE:
    {
        // Count 1 period in the future
        OCR0A = 25;
        
        // Not all bits received (LSB first)?
        if(SoftSerialRXBitCount < 8) 
        {
            // Select the next bit position
            SoftSerialRXBitCount++;
            SoftSerialRXBits = SoftSerialRXBits >> 1;

            // Is the RX pin set?
            if(GET_RX_PIN() != 0)
            {
                // Also set the current bit position
                SoftSerialRXBits |= 0x80;
            }
        }
        else 
        {
            // All bits received
            // Disable timer/counter interrupt
            TIMSK0 &= ~(1 << OCIE0A);

            // Reset external interrupt flag (if any) and enable external
            // interrupt
            EIFR |= (1 << INTF0);
            EIMSK |= (1 << INT0);

            unsigned char tmphead;
    
            // Calculate buffer index
            tmphead = (SoftSerial_RxHead + 1) & SOFTSERIAL_RX_BUFFER_MASK;
    
            // Store new index
            SoftSerial_RxHead = tmphead;
    
            if (tmphead == SoftSerial_RxTail)
            {
                // ERROR! Receive buffer overflow
            }
    
            // Store received data in buffer
            SoftSerial_RxBuf[tmphead] = SoftSerialRXBits;

            state = IDLE;
        }
    }
    break;
    default:        
    {
        // Error, unknown state
        // Return to known state
        state = IDLE;
    }
    break;
    }

#ifdef DBG_ENABLE
    PORTD &= ~(1 << DBG_PIN);
#endif

}

void SoftSerialInit(void)
{
    // Flush buffers
    char  x = 0;
    SoftSerial_RxTail = x;
    SoftSerial_RxHead = x;
    SoftSerial_TxTail = x;
    SoftSerial_TxHead = x;

    // RX pin input with pullup enabled
    DDRD &= ~(1 << RX_PIN);
    PORTD |= (1 << RX_PIN);
    
    // TX pin output and set pin high
    DDRD |= (1 << TX_PIN);
    PORTD |= (1 << TX_PIN);

#ifdef DBG_ENABLE
    DDRD |= (1 << DBG_PIN);
#endif

    // Initialize Timer/Counter 0
    // - Disable interrupt
    // - CTC mode with TOP in OCR0A
    // - 64 prescaler
    // 
    // Note. At 16 MHz, the timer now counts at 250 kHz
    TIMSK0 &= ~(1 << OCIE0A);
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // Initialize external interrupt
    // - The falling edge of INT0 generates an interrupt request
    // - Reset interrupt flag
    // - Enable interrupt
    EICRA |= (1 << ISC01);
    EIFR |= (1 << INTF0);
    EIMSK |= (1 << INT0);

    // Set initial state
    state = IDLE;
}

char SoftSerialReceiveByte(void)
{
    unsigned char tmptail;
    
    // Wait for incoming data
    while (SoftSerial_RxHead == SoftSerial_RxTail)
    {;}
    
    // Calculate buffer index
    tmptail = (SoftSerial_RxTail + 1) & SOFTSERIAL_RX_BUFFER_MASK;
    
    // Store new index
    SoftSerial_RxTail = tmptail;
    
    // Return data
    return SoftSerial_RxBuf[tmptail];
}

void SoftSerialTransmitByte(char data)
{
    unsigned char tmphead;
    
    // Calculate buffer index
    tmphead = (SoftSerial_TxHead + 1) & SOFTSERIAL_TX_BUFFER_MASK;
    
    // Wait for free space in buffer
    while (tmphead == SoftSerial_TxTail)
    {;}
    
    // Store data in buffer
    SoftSerial_TxBuf[tmphead] = data;
    
    // Store new index
    SoftSerial_TxHead = tmphead;

    if(state == IDLE)
    {
        unsigned char tmptail;

        // Calculate buffer index
        tmptail = (SoftSerial_TxTail + 1) & SOFTSERIAL_TX_BUFFER_MASK;
        
        // Store new index
        SoftSerial_TxTail = tmptail;

        // Set new state
        state = TRANSMIT;

        // Disable reception
        EIMSK &= ~(1 << INT0);

        // Put the byte in the TX buffer
        SoftSerialTXBits = SoftSerial_TxBuf[tmptail];
        SoftSerialTXBitCount = 0;

        // Reset the prescaler, stopping the timer/counter
        TCCR0B &= ~((1 << CS01) | ( 1 << CS00 ));
        
        // Reset counter 
        TCNT0 = 0;

        // Generate interrupts at (16 MHz / 64) / (25+1) = 9615.4 Hz
        // (every 0.104 ms)
        OCR0A = 25;
        
        // Set prescaler and start the timer/counter
        TCCR0B |= (1 << CS01) | (1 << CS00);

        // Clear the TX pin marking the beginning of the start bit
        PORTD &= ~(1 << TX_PIN);

        // Enable timer/counter interrupt
        TIMSK0 |= (1 << OCIE0A);
    }
}

void SoftSerialReceiveString(char *str)
{
    uint8_t t = 0;
    while ((str[t] = SoftSerialReceiveByte()) != '\n')
    {
        t++;
    }
    
    str[t++] = '\n';
    str[t] = '\0';
}

void SoftSerialTransmitString(char *str)
{
    while(*str)
    {
        SoftSerialTransmitByte(*str++);
    }
}

/*
 * This function returns the number of unread bytes in the receive buffer.
 */
unsigned char SoftSerialUnread(void)
{
    if(SoftSerial_RxHead == SoftSerial_RxTail)
        return 0;
    else if(SoftSerial_RxHead > SoftSerial_RxTail)
        return SoftSerial_RxHead - SoftSerial_RxTail;
    else
        return SOFTSERIAL_RX_BUFFER_SIZE - SoftSerial_RxTail + SoftSerial_RxHead;
}

#endif /* SOFTSERIAL_H_ */