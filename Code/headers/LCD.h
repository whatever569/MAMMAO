#ifndef LCD_h
#define LCD_h
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27 ,16, 2); // Setting the I2C adress as 0x27, LCD colums as 16, LCD lines as 2

unsigned long total_system_time = 0;
const long TST_LCD_REFRESH = 1000;
const long TST_UPDATE_INTERVAL = 1000;

unsigned long elapsed_time = 0;
unsigned long previous_update_time = 0;
unsigned long previous_elapsed_second = 0;

unsigned long TST_elapsed_second = 0;
unsigned long TST_elapsed_minutes = 0;
unsigned long TST_elapsed_hours = 0;

int car_direction = 0; 
int driving_mode = 0;      
int car_speed = 0;  

void LCD_setup();
void update_time_count();
void update_display();
unsigned long current_time(); 
void LCD_loop();
void LCD_mode();
void LCD_speed();
void LCD_direction();
void LCD_TST();

#endif