//******************************************************************************
//*    lib_sen_light.c                                                         *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    light sensor of Moway robot with the C18 compiler.                      *
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
#include "lib_sen_light.h"
#include "lib_sen_accel.h"

//*****************************************************



//*****************************************************
//*              SEN_LIGHT_CONFIG       	          *
//*****************************************************
//*		Description:Configuration of the light        *
//* 	     	    sensor.                           *
//*****************************************************

void SEN_LIGHT_CONFIG(void)
{	
    //TRIS configuration
	//********************TRISA**********************//    
     LIGHT_SEN_TRIS=1; 
}

//*****************************************************



//*****************************************************
//*                  SEN_LIGHT                        *
//*****************************************************
//*		Description:It returns the light percentage   *
//* 		from the light sensor (0-100)             *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                -SEN_LIGHT_P      *
//*****************************************************

unsigned char SEN_LIGHT(void)
{	
   //Declaration of the variables to be used   
   unsigned char SEN_LIGHT_P=0;
   unsigned int aux_value_light;
   unsigned char max_value_light = 45;
   unsigned char type_acce_ligth;
   
   type_acce_ligth=SEN_ACCE_GET_TYPE();
   
   //The ADC channel 0 is selected     
   OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH0 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_1ANA);
   
   //It is necessary to wait until the conversion is completely done  
   ConvertADC();
   while( BusyADC() );                                                          // Until it is completed it does not continue with the program
   
   //Reading and calculation of the percentage of the incident light 
   if((type_acce_ligth    ==  ACCELEROMETER_I2C))
   {
       aux_value_light = ADRESH;
       
       if(aux_value_light>max_value_light)
       {
           aux_value_light  =   max_value_light;
       }
       
       //Normalize      
       aux_value_light  =   100*aux_value_light;
	   aux_value_light  = 	aux_value_light/max_value_light;
		
       SEN_LIGHT_P  =   (unsigned char)aux_value_light;     
   }
   else
   {
		SEN_LIGHT_P = ADRESH/2; 
   }

   //A/D conversion is disabled  
   CloseADC(); 
   Nop();
   
   //It returns percentage of the incident light 
   return (SEN_LIGHT_P);	
}




