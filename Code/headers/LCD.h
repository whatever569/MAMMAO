#ifndef LCD_h
#define LCD_h
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27 ,16, 2); // Setting the I2C adress as 0x27, LCD colums as 16, LCD lines as 2

unsigned long totalSystemTime = 0;
const long TST_LCD_REFRESH = 1000;
const long TST_UPDATE_INTERVAL = 1000;

unsigned long elapsedTime = 0;
unsigned long previousUpdateTime = 0;
unsigned long previousElapsedSecond = 0;

unsigned long TSTElapsedSecond = 0;
unsigned long TSTElapsedMinutes = 0;
unsigned long TSTElapsedHours = 0;

int carDirection = 0; 
int drivingMode = 0;      
int carSpeed = 0;  

void LCDSetup();
void updateTimeCount();
void updateDisplay();
unsigned long currentTime(); 
void LCDLoop();
void LCDMode();
void LCDSpeed();
void LCDDirection();
void LCDTST();

#endif