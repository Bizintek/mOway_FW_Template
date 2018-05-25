//******************************************************************************
//*    lib_sen_led.c                                                           *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    Moway robot Leds with the C18 compiler.                                 *
//*    Copyright (C) 2010  Bizintek Innova S.L.                                *
//*                                                                            *
//******************************************************************************
//*    This program is free software; you can redistribute it and/or modify    *
//*    it under the terms of the GNU General Public License as published by    *
//*    the Free Software Foundation; either version 3 of the License, or       *
//*    (at your option) any later version.                                     *
//*                                                                            *
//*    This program is distributed in the hope that it will be useful,         *
//*    but WITHOUT ANY WARRANTY; without even the implied warranty of          *
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
//*    GNU General Public License for more details.                            *
//*                                                                            *
//*    You should have received a copy of the GNU General Public License along *
//*    with this program; if not, write to the Free Software Foundation, Inc., *
//*    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.             *
//******************************************************************************

#include "lib_sen_led.h"
#include "delays.h"

//*****************************************************



//*****************************************************
//*              SEN_LED_CONFIG  			          *
//*****************************************************
//*		Description:Configuration of the  			  *
//* 	LEDs.    	                                  *
//*****************************************************
//TRIS configuration 
void SEN_LED_CONFIG(void)
{
    //********************TRISE**********************//   
	LED_BRAKE_TRIS=0; 

	//********************TRISC**********************//
	LED_FRONT_TRIS=0;   
	
	//*********************TRISB*********************//   
	LED_TOP_RED_TRIS=0;
	LED_TOP_GREEN_TRIS=0; 
    
 	//*********************PORTB*********************// 	
    //Green LED is off   
 	LED_TOP_GREEN=1;	
 	
    //Red LED is off    
 	LED_TOP_RED=1;	
 	
 	//*******************PORTE**********************//	
    //Brake LED is off   
 	LED_BRAKE=0;
 
 	//********************PORTC*********************//	
    //Front LED is off   
 	LED_FRONT=1;     
}

//*****************************************************



//*****************************************************
//*                   LED_xx_xx()                     *				
//*****************************************************
//*Description: Functions for the use of the LEDs     *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                                  *
//*****************************************************

//The switch on of the front LED
void LED_FRONT_ON(void)
{
   LED_FRONT=0;
}

//The switch off of the front LED
void LED_FRONT_OFF(void)
{
   LED_FRONT=1;
}

//The blinking of the front LED
void LED_FRONT_ON_OFF(void)
{
   LED_FRONT=0;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
   LED_FRONT=1;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
}

//The switch on of the brake LED
void LED_BRAKE_ON(void)
{
  LED_BRAKE=1;
}

//The switch off of the brake LED
void LED_BRAKE_OFF(void)
{
   LED_BRAKE=0;
}

//The blinking of the brake LED
void LED_BRAKE_ON_OFF(void)
{
   LED_BRAKE=0;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
   LED_BRAKE=1;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
}

//The switch on of the top red LED
void LED_TOP_RED_ON(void)
{
   LED_TOP_RED=0;
}

//The switch off of the top red LED
void LED_TOP_RED_OFF(void)
{
   LED_TOP_RED=1;
}

//The blinking of the top red LED
void LED_TOP_RED_ON_OFF(void)
{
   LED_TOP_RED=0;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
   LED_TOP_RED=1;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
}

//The switch on of the top green LED
void LED_TOP_GREEN_ON(void)
{
   LED_TOP_GREEN=0;
}

//The switch off of the top green LED
void LED_TOP_GREEN_OFF(void)
{
   LED_TOP_GREEN=1;
}

///The blinking of the top green LED
void LED_TOP_GREEN_ON_OFF(void)
{
   LED_TOP_GREEN=0;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
   LED_TOP_GREEN=1;
   Delay10KTCYx (5);	                                                        //Delay of 50 ms
}

