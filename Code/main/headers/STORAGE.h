//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11
#ifndef STORGAGE_H
#define STORGAGE_H

#include <EEPROM.h>

// Define the EEPROM address where the total system time is stored
const int totalSystemTimeAddress = 0;
unsigned long getPreviousTotalSystemTime();
void addTimeToEepromTotalSystemTime(unsigned long time);

void writeNewTotalSystemTime(unsigned long time)
{
  EEPROM.put(totalSystemTimeAddress, time);
}

// Function to retrieve the previous total system time from EEPROM
unsigned long getPreviousTotalSystemTime()
{
  unsigned long previousTotalSystemTime;
  
  // Read the previous total system time from EEPROM
  EEPROM.get(totalSystemTimeAddress, previousTotalSystemTime);
  
  return previousTotalSystemTime;
}

// Function to erase all data stored in EEPROM (set to 0)
void eraseEEPROM()
{
  // Loop through each EEPROM address and write 0 to erase the data
  for(int i = 0; i < 1024; i++) EEPROM.write(i, 0);
}

#endif
