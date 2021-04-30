/*
 * File:   Timer.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TIMER_H_
#define	TIMER_H_

#include <xc.h> // include processor files - each processor file is guarded.  

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

void Timer_INIT(void);



#endif	/* TIMER_H_ */

