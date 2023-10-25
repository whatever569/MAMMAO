#include "headers/LCD.h"
#include "headers/SELECT.h"

void LCDSetup() {
  //get_previous_total_system_time();  
  lcd.init();   // initialize LCD
  lcd.backlight(); // turn on LCD backlight

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
  // totalSystemTime = previous_total_system_time;

  // Convert totalSystemTime from seconds to seconds, minutes and hours
  TSTElapsedSecond = totalSystemTime % 60;
  TSTElapsedMinutes = (totalSystemTime % 3600)/60;
  TSTElapsedHours  = totalSystemTime / 3600; 
}

void updateTimeCount() {
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
    case 0: lcd.print("A.s"); break;
    case 1: lcd.print("S.r"); break;
    case 2: lcd.print("R.a"); break;
  }
}

void LCD_speed() {
  //get_speed();
  lcd.setCursor(15, 0);
  if (carSpeed == 10) {
    lcd.print("M");   // max speed is shown with a M, because there is only 1 space for printing the speed
  } 
  else {
  lcd.print(carSpeed);
  }
}

void LCDDirection() {
  lcd.setCursor (15, 1);
  // get_direction();

  switch (carDirection) {        
    case 0: lcd.print("^"); break;
    case 1: lcd.print("v"); break;
    case 2: lcd.print(">"); break;
    case 3: lcd.print("<"); break;
  }
}

void LCDTST () {
  updateTimeCount();
  updateDisplay();
  currentTime ();
}
 

void LCDLoop() {
  elapsedTime = millis();
  LCDTST();

  if (elapsedTime - previousUpdateTime >= TST_LCD_REFRESH) { // refresh the LCD
    LCDMode();
    LCD_speed();
    LCDDirection();

    previousUpdateTime = elapsedTime;
  }
}