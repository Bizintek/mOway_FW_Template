//******************************************************************************
//*    lib_sen_temp.c                                                          *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    temperature sensor of Moway robot with the C18 compiler.                *
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

#include "adc.h"

//*****************************************************



//*****************************************************
//*                  SEN_TEMPERATURE                  *
//*****************************************************
//*Description:It returns the temperature  		      *
//*****************************************************
//*Input variables:                                   *
//*Output variables:            -SEN_TEMPERATURE_P    *
//*****************************************************

unsigned char SEN_TEMPERATURE (void)
{
	//Declaration of the variables to be used    
	int SEN_TEMPERATURE_C=0;

   	//Channel 13 of the ADC is selected and the acquisition time of the A / D converter is expected.   
	OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH13 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_14ANA);
	ConvertADC();                                                               //The conversion begins
    while( BusyADC() );                                                         // Until it is completed it does not continue with the program

	//Reading and calculation of temperature   
    SEN_TEMPERATURE_C = ADRESH; 

	//It checks if the value is ok and it calculates the percentage   
	SEN_TEMPERATURE_C = (SEN_TEMPERATURE_C - 69);
	if(SEN_TEMPERATURE_C>0)
	{
		SEN_TEMPERATURE_C=(SEN_TEMPERATURE_C*10)/23;
	}
	else
	{
		SEN_TEMPERATURE_C = 0;
	}

	//A/D conversion is disabled   
    CloseADC();

	//It returns the battery level    
	return (SEN_TEMPERATURE_C);
}




