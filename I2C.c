/*
 * File:   I2C.c
 * Author: john
 *
 * Created on 15 ?????, 2020, 09:52 ?
 */

#include <xc.h>
#include"I2C.h"

void Wait_IdleState(void) //to wait till the bus get been in idle state
{
    while( (SSPCON2&0b00011111) || (SSPSTAT&0b00000100) );
}
void Master_INIT(unsigned long I2C_BaudRate)
{
    SSPM3=1; // master mode is activated
    SSPEN=1; //Enables the serial port and configures the SDA and SCL pins as the serial port pins 
    SSPCON2 = 0x00;  
    SSPSTAT=0x00;
    SSPADD=( (_XTAL_FREQ/4)/I2C_BaudRate )-1; // set BaudRate to 100KHz by setting the SSPADD to 9
    SCK_TRIS=SDA_TRIS=1; // set SCK&SDA pins as inputs
}
void I2C_Start(void)    
{
    Wait_IdleState();
    SEN=1; // Initiate Start condition on SDA and SCL pins. Automatically cleared by hardware 
}
void I2C_Repeated_Start(void)
{
    Wait_IdleState();
    RSEN=1;
}
void I2C_Stop(void)
{
    Wait_IdleState();
    PEN=1;//Initiate Stop condition on SDA and SCL pins. Automatically cleared by hardware.
    Wait_IdleState();
}
void I2C_ACK(void)
{
    Wait_IdleState();
    ACKDT=0;//send  Acknowledge
    Wait_IdleState();
    ACKEN=1;// Initiate  Acknowledge    
}
void I2C_NACK(void)
{
    Wait_IdleState();
    ACKDT=1;//send  Not Acknowledge
    Wait_IdleState();
    ACKEN=1;// Initiate  Acknowledge
}
void I2C_Write_Address(unsigned char Address)
{
    Wait_IdleState();
    SSPBUF=Address;
    Wait_IdleState();  
}
void I2C_Write_Data(unsigned char Data)
{
    Wait_IdleState();
    while(ACKSTAT); //wait till Acknowledge get received from slave 
    SSPBUF = Data;
    while(!SSPIF); // Wait Until Completion
    SSPIF = 0;
    Wait_IdleState();
    //while(BF);// wait until buffer get be full
}
unsigned char I2C_Read_Data(void)
{
    Wait_IdleState();
    while(ACKSTAT); //wait till Acknowledge get received from slave 
    RCEN=1; //Enables Receive mode for I2C
    while(!SSPIF); // Wait Until Completion
    SSPIF = 0;
    Wait_IdleState();
    return SSPBUF; //return the data from the buffer SSPBUF
}