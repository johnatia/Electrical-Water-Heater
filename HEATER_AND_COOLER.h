/*
 * File:   HEATER_AND_COOLER.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef HEATER_AND_COOLER_H_
#define	HEATER_AND_COOLER_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include"BUTTONS.h"

#define Heating_TRIS TRISC5
#define Heating_PIN RC5
#define Cooling_TRIS TRISC2
#define Cooling_PIN RC2
#define Heating_LED_TRIS TRISB7
#define Heating_LED RB7

void Heating_and_Cooling_INIT(void);//Initializing PINs Heating and Cooling Elements
void Disable_Heating_and_Cooling(void);
void Heating_and_Cooling(float * current_Temp , unsigned char * Temperature);//to check which of them Heater or Cooler we have to turn on 


#endif	/* HEATER_AND_COOLER_H_ */

