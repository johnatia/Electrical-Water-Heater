/*
 * File:   SSD.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */
#include <xc.h>
#include"SSD.h"

unsigned char SetNum[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//corresponding numbers to display on 7SEGS
unsigned char Num_Digit[2]; // array to be passed from function to another
unsigned char Select_Seg=0; // initialize at the first by zero this variable used to select the digit in 7SEGs

void SSD_INIT(void) 
{
    SSD_TRIS=0x00; // set the connected PORT to 7seg as OUPUT
    // activate Displays PORTs as OUTPUTs
    Display1_TRIS=0;
    Display2_TRIS=0;  
}
void Disable_Display(void)
{
    //Disable_Displays
    Display2_PIN = OFF; 
    Display1_PIN = OFF;
    
}
void Seperate_Num(unsigned char Num) //Seperating the numbers for 2 digits to display on 7SEGs
{
    Num_Digit[0]=Num%10; // 1st digit in 7 segment
    Num_Digit[1]=Num/10; // 2nd digit in 7 segment
    
//    return Num_Digit; // pointer to the first element in array
}
void Select_Digit(unsigned char Digit)    
{   
        SSD_PORT = SetNum[Num_Digit[Digit-1]];
        switch(Digit)
        {
            case Digit_1:
                 Display1_PIN = OFF; // de-activate Display1
                 Display2_PIN= ON; // activate Display2  
              break;  
            case Digit_2:
                Display2_PIN = OFF; // de-activate Display2   
                Display1_PIN = ON; // activate Display1
              break;
        }    

}

void Display_Num(unsigned char Temp)    
{  
    Select_Seg++;
       
        if(Select_Seg==1)
        {
            Seperate_Num(Temp);
            Select_Digit(Digit_1);
            //Select_Digit1();
        }  // if Select_Seg=1 >>> selecting 1st digit in 7SEGs
        else
        {
            Select_Digit(Digit_2);
            //Select_Digit2();  
            Select_Seg=0;
        } // if Select_Seg=1 >>> selecting 2nd digit in 7SEG
}

