//Written by Mohammed Alzuaa
//Student Number: 2135835
//Project Group 11
//24.09.2023

#include <EEPROM.h>
#include "headers/STORAGE.h"

// Function to add a given time value to the total system time stored in EEPROM
void add_time_to_eeprom_total_system_time(unsigned long time)
{
  // Calculate the new total system time by adding the given time to the previous total
  unsigned long new_time = get_previous_total_system_time() + time;

  // Store the updated total system time back in EEPROM
  EEPROM.put(TOTAL_SYSTEM_TIME_ADDRESS, new_time);


}

// Function to retrieve the previous total system time from EEPROM
unsigned long get_previous_total_system_time()
{
  unsigned long previous_total_system_time;
  
  // Read the previous total system time from EEPROM
  EEPROM.get(TOTAL_SYSTEM_TIME_ADDRESS, previous_total_system_time);
  
  return previous_total_system_time;
}

// Function to erase all data stored in EEPROM (set to 0)
void erase_eeprom()
{
  // Loop through each EEPROM address and write 0 to erase the data
  for(int i = 0; i < 1024; i++) EEPROM.write(i, 0);
}

