#ifndef SOFTSERIAL_H
#define SOFTSERIAL_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// UART Buffer Defines
// Supported sizes: 2,4,8,16,32,64,128 or 256 bytes
#define USART_RX_BUFFER_SIZE (64)
#define USART_TX_BUFFER_SIZE (64)

// Buffer size checks
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)
#if (USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif
#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)
#if (USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif

// Define baud-rate
#define BAUDRATE 9600
#define myUBRR ((F_CPU / 16UL / BAUDRATE) - 1)

// Static variables 
static char USART_RxBuf[USART_RX_BUFFER_SIZE];
static volatile unsigned char USART_RxHead;
static volatile unsigned char USART_RxTail;
static char USART_TxBuf[USART_TX_BUFFER_SIZE];
static volatile unsigned char USART_TxHead;
static volatile unsigned char USART_TxTail;

// Function prototypes
void clearUSART();
void usart0_init(void);
char usart0_receive(void);
void usart0_transmit(char data);
unsigned char usart0_nUnread(void);
void usart0_transmit_str(char *str);

/*
 * Initialize the USART.
 */
void usart0_init(void)
{
    // Configure the baud rate
    UBRR0H = (unsigned char)(myUBRR >> 8);
    UBRR0L = (unsigned char)myUBRR;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Enable USART receiver and transmitter
    UCSR0B = ((1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0));

    // Flush buffers
    unsigned char x = 0;
    USART_RxTail = x;
    USART_RxHead = x;
    USART_TxTail = x;
    USART_TxHead = x;
}

/*
 * Interrupt handler for received data.
 * Data is placed in the receive buffer.
 */
ISR(USART_RX_vect)
{
    char data;
    unsigned char tmphead;

    // Read the received data
    data = UDR0;

    // Calculate buffer index
    tmphead = (USART_RxHead + 1) & USART_RX_BUFFER_MASK;

    // Store new index
    USART_RxHead = tmphead;

    if (tmphead == USART_RxTail)
    {
        // ERROR! Receive buffer overflow
        // Handle the overflow condition (e.g., set an overflow flag or reset the buffer)
    }

    // Store received data in buffer
    USART_RxBuf[tmphead] = data;
}

/*
 * Interrupt handler for transmit data.
 * Data is read from the transmit buffer. If all data was transmitted,
 * transmit interrupts are disabled.
 */
ISR(USART_UDRE_vect)
{
    unsigned char tmptail;

    // Check if all data is transmitted
    if (USART_TxHead != USART_TxTail)
    {
        // Calculate buffer index
        tmptail = (USART_TxTail + 1) & USART_TX_BUFFER_MASK;

        // Store new index
        USART_TxTail = tmptail;

        // Start transmission
        UDR0 = USART_TxBuf[tmptail];
    }
    else
    {
        // Disable UDRE interrupt
        UCSR0B &= ~(1 << UDRIE0);
    }
}

/*
 * This function returns a new byte from the receive buffer.
 * It will wait for data to be available! Use the function
 * usart0_nUnread() to make sure data is available.
 */
char usart0_receive(void)
{
    unsigned char tmptail;
    // Wait for incoming data
    while (USART_RxHead == USART_RxTail)
        ;

    // Calculate buffer index
    tmptail = (USART_RxTail + 1) & USART_RX_BUFFER_MASK;

    // Store new index
    USART_RxTail = tmptail;

    // Return data
    return USART_RxBuf[tmptail];
}

/*
 * This function places a new byte in the transmit buffer
 * and starts a new transmission by enabling transmit interrupt.
 */
void usart0_transmit(char data)
{
    unsigned char tmphead;

    // Calculate buffer index
    tmphead = (USART_TxHead + 1) & USART_TX_BUFFER_MASK;

    // Wait for free space in buffer
    while (tmphead == USART_TxTail)
        ;

    // Store data in buffer
    USART_TxBuf[tmphead] = data;

    // Store new index
    USART_TxHead = tmphead;

    // Enable UDRE interrupt
    UCSR0B |= (1 << UDRIE0);
}

/*
 * This function returns the number of unread bytes in the receive buffer.
 */
unsigned char usart0_nUnread(void)
{
    if (USART_RxHead >= USART_RxTail)
        return USART_RxHead - USART_RxTail;
    else
        return USART_RX_BUFFER_SIZE - USART_RxTail + USART_RxHead;
}

/*
 * Transmits a string of characters to the USART.
 * The string must be terminated with '\0'.
 *
 * - This function uses the function usart0_transmit() to
 * transmit a byte via the USART
 * - Bytes are transmitted until the terminator
 * character '\0' is detected. Then the function returns.
 */
void usart0_transmit_str(char *str)
{
    while (*str)
    {
        usart0_transmit(*str++);
    }
}

void clearUSART() {
	UCSR0B = 0;
	UCSR0A = 0;
	UCSR0C = 0;
	UBRR0H = 0;
	UBRR0L = 0;
}
#endif