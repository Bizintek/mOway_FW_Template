//******************************************************************************
//*    lib_sen_battery.c                                                       *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    Moway robot battery with the C18 compiler.                              *
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

#include "lib_sen_battery.h"
#include "adc.h"

//*****************************************************



//*****************************************************
//*              SEN_BATTERY_CONFIG			          *
//*****************************************************
//*		Description:Configuration of the  			  *
//* 	battery.    	                              *
//*****************************************************

void SEN_BATTERY_CONFIG(void)
{
    //TRIS configuration   
    //********************TRISH***********************//
	NTC_TRIS=1;
	BATTERY_TRIS=1;	
}

//******************************************************

 

//******************************************************
//*                  SEN_BATTERY                       *		
//******************************************************
//*Description:It returns the battery level            *
//******************************************************
//*Input variables:                                    *
//*Output variables:            -SEN_BATTERY_P         *
//******************************************************

unsigned char SEN_BATTERY(void)
{  
	//Declaration of the variables to be used    
	unsigned char SEN_BATTERY_P=0;

	//Channel 14 of the ADC is selected and the acquisition time of the A / D converter is expected   
	OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH14 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_15ANA);
	ConvertADC(); 	                                                            //The conversion begins
    while( BusyADC() );                                                         //Until it is completed it does not continue with the program

	//Reading and calculating the battery level     
    SEN_BATTERY_P = ADRESH; 

	if(SEN_BATTERY_P<MAX_BAT_ADC)
	{
		if(SEN_BATTERY_P> MIN_BAT_ADC)
		{
			SEN_BATTERY_P=(SEN_BATTERY_P-MIN_BAT_ADC)*DIV_100_MAX_BAT_ADC_MIN_BAT_ADC;
		}
		else
		{
			SEN_BATTERY_P = 0;
		}
	}
	else
	{
		SEN_BATTERY_P = 100;
	}

	//A / D conversion disabled    
	CloseADC(); 

	//Returns the battery level    
	return (SEN_BATTERY_P);
}


