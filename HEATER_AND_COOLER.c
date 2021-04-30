/*
 * File:   HEATER_AND_COOLER.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */


#include <xc.h>
#include"HEATER_AND_COOLER.h"


void Heating_and_Cooling_INIT(void) //Initializing PINs Heating and Cooling Elements
 {
    Heating_LED_TRIS=0;// set Heating LED as OUTPUT
    Heating_LED=0;//Initializing Heating LED
    Heating_TRIS=Cooling_TRIS=0; // activate Heating&Cooling PINs as OUTPUTs  
 }
void Disable_Heating_and_Cooling(void)
{
    Heating_PIN=OFF; //Disable Heating element
    Cooling_PIN=OFF; //Disable Cooling element
    Heating_LED=OFF; //Turning Heating LED OFF
}

void Heating_and_Cooling(float * current_Temp , unsigned char * Temperature)//to check which of them Heater or Cooler we have to turn on
{
    if(*current_Temp > *Temperature)
    {
        if( *current_Temp > *(Temperature)+5 )//if current temperature is greater than the set temperature by 5 degrees
        {
        Heating_PIN=OFF; //Heating element should be turned OFF
        Cooling_PIN=ON; //cooling element should be turned ON
        Heating_LED=ON; // while cooling Element is on , always Turning Heating LED ON 
        }
    }
    
    if(*current_Temp < *Temperature)
    {
        if( *current_Temp < *(Temperature)+5)//if current temperature is less than the set temperature by 5 degrees
       {
        Heating_PIN=ON; //Heating element should be turned ON
        Cooling_PIN=OFF; //Cooling element should be turned OFF
       }
    }
}
