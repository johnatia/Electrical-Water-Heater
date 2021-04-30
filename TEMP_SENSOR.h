/*
 * File:   TEMP_SENSOR.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */
/*
 * 
    Data sheet of LM35 Temperature sensor that i used --> the link below
    https://www.alldatasheet.com/view.jsp?Searchword=LM35
 *
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TEMP_SENSOR_H_
#define	TEMP_SENSOR_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include"ADC.h"

float Sense_Temp(void);


#endif	/* TEMP_SENSOR_H_ */

