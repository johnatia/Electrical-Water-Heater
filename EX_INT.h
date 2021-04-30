/*
 * File:   EX_INT.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef EX_INT_H_
#define	EX_INT_H_

#include <xc.h> // include processor files - each processor file is guarded.  


void EX_Interrupt_INIT( void (*PtrToFunc)(void)   );
void __interrupt() ISR(void);

#endif	/* EX_INT_H_ */

