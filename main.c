/*
 * File:   main.c
 * Author: JOHN_ATIA
 *
 * Created on 14/7/2020
 */
/*
 * 
    Data sheet of PIC16f877A that i used --> the link below
    https://www.microchip.com/wwwproducts/en/PIC16F877A
 *
 */
/*
 * 
    Attached PNG file for State Machine Diagram
    https://drive.google.com/file/d/1c2Zppu7rf6zoQW_K7E7I4hmhEECYc9oC/view?usp=sharing

 *
 */
/*
 * 
    Testing Video on Drive  --> the link below
    https://drive.google.com/file/d/1WYxe5F5uFLNkFtCmZjRUc0qwqAzCdEgk/view?usp=drivesdk
 *
 */
/*********************************Compiler that i used is XC8******************************************/
/*********************************IDE that i used is MPLAB*********************************************/
#include <xc.h>
#include"config.h"
#include"EX_INT.h"
#include"Timer.h"
#include"SSD.h"
#include"EX_EEPROM.h"
#include"TEMP_SENSOR.h"
#include"BUTTONS.h"
#include"HEATER_AND_COOLER.h"
#include <stdbool.h> 

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

 unsigned char Temperature=60; // to store temperature value which get edited
 float current_Temp=27.5;// the current Temperature is the average of last 10 sensor readings 
 unsigned char INT1=0; //Initializing interrupt 1 
 unsigned char INT2=0; //Initializing interrupt 2
 unsigned int Sec1=0; // when reaches 100 perform 1sec time interval
 unsigned int Sec5=0; // when reaches 500 perform 5sec time interval
 unsigned char Setting_Mode=0; // Setting Mode to edit display
bool Sleep_Mode=true;//determine the State of the Heater while Power is connected

void decrease_Temp(void);  //function to decrease the temperature and change mode for setting mode
void increase_Temp(void); //function to increase the temperature and change mode for setting mode 
void ISR_CallBack(void); //The Implementation of Time Trigger using Interrupt


void main(void) {
    TRISB &=0b10000111;//disable the unused PINs in PORTB
    
    EX_Interrupt_INIT(ISR_CallBack);//Initializing External Interrupt   
    ADC_INIT();//Initializing Analog TO Digital Converter
    Master_INIT(100000);//Initializing I2C in Master mode with 100KHZ BaudRate
    Timer_INIT();//Initializing Timer1
    
    SSD_INIT();//Initializing 7 Segment Display
    Buttons_INIT();//Initializing UP&DOWN Buttons
    Heating_and_Cooling_INIT();//Initializing Heat&Cooling Elements  
    EEPROM_Read( 2 , 0xF0 , &Temperature );//Read the stored Temperature from EEPROM and Passing it by Reference
    
        
    while(1) 
    {   
        Heating_and_Cooling( &current_Temp , &Temperature ); //to check which of them Heater or Cooler we have to turn on 
        
        if(UP_Button_PORT==0)// if UP Button is pressed
        {   
            __delay_ms(50); // wait for releasing the button
            if(UP_Button_PORT==0)// if UP Button is pressed
            {
                INT2=1;//activate Software interrupt INT2
            }
            
            
        }
        if(DOWN_Button_PORT==0) // if DOWN Button is pressed
        {  
            __delay_ms(50); // wait for releasing the button 
            
          if(DOWN_Button_PORT==0) // if DOWN Button is pressed
          {
              INT1=1; //activate Software interrupt INT1
          }
          
        }
    }
    
    return;
}


//function to decrease the temperature and change mode for setting mode 
void decrease_Temp(void)
{
    if(Setting_Mode==ON)
        {
        if(Temperature<=35)  {Temperature=35;} // minimum Temperature could be to set
        else Temperature-=5; //Set Temperature
        EEPROM_Write( 2 , 0xF0 , Temperature ); //store the updated temperature in EEPROM
        INT1=Sec1=Sec5=0;
        }
        else //if(Setting_Mode==0) 
        {
            Setting_Mode=ON;
            INT1=Sec1=Sec5=0; 
        }
}

//function to increase the temperature and change mode for setting mode 
void increase_Temp(void)
{
    if(Setting_Mode==ON)
        {
        if(Temperature>=75)  {Temperature=75;} // maximum Temperature could be to set 
        else Temperature+=5; //Set Temperature
        EEPROM_Write( 2 , 0xF0 , Temperature ); //store the updated temperature in EEPROM
        INT2=Sec1=Sec5=0;
        }
        else //if(Setting_Mode==0) 
        {
            Setting_Mode=ON;
            INT2=Sec1=Sec5=0;
        }
}



/******************************************************************************************************************/

                                                /*Important Note*/
/*
 * i attached a Picture that figure out the total time which interrupt takes to be done 
 * "interrupt latency" so you get had a look on the picture you know interrupt takes about 1.77ms to finish 
 * that's why we made the timer make a delay equal to 5ms to let the interrupt finish the event 
 * and you will notice there's another signal you will see which  represented as 1s delay
 *it is the delay of blinking the Heating LED while the Heater is in ON State
 */
/*
 * 
   Important Note about interrupt timing
    https://drive.google.com/file/d/1TO-5AC2ocJgN0xMFQA0QW0bTF1JeTZDk/view?usp=sharing

 *
 */

void ISR_CallBack(void)
{
    if(INTF) // if the "ON/OFF" button is released the heater goes to ON state and exit from Sleep Mode
    {
        Sleep_Mode= !Sleep_Mode;//Toggle it 
        INTF=0;//Clear Interrupt Flag
    }
       
    if(Sleep_Mode==true) // if Power Connected , the Heater will be in the OFF State or Sleep Mode
    {
        Disable_Display(); //Disable 7Segments Display
        Disable_Heating_and_Cooling(); //Disable Heater, Cooler and Heating LED
        INT1=INT2=OFF; //Disable Interrupts
    }
    if(Sleep_Mode==false) // if the heater goes to ON state or exit from Sleep Mode
    {
        float Temp_average[10];
        static unsigned char i=0; // for the loop
        static unsigned int Heating_LED_Flag=0; // for the of heating element
        static unsigned char Milli_Sec=0; // when reaches 100 perform 1ms time interval

        //software interrupt 1 to decrease the temperature and set mode in setting mode   
        if(INT1==ON)     {decrease_Temp();}
    
        //software interrupt 2 to increase the temperature and set mode in setting mode
        if(INT2==ON)     {increase_Temp();} 
   
    
        if(TMR1IF==ON)   // Timer1 execute every 5ms
        {  
            //Pre-loading the timer to perform 5ms time interval by the eq. 65536-((0.005*_XTAL_FREQ)/4)
            TMR1 =60536; 
            Heating_LED_Flag++;
            Milli_Sec++;
            Sec1++;
            Sec5++;    
            
            //Calculate the Average of the last 10 Temperature readings
            if(i>9)
            {
                current_Temp=0;//to store the current Temperature
                for(i=0; i<=9; i++)  {current_Temp += Temp_average[i];}
                current_Temp /= 10;
                i=0;
            } 
            if(Milli_Sec==20) //every 100ms get the sensor readings then get the average of 10 readings
            {      
                Temp_average[i++]=Sense_Temp();// get the temperature Sensor Reading 
                Milli_Sec=0; 
            }
                            /************************************************************/
            if(Heating_LED_Flag==200 ) // when achieve 1 seconds delay
            {
                if(Heating_PIN==ON) {Heating_LED=!Heating_LED; } // while Heating Element is on --> blinking Heating LED
                Heating_LED_Flag=OFF; 
            }
    /**********************************************************************************************************/
            if(Sec5==1000) // after 5 seconds exit from setting mode by clearing Setting_Mode variable
            {   Setting_Mode=OFF;   Sec1=Sec5=0;  }

    /**********************************************************************************************************/
    // if we were in Setting Mode
            if(Setting_Mode==ON)//while we are in Setting_Mode
            {
                if(Sec1<200) //blinking 7Segment Display every 1 s
                { Disable_Display();  } // de-activate Displays in the first second
             
                else
                {
                   if(Milli_Sec!=0) //don't display when ADC reads value
                    {  
                        Display_Num(Temperature); // Display the Temperature in the 2nd second
                    }
                    if(Sec1==400)  {Sec1=0;} //1724 then 1500
                    
                }
            }
           // if we were in Normal Mode
            else
            {
                if(Milli_Sec!=0) //don't display when ADC reads value
                {  
                    Display_Num((unsigned char)current_Temp);
                }
                //here we Could Display the actual Temperature that we set by using this Function Display_Num(Temperature);
                //or we could Display the current Temperature and that we did above 
            }

    /**********************************************************************************************************/
   
 
            TMR1IF=0;//cleat Timer1 Flag
        }
    }
}


