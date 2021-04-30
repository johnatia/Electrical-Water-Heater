/*
 * File:   EX_EEPROM.c
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


#include <xc.h>
#include"EX_EEPROM.h"

void EEPROM_Write(unsigned char page,unsigned char address, unsigned char Data)
{
        I2C_Start();
        I2C_Write_Address(Device_Adsress_Write+page);//send device address + page + Write
        I2C_Write_Data(address);//send address of the data in eeprom
        I2C_Write_Data(Data);// the stored data in eeprom
        I2C_Stop();
}

void EEPROM_Read(unsigned char page,unsigned char address,unsigned char * Data )
{
        I2C_Start();
        I2C_Write_Address(Device_Adsress_Write+page);//send device address + page + Write
        I2C_Write_Data(address);//send address of the data in eeprom
        I2C_Start();//Restart
        I2C_Write_Data(Device_Adsress_Read+page);//send device address + page + Read
        *Data=I2C_Read_Data();//Store the read data in pointer
        I2C_NACK();//send not acknowledge to prevent slave from sending more data
        I2C_Stop();
}

void EEPROM_Write_Page(unsigned char page,unsigned char address, unsigned short int length,unsigned char * Data)
{
        I2C_Start();
        I2C_Write_Address(Device_Adsress_Write+page);//send device address + page + Write
        I2C_Write_Data(address);//send the LSB address of the data suppose to be stored in eeprom 
        for(unsigned int i=0; i<length; i++)   
       {
        I2C_Write_Data(*(Data+i));// the stored data in eeprom
       }
        I2C_Stop();
}

 void EEPROM_Read_Page(unsigned char page,unsigned char address, unsigned short int length,unsigned char * Data)
 {     
        I2C_Start();
        I2C_Write_Address(Device_Adsress_Write+page);//send device address + page + Write
        I2C_Write_Data(address);//send address of the data in eeprom
        I2C_Repeated_Start();//Restart
        I2C_Write_Data(Device_Adsress_Read+page); //send device address + page  + Read
        for(unsigned int i=0; i<length; i++)
        {
        *(Data+i)=I2C_Read_Data();//Store the read data in pointer to array
        I2C_ACK();//send acknowledge to slave after every receieved data 
        }
        I2C_NACK();//send not acknowledge to prevent slave from sending more data
        I2C_Stop();
}
