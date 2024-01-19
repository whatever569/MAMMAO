#include "MOTOR.h"
#include <avr/io.h>
//in 3,4 are the right two motors of the car and in 1, 2 are for the left

uint8_t speed = 255; // max speed
//speed for the slower side when doing soft left and right
#define SOFT_SPEED 75
#define OFF 0
Direction direction = STOPPED;
void motor_init()
{
    pwmSetup();
}

/*

*/

void forward()
{
    set_in1(speed);
    set_in2(OFF);
    set_in3(speed);
    set_in4(OFF);
    direction = FORWARD;
}

void backward()
{
    set_in1(OFF);
    set_in2(speed);
    set_in3(OFF);
    set_in4(speed);
    direction = BACKWARD;
}

//turn like a tank
void left()
{
    set_in1(speed);
    set_in2(OFF);
    set_in3(OFF);
    set_in4(speed);
    direction = LEFT;
}

//turn like a tank
void right()
{
    set_in1(OFF);
    set_in2(speed);
    set_in3(speed);
    set_in4(OFF);
    direction = RIGHT;
}

//turn like a normal car
void softLeft()
{
    set_in1(OFF);
    set_in2(SOFT_SPEED);
    set_in3(OFF);
    set_in4(speed);
    direction = SOFTLEFT;
}

//turn like a normal car
void softRight()
{
    set_in1(SOFT_SPEED);
    set_in2(OFF);
    set_in3(speed);
    set_in4(OFF);
    direction = SOFTRIGHT;
}


void stop()
{
    set_in1(OFF);
    set_in2(OFF);
    set_in3(OFF);
    set_in4(OFF);
    direction = STOPPED;
}
void pwmSetup()
{
    //prescaler 64 and noninverting fast pwm and top at 255

    //in 1 is pd5, in2 pd6, in3 pd3, in4 pb4
    DDRD |= (1<<DDD5) | (1<<DDD6) | (1<<DDD3);
    DDRB |= (1<<DDB3);
        //config timer 0
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // config timer 2
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
    TCCR2B |= (1 << CS22);

}

//setters for motors to enhance readability and make it more modular
void set_in1(uint8_t speed_setting) {

    if (speed_setting <= 255)
    {
        OCR0A = speed_setting;
    }
}
void set_in2(uint8_t speed_setting) {
    OCR0B = speed_setting;
}
void set_in3(uint8_t speed_setting) {
    OCR2A = speed_setting;
}
void set_in4(uint8_t speed_setting) {
    OCR2B = speed_setting;
}
