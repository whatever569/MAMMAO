//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11
#ifndef STORGAGE_H
#define STORGAGE_H

// Define the EEPROM address where the total system time is stored
const int totalSystemTimeAddress = 0;


unsigned long getPreviousTotalSystemTime();
void addTimeToEepromTotalSystemTime(unsigned long time);
void eraseEEPROM();
#endif