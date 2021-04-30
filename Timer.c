/*
 * File:   Timer.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

#include <xc.h>
#include"Timer.h"


void Timer_INIT(void)   
{
    TMR1 =( 65536-((0.005*_XTAL_FREQ)/4) ); //Pre-loading the timer to perform 5ms time interval 
    TMR1CS = 0;// Choose the local clock source (timer mode)
    TMR1ON = 1;//Turning TIMER1 ON
    TMR1IE=1;//Enable timer interrupt bit in PIE1 register
    TMR1IF = 0;// Clear The Interrupt Flag Bit
    GIE=1;//Enable Global Interrupt
    PEIE=1;//Enable the Peripheral Interrupt         
}
