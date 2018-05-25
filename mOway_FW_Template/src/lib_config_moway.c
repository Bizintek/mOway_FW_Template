//******************************************************************************
//*    lib_config_moway.c                                                      *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    sensors of the Moway robot with the C18 compiler.                       *
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

#include "lib_config_moway.h"

//******************************************************
//*                     CODE	                       *
//******************************************************

//Internal function
void 			Delay10TCYx (unsigned char);
void 			Delay10KTCYx (unsigned char);
void 			ACCE_WRITE(unsigned char, unsigned char);
unsigned char 	ACCE_READ(unsigned char);
void            ACCE_CHECK_TYPE(void);

//*****************************************************



//*****************************************************
//*                  SEN_CONFIG()                     *
//*****************************************************
//*Descripción: The function configurates the pic I/Os*
//* 			and the ADC.                          *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                                  * 
//*****************************************************

void SEN_CONFIG(void)
{	
 	//Disable vref circuit    
	CVRCON=0b00000000;
	
    //Disable parallel port   
	PMCONH=0b00000000;

	//Disable the comparator   
	CM1CON=0b00000000;
	CM2CON=0b00000000;

    //ADC configuration    
	WDTCONbits.ADSHR=0;
	ADCON0=0b00000000;
	ADCON1=0b00100011;
	
	WDTCONbits.ADSHR=1;
	ANCON0=0b11111111;		                                                    //All ports are configured as digital
	ANCON1=0b11111111;		                                                    //All ports are configured as digital
	WDTCONbits.ADSHR=0;
		
	//Disable PLL    
	OSCTUNEbits.PLLEN=0;

    //Configuration of TRIS and PORT each in its module.    
	SEN_LINE_CONFIG();
    SEN_LIGHT_CONFIG();
    SEN_OBSTAC_CONFIG(); 
	SEN_LED_CONFIG();
   	SEN_SPEAKER_CONFIG();
    SEN_MICRO_CONFIG();
    SEN_BATTERY_CONFIG();    
    SEN_ACCE_CONFIG();   	
}

 


