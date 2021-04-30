/*
 * File:   EX_EEPROM.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */
/*
 * 
    Data sheet of EEPROM that i used --> the link below
    https://www.alldatasheet.com/datasheet-pdf/pdf/174990/ATMEL/AT24C04.html
 *
 */

// This is a guard condition so that contents of this file are not included
// more than once. 

#ifndef EX_EEPROM_H_
#define	EX_EEPROM_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include"I2C.h"

#define Device_Adsress_Write 0xA0
#define Device_Adsress_Read 0xA1

void EEPROM_Write(unsigned char page,unsigned char address, unsigned char Data);
void EEPROM_Read(unsigned char page,unsigned char address, unsigned char * Data );
void EEPROM_Write_Page(unsigned char page,unsigned char address, unsigned short int length,unsigned char * Data);
void EEPROM_Read_Page(unsigned char page,unsigned char address, unsigned short int length,unsigned char * Data);


#endif	/* EX_EEPROM_H_ */

