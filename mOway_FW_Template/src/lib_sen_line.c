//******************************************************************************
//*    lib_sen_line.c                                                          *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    Moway robot line sensors with the C18 compiler.                         *
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

#include "lib_sen_line.h"
#include "adc.h"
#include "delays.h"

//*****************************************************



//*****************************************************
//*              SEN_LINE_CONFIG  			          *
//*****************************************************
//*		Description:Configuration of the line  		  *
//* 	     	    sensor.                           *
//*****************************************************

void SEN_LINE_CONFIG(void)
{
    //TRIS configuration
	//*******************TRISA***********************//   
    LINE_RX_R_TRIS=1; 
  	LINE_RX_L_TRIS=1; 
    
    //*******************TRISD***********************//   
	LINE_TX_TRIS=0; 
}   

//*****************************************************



//*****************************************************
//*               SEN_LINE_ANALOG()                   *		
//*****************************************************
//*Descripción: Returns the clarity value of floor.   *
//*You can distinguish colors depending on material.  *
//*                                                   *
//*****************************************************
//*Variables de entrada:                -LINE_R  	  *
//*                                     -LINE_L       *
//*Variables de salida:                 -SEN_LINE_R   *
//*                                     -SEN_LINE_L   *
//*****************************************************

unsigned char SEN_LINE_ANALOG (unsigned char LINE_TO_CHECK)
{	
	//Declaration of the variables to be used
	unsigned char SENSOR=0;

	//It selects the line to be checked   
	switch (LINE_TO_CHECK)
    {
		case LINE_R:         
		   
            //The ADC channel 2 is selected
		   OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH2 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_3ANA);
		break;
           
		case LINE_L:
		   
            //The ADC channel 4 is selected           
		   OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH4 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_5ANA);
	    break;
	}
	
	//An infrared light pulse is sent for the line detection    
    LINE_TX=1;
    Delay10TCYx (90);	                                                        //Delay of 900 us

    //It is necessary to wait until the conversion is completely done    
    ConvertADC();                                                               //Start the conversion
    while( BusyADC() );                                                         //Until it is completed it does not continue with the program

    //Reading of the value    
    SENSOR = ADRESH; 
    	
    //The end of the infrared light pulse    
    LINE_TX=0;
	
    //A/D conversion is disabled    
    CloseADC();
   
    //It returns the value of the sensor   
    return (SENSOR);
}

//*****************************************************



//*****************************************************
//*               SEN_LINE_DIG()                      *		
//*****************************************************
//*Description: It returns if it has detected a black * 
//*line in a white floor.                             *
//*****************************************************
//*Input variables:                 -LINE_R			  *
//*                                 -LINE_L           *                 
//*Output variables:                -SEN_LINE_R       *
//*                                 -SEN_LINE_L       *
//*****************************************************

unsigned char SEN_LINE_DIG(unsigned char LINE_TO_CHECK)
{
	//Declaration of the variables to be used   
	unsigned char SENSOR=0;
	
	WDTCONbits.ADSHR=1;
	ANCON0=0b11111111;		                                                    //All ports are configured as digital
	ANCON1=0b11111111;		                                                    //All ports are configured as digital
	WDTCONbits.ADSHR=0;

	//An infrared light pulse is sent for the line detection    
	LINE_TX=1;
    Delay10TCYx (90);		                                                    //Delay of 900 us
 	
    //It selects the line to be checked    
	switch (LINE_TO_CHECK)
    {
	    case LINE_R:   
            
            //Reading of the value of the right line           
            SENSOR=LINE_RX_R;
 	    break;

	    case LINE_L:
            
            //Reading of the value of the left line           
            SENSOR=LINE_RX_L;
 	    break;
	}

	//The end of the infrared light pulse   
  	LINE_TX=0;
      
	//It returns the value of the sensor	
	return (SENSOR);
}

