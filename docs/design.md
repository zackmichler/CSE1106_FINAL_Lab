# Design Specification: Smart Classroom Comfort Monitor

## 1. System Architecture Overview
This system is written in C and runs on a Raspberry Pi 4b.

## 2. Program Flow 
Will first prompt user to enter temperature in Fahrenheit
Reads in user inputted temperature
Checks whether temperature is in accepted range (68°F-76°F)
If not, display WARNING status. If accepted, display NORMAL status and add to tempcount.
An LED connected to a Raspberry Pi will turn on if there is a WARNING status as well.
Save the temperature reading and their status to a file.
Calculate the average of recorded temperatures.

Allow for acceptable temperatures range to change according to a new client requirement.
