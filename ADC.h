/*
 * File:   ADC.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */ 

#ifndef ADC_H_
#define	ADC_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 4000000

void ADC_INIT(void);
unsigned short int ADC_Read(void);

#endif	/* ADC_H_ */

