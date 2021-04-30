/*
 * File:   TEMP_SENSOR.c
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

#include <xc.h>
#include"TEMP_SENSOR.h"

float Sense_Temp(void)
{
 return ( (ADC_Read()*(5.0/1024.0))/0.01 );
}
