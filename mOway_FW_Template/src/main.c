 //*****************************************************************************
//*                          Moway First Project                               *
//******************************************************************************
//*    Moway First Project                                                     *
//*    version: 5.0.1                                                          *
//*    The four obstacle sensors are checked.                                  *
//*    Copyright (C) 2013  Bizintek Innova S.L.                                *
//******************************************************************************
//*    This program is free software; you can redistribute it and/or modify    *
//*    it under the terms of the GNU General Public License as published by    *
//*    the Free Software Foundation; either version 2 of the License, or       *
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
//*    Date: 07/03/2013                                                        *
//******************************************************************************


//*****************************************************
//	INCLUDES                                          *
//*****************************************************
#include "p18f87j50.h"                                                          //Moway microcontroller

#include "lib_mot_moway.h"                                                      //Engines library

#include "lib_config_moway.h"                                                   //Sensor library
#include "lib_sen_accel.h"	
#include "lib_sen_battery.h"
#include "lib_sen_led.h"
#include "lib_sen_line.h"
#include "lib_sen_micro.h"
#include "lib_sen_obstac.h"
#include "lib_sen_speaker.h"
#include "lib_sen_light.h"	
	
//*****************************************************
// BOOTLOADER JUMP                                    *
//*****************************************************
#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018

//*****************************************************
//	CONFIGURATION BITS                                *
//*****************************************************

#pragma config XINST    = OFF                                                   // Extended instruction set
#pragma config STVREN   = ON                                                    // Stack overflow reset
#pragma config PLLDIV   = 3                                                     // (12 MHz crystal used on this board)
#pragma config WDTEN    = ON                                                    // Watch Dog Timer (WDT)
#pragma config CP0      = OFF                                                   // Code protect
#pragma config CPUDIV   = OSC3_PLL3                                             // OSC1 = divide by 1 mode
#pragma config IESO     = OFF                                                   // Internal External (clock) Switchover
#pragma config FCMEN    = OFF                                                   // Fail Safe Clock Monitor
#pragma config FOSC     = HSPLL                                                 // Firmware must also set OSCTUNE<PLLEN> to start PLL!
#pragma config WDTPS    = 256                                                   // Aprox 1 sec
#pragma config MSSPMSK  = MSK5                                                  //
#pragma config CCP2MX   = ALTERNATE                                             //
#pragma config WAIT     = OFF                                                   // 
#pragma config BW       = 16                                                    // Only available on the
#pragma config MODE     = XM12                                                  // 80 pin devices in the 
#pragma config EASHFT   = OFF                                                   // family.
#pragma config PMPMX    = DEFAULT                                               //
#pragma config ECCPMX   = ALTERNATE                                             //

//*****************************************************
	
extern void _startup (void); 

#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS

void _reset (void)
{
    _asm goto _startup _endasm
}

//*********************DECLARATIONS******************//
#pragma code

//***********************[MAIN]**********************//
void main()
{   
	//******************VARIABLES********************//
	unsigned char time=1;                                                       //100 ms
	unsigned char freq=0;
	
	//*************SENSORS CONFIGURATION*************//
	SEN_CONFIG();

    //********OBSTACLE SENSORS ARE CHECKED***********//   
    //*************************************************
    //*	 Description: Program to check the correct    *
    //*	 functioning of obstacle sensors.             *
    //*************************************************
	while(1)
    {
        //Left side obstacle sensor
        //When an obstacle is detected, it will sound a tone (propotional to the distance) during 100 ms        
        if (SEN_OBS_ANALOG(OBS_SIDE_L)>40)
        {		
            //The OBS_SIDE_L variable indicates the sensor we want to check (left side)		
            freq=SEN_OBS_ANALOG(OBS_SIDE_L);
            SEN_SPEAKER(freq,time,SPEAKER_TIME);
        }
        
        //Left central obstacle sensor
        //When an obstacle is detected, the front Led is switched on       
        if (SEN_OBS_DIG(OBS_CENTER_L))
        {		
            //The OBS_CENTER_L variable indicates the sensor we want to check (left central)
            LED_FRONT_ON();
        }	
        else
        {
            LED_FRONT_OFF();	
        }
        
        //Right central obstacle sensor	
        //When an obstacle is detected, the brake Led is switched on       
        if (SEN_OBS_DIG(OBS_CENTER_R))
        {		
            //The OBS_CENTER_R variable indicates the sensor we want to check (right central)
            LED_BRAKE_ON();		
        }
        else
        {
            LED_BRAKE_OFF();	
        }
        
        //Right side obstacle sensor
        //When an obstacle is detected, it will sound a tone (propotional to the distance) during 100 ms        
        if (SEN_OBS_ANALOG(OBS_SIDE_R)>40)
        {		
            //The OBS_SIDE_R variable indicates the sensor we want to check (right side)
            freq=SEN_OBS_ANALOG(OBS_SIDE_R);
            SEN_SPEAKER(freq,time,SPEAKER_TIME);
        }	
	}
}





	