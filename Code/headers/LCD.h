#ifndef LCD_h
#define LCD_h
#include <LiquidCrystal_I2C.h>
#include "SELECTION.h"
#include "STORAGE.h"
#include "PINS.h"

LiquidCrystal_I2C lcd(0x27 ,16, 2); // Setting the I2C adress as 0x27, LCD colums as 16, LCD lines as 2

unsigned long totalSystemTime = 0;
const long TST_LCD_REFRESH = 1000;
const long TST_UPDATE_INTERVAL = 1000;
const long TST_SAVING_INTERVAL = 100;
const long TST_DISPLAYSAVE_TIME = 3000;

unsigned long elapsedTime = 0;
unsigned long previousUpdateTime = 0;
unsigned long previousElapsedSecond = 0;
unsigned long LCDSaving = 0;
unsigned long savingDisplayState = 0;
unsigned long savingState = 0;

unsigned long TSTElapsedSecond = 0;
unsigned long TSTElapsedMinutes = 0;
unsigned long TSTElapsedHours = 0;

void LCDSetup() {
  lcd.init();   // initialize LCD
  lcd.backlight(); // turn on LCD backlight
  pinMode(saveButton, INPUT_PULLUP);      

  // Setting up the starting display to be: 
  // 'TST 00:00 SPD  '
  // 'MOD       DIR  '   
  lcd.setCursor (0, 0);
  lcd.print ("TST  00:00");

  lcd.setCursor(11, 0);
  lcd.print("SPD");

  lcd.setCursor(0, 1);
  lcd.print("MOD");

  lcd.setCursor(11, 1);
  lcd.print("DIR");

  // Set the starting time to the previous time from eeprom 
  totalSystemTime = getPreviousTotalSystemTime();

  // Convert totalSystemTime from seconds to seconds, minutes and hours
  TSTElapsedSecond = totalSystemTime % 60;
  TSTElapsedMinutes = (totalSystemTime % 3600)/60;
  TSTElapsedHours  = totalSystemTime / 3600; 
}

void updateTimeCount() {
  elapsedTime = millis();
  if (elapsedTime - previousUpdateTime >= TST_UPDATE_INTERVAL) {

    // Counting the elapsed seconds
    if (elapsedTime-previousElapsedSecond >= 1000) {
      TSTElapsedSecond++;
      previousElapsedSecond+= 1000;
    }

    // Counting the elapsed minutes
    if (TSTElapsedSecond == 60) {
      TSTElapsedSecond = 0; 
      TSTElapsedMinutes++; 
    } 

    // Counting the elapsed hours
    if (TSTElapsedMinutes == 60) {
      TSTElapsedMinutes = 0;
      lcd.setCursor (8, 0);
      lcd.print ("0");    // Making the Minutes counter '00' again after resetting
      TSTElapsedHours++;
    }
  }
}

void updateDisplay() {
  // Displays minute counter
  lcd.setCursor(8, 0);
  if (TSTElapsedMinutes < 10) {
    lcd.print("0"); // when under 10 the minutes will be displayed like xx:03 for example, instead of xx:30
  }
  lcd.print(TSTElapsedMinutes);
  
  // Displays hour counter
  lcd.setCursor(4, 0);
  if (TSTElapsedHours >= 10 && TSTElapsedHours < 100) {
    lcd.print (" ");  //when between 10 and 100 it will show 2 digits instead of 3
  }
  if (TSTElapsedHours < 10) {
    lcd.print(" 0");  //when under 10 it will display a zero before the number; for example 02:xx instead of 20:xx
  }
  lcd.print(TSTElapsedHours);
}

unsigned long currentTime () { //called when you save the total system time
  return totalSystemTime = (TSTElapsedHours * 3600) + (TSTElapsedMinutes * 60) + TSTElapsedSecond;  // Convert seconds, minutes and hours to totalSystemTime in seconds
}

void LCDMode() {
  lcd.setCursor(4, 1);
  
  switch (mode) {
    case AUTOMATED: lcd.print("A.s"); break;
    case LINE_TRACKING: lcd.print("S.r"); break;
    case REMOTE: lcd.print("R.a"); break;
  }
}

void LCD_speed() {
  lcd.setCursor(15, 0);
  lcd.print(speed);
}

void LCDDirection() {
  lcd.setCursor (15, 1);

  switch (direction) {        
    case FORWARD: lcd.print("^"); break;
    case BACKWARD: lcd.print("v"); break;
    case RIGHT: lcd.print(">"); break;
    case LEFT: lcd.print("<"); break;
  }
}

void LCDTST () {
 updateTimeCount ();
 
  if (digitalRead(saveButton) == LOW) { // Read wheter the button is pressed
    savingDisplayState = 1; 
    savingState = 1;
    LCDSaving = elapsedTime;
  }   
  if (savingDisplayState == 1) {    // Start counting when the button is pressed
    if (elapsedTime - LCDSaving >= TST_SAVING_INTERVAL && elapsedTime - LCDSaving <= TST_DISPLAYSAVE_TIME) {    // give the microcontroller time to save and keep the text printed for certain time
      lcd.setCursor(4, 0);
      lcd.print ("Saved ");  
    }
    else if (elapsedTime - LCDSaving > TST_DISPLAYSAVE_TIME) {    //after Saved has been displayed for enough time, revert the TST display back to its normal state.
    savingDisplayState = 0;
    lcd.setCursor(4, 0);
    lcd.print (" 00:00");
    }
  }
  if (savingState == 1) {
      addTimeToEepromTotalSystemTime(currentTime());
      savingState = 0;
  }

  if (savingDisplayState == 0) {
    updateDisplay ();
    currentTime ();
  }
}

void LCDLoop() {
  LCDTST();

  if (elapsedTime - previousUpdateTime >= TST_LCD_REFRESH) { // refresh the LCD
    LCDMode();
    LCD_speed();
    LCDDirection();

    previousUpdateTime = elapsedTime;
  }
}

#endif
