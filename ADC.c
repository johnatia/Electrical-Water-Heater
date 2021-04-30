/*
 * File:   ADC.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

#include <xc.h>
#include"ADC.h"

void ADC_INIT(void)
{
    ADCS2=1; // set ADC clock source to 8Tosc which lead to 2us delay
    CHS1=1; // select Channel 2 (AN2) on PIN RA2
    PCFG3=PCFG0=1; // A/D Port Configuration Control bits
    ADFM=1; // A/D Result Format Select bit 1 = Right justified. Six (6) Most Significant bits of ADRESH are read as ?0?. 
    ADON=1; // A/D converter module is powered up  
    __delay_us(25); // wait the ACQUISITION TIME
}

unsigned short int ADC_Read(void)
{
    GO_DONE=1; //  A/D starts conversion
    while(GO_nDONE);// wait the A/D conversion is completed
    return ((ADRESH<<8)+ADRESL); // shift MSBs then add LSBs
}
