/*
 * File:   SSD.h
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */

#ifndef SSD_H_
#define	SSD_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include"BUTTONS.h"

#define Display1_TRIS TRISA4
#define Display1_PIN PORTAbits.RA4
#define Display2_TRIS TRISA5
#define Display2_PIN PORTAbits.RA5

#define SSD_PORT PORTD
#define SSD_TRIS TRISD
#define Digit_1  1
#define Digit_2  2

  extern unsigned char SetNum[10];
  extern unsigned char num;
  extern unsigned char Num_Digit[2]; // array to be passed from function to another
  extern unsigned char Select_Seg; // initialize at the first by zero this variable used to select the digit in 7SEGs 

void SSD_INIT(void);
void Disable_Display(void);
void Seperate_Num(unsigned char Num);
void Select_Digit(unsigned char Digit);
void Display_Num(unsigned char Temp);

#endif