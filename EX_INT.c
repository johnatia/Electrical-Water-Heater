/*
 * File:   EX_INT.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */


#include <xc.h>
#include"EX_INT.h"

void (*EX_INT_CallBack)(void);

void EX_Interrupt_INIT( void (*PtrToFunc)(void)   )
{
    TRISB0=1;//set RB0 AS INPUT
    INTEDG=1;//Interrupt on rising edge of RB0/INT pin
    INTE=1;//RB0/INT External Interrupt Enable bit
    GIE=1;//Global Interrupt Enable bit  
    EX_INT_CallBack = PtrToFunc;
}

void __interrupt() ISR(void)
{
    EX_INT_CallBack();
}