//******************************************************************************
//*    lib_sen_micro.c                                                         *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    Moway robot microphone with the C18 compiler.                           *
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
#include "lib_sen_micro.h"

//*****************************************************



//*****************************************************
//*              SEN_MICRO_CONFIG  			          *
//*****************************************************
//*		Description:Configuration of the microphone.  *
//* 	     	                                      *
//*****************************************************

void SEN_MICRO_CONFIG(void)
{
    //TRIS configuration
    //******************TRISH************************//   
	MIC_IN_TRIS=1;
}

//*****************************************************



//*****************************************************
//*                  SEN_MIC_ANALOG                   *		
//*****************************************************
//*			Description:It returns the analog         *
//*				value form the microphone      		  *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                   -SEN_MIC       *
//*****************************************************

unsigned char SEN_MIC_ANALOG (void)
{
	//Declaration of the variables to be used   
	unsigned char SEN_MIC=0;

   	//Channel 15 of the ADC is selected and the acquisition time of the A / D converter is expected   
	OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH15 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_15ANA);
	ConvertADC(); 	                                                            //The conversion begins
    while( BusyADC() ); 	                                                    //It is necessary to wait until the conversion is completely done

	//Reading of microphone  
    SEN_MIC = ADRESH; 

	//A/D conversion is disabled  
    CloseADC(); 

	//It returns the microphone value   
	return (SEN_MIC);
}

//*****************************************************



//*****************************************************
//*                  SEN_MIC_DIG                      *	
//*****************************************************	
//*			Description:It returns the digital        *
//*				value of the microphone   		  	  *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                    -SEN_MIC      *
//*****************************************************

unsigned char SEN_MIC_DIG (void)
{
	WDTCONbits.ADSHR=1;
	ANCON0=0b11111111;
	ANCON1=0b11111111;
	WDTCONbits.ADSHR=0;
    
	//It returns the microphone value   
	return (MIC_IN);
}






