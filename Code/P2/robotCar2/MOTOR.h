#ifndef MOTOR_H
#define MOTOR_H
/// @brief Look at the product report subsystem report section on driving the car in different directions
// WARNING : I mistakingly said the switching happens between in1/in3 in2/in4, but the switching is happening between in1/in2 and in3/in4

#include "DATA.h"

/*
void motor_init();
void forward();
void backward();
void left();
void right();
void softLeft();
void softRight();
void stop();
*/

void rightSide(uint8_t speed, int direction);
void leftSide(uint8_t speed, int direction);

void motor_init(void)
{
    //prescaler 64 and noninverting fast pwm and max_top at 255

    //in1/in2 is pd3, in3/in4 pb3
    DDRD |= (1 << DDD3);
    DDRB |= (1 << DDB3);
    
    //demuxSelect 1 and 2 in PB1 and PB2
    DDRB |= (1<<DDB1) | (1 << DDB2);
    // config timer 2
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
    TCCR2B |= (1 << CS22);
}

void forward()
{
    leftSide(speed, DIR_FORWARD);
    rightSide(speed, DIR_FORWARD);
    direction = FORWARD;
}

void backward()
{
    leftSide(speed, DIR_BACKWARD);
    rightSide(speed, DIR_BACKWARD);
    direction = BACKWARD;
}

//turn like a tank
void left()
{
    leftSide(speed, DIR_FORWARD);
    rightSide(speed, DIR_BACKWARD); // right goes reverse
    direction = LEFT;
}

//turn like a tank
void right()
{
    rightSide(speed, DIR_FORWARD);
    leftSide(speed, DIR_BACKWARD); // left goes reverse
    direction = RIGHT;
}

//turn like a normal car
void softLeft()
{
    leftSide(speed, DIR_FORWARD);
    rightSide(SOFT_SPEED, DIR_FORWARD);
    direction = SOFTLEFT;
}

//turn like a normal car
void softRight()
{
    rightSide(speed, DIR_FORWARD);
    leftSide(SOFT_SPEED, DIR_FORWARD);
    direction = SOFTRIGHT;
}


void stop()
{
    leftSide(OFF, DIR_FORWARD);
    rightSide(OFF, DIR_FORWARD);
    direction = STOPPED;
}

//setters for motors to enhance readability and make it more modular
//it is assumed that 0 is the natural direction, 1 is reverse for the direction variable
void leftSide(uint8_t speed, int direction) {
    if ((speed <= 255 && speed >= 0) && (direction == 0 || direction == 1))
    {
        OCR2A = speed;

        if(direction)
        {
            PORTB |= (1 << PORTB1);
        }
        else
        {
            PORTB &= ~(1 << PORTB1);
        }
    }
}
void rightSide(uint8_t speed, int direction) {
    if ((speed <= 255 && speed >= 0) && (direction == 0 || direction == 1))
    {
        OCR2B = speed;
        
        if(direction)
        {
            PORTB |= (1 << PORTB2);
        }
        else
        {
            PORTB &= ~(1 << PORTB2);
        }
    }
}
#endif