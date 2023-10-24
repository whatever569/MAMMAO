#include "headers/LCD.h"

void LCD_setup() {
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
  // total_system_time = previous_total_system_time;

  // Convert total_system_time from seconds to seconds, minutes and hours
  TST_elapsed_second = total_system_time % 60;
  TST_elapsed_minutes = (total_system_time % 3600)/60;
  TST_elapsed_hours  = total_system_time / 3600; 
}

void update_time_count() {
  if (elapsed_time - previous_update_time >= TST_UPDATE_INTERVAL) {

    // Counting the elapsed seconds
    if (elapsed_time-previous_elapsed_second >= 1000) {
      TST_elapsed_second++;
      previous_elapsed_second+= 1000;
    }

    // Counting the elapsed minutes
    if (TST_elapsed_second == 60) {
      TST_elapsed_second = 0; 
      TST_elapsed_minutes++; 
    } 

    // Counting the elapsed hours
    if (TST_elapsed_minutes == 60) {
      TST_elapsed_minutes = 0;
      lcd.setCursor (8, 0);
      lcd.print ("0");    // Making the Minutes counter '00' again after resetting
      TST_elapsed_hours++;
    }
  }
}

void update_display() {
  // Displays minute counter
  lcd.setCursor(8, 0);
  if (TST_elapsed_minutes < 10) {
    lcd.print("0"); // when under 10 the minutes will be displayed like xx:03 for example, instead of xx:30
  }
  lcd.print(TST_elapsed_minutes);
  
  // Displays hour counter
  lcd.setCursor(4, 0);
  if (TST_elapsed_hours >= 10 && TST_elapsed_hours < 100) {
    lcd.print (" ");  //when between 10 and 100 it will show 2 digits instead of 3
  }
  if (TST_elapsed_hours < 10) {
    lcd.print(" 0");  //when under 10 it will display a zero before the number; for example 02:xx instead of 20:xx
  }
  lcd.print(TST_elapsed_hours);
}

unsigned long current_time () { //called when you save the total system time
  return total_system_time = (TST_elapsed_hours * 3600) + (TST_elapsed_minutes * 60) + TST_elapsed_second;  // Convert seconds, minutes and hours to total_system_time in seconds
}

void LCD_mode() {
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
  if (car_speed == 10) {
    lcd.print("M");   // max speed is shown with a M, because there is only 1 space for printing the speed
  } 
  else {
  lcd.print(car_speed);
  }
}

void LCD_direction() {
  lcd.setCursor (15, 1);
  // get_direction();

  switch (car_direction) {        
    case 0: lcd.print("^"); break;
    case 1: lcd.print("v"); break;
    case 2: lcd.print(">"); break;
    case 3: lcd.print("<"); break;
  }
}

void LCD_TST () {
  update_time_count();
  update_display();
  current_time ();
}
 

void LCD_loop() {
  elapsed_time = millis();
  LCD_TST();

  if (elapsed_time - previous_update_time >= TST_LCD_REFRESH) { // refresh the LCD
    LCD_mode();
    LCD_speed();
    LCD_direction();

    previous_update_time = elapsed_time;
  }
}
