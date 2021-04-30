/*
 * File:   BUTTONS.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUTTONS_H_
#define	BUTTONS_H_

#include <xc.h> // include processor files - each processor file is guarded. 

#define UP_Button_TRIS TRISB2
#define UP_Button_PORT PORTBbits.RB2
#define DOWN_Button_TRIS TRISB1
#define DOWN_Button_PORT PORTBbits.RB1
#define ON 1
#define OFF 0

void Buttons_INIT(void);

#endif	/* XC_HEADER_TEMPLATE_H */

