//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11
#ifndef STORGAGE_H
#define STORGAGE_H

// Define the EEPROM address where the total system time is stored
const int TOTAL_SYSTEM_TIME_ADDRESS = 0;


unsigned long get_previous_total_system_time();
void add_time_to_eeprom_total_system_time(unsigned long time);
void erase_eeprom();
#endif