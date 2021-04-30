/*
 * File:   I2C.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

#ifndef I2C_H_
#define	I2C_H_

#include <xc.h> // include processor files - each processor file is guarded. 
#define _XTAL_FREQ 4000000

#define SCK_TRIS TRISC3
#define SCK_pin RC3
#define SDA_TRIS TRISC4
#define SDA_pin RC4


void Wait_IdleState(void); //to wait till the bus get been in idle state
void Master_INIT(unsigned long I2C_BaudRate);
void I2C_Start(void);   
void I2C_Repeated_Start(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Write_Address(unsigned char Address);
void I2C_Write_Data(unsigned char Data);
unsigned char I2C_Read_Data(void);


#endif	/* I2C_H_ */

