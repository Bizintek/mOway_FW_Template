//******************************************************************************
//*    lib_sen_obstac.c                                                        *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    obstacle sensors of the Moway robot  with the C18 compiler.             *
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
#include "lib_sen_obstac.h"
#include "delays.h"

//*****************************************************



//*****************************************************
//*              SEN_OBSTAC_CONFIG       	          *
//*****************************************************
//*		Description:Configuration of the obstacle     *
//* 	     	    sensors.                          *
//*****************************************************

void SEN_OBSTAC_CONFIG(void)
{
    //TRIS configuration
	//******************TRISA************************//
    IR_RX_L_2_TRIS=1;  
	IR_RX_L_1_TRIS=1; 
    
    //******************TRISF************************//   
	IR_RX_R_1_TRIS=1;  
	IR_RX_R_2_TRIS=1;
    
    //******************TRISJ************************// 
	LED_IR_TRIS=0;  
  	IR_TX_TRIS=0;  
}

//*****************************************************



//*****************************************************
//*               SEN_OBS_ANALOG()                    *
//*****************************************************
//*    Descripción: Returns if an was detected        *
//*    obstacle on the left or right of the robot in  *
//*    value proportional to distance.                *
//*****************************************************
//*Input Variables:             -OBS_SIDE_L           *
//*                             -OBS_CENTER_L         *
//*                             -OBS_CENTER_R	      *			
//*                             -OBS_SIDE_R			  *                             
//*Output Variables:            -SEN_OBS_CENTER_R     *
//*                             -SEN_OBS_CENTER_L     *
//*                             -SEN_OBS_SIDE_R       *
//*                             -SEN_OBS_SIDE_L       *
//*Output:                      -1: Data ok		      *
//*                             -0: Data wrong	      *
//*****************************************************

unsigned char SEN_OBS_ANALOG(unsigned char OBS_TO_CHECK)
{
	//Declaration of the variables to be used   
	unsigned char SENSOR=0;
	
	//It checks which of the four sensors is going to be tested    
	switch(OBS_TO_CHECK)
    {		
		case OBS_SIDE_L:
	
		   //Verification of non-existence of external signal            
		   if((IR_RX_L_2)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
		   }		
		   
           //The ADC channel 3 is selected       
		   OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH3 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_4ANA);

		   //An infrared light pulse is sent for the obstacle detection          
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
		
		   //The acquisition time of the A / D converter is expected          
		   ConvertADC();                                                        // The conversion begins
		   while( BusyADC() );                                                  //Until it is completed it does not continue with the program
		
		   //Reading of the left side sensor          
		   SENSOR=ADRESH;
		   	
		   //The end of the infrared light pulsea          
		   IR_TX=0;
		break;
		Delay10TCYx (50);		                                                //Delay of 500 us
		
		//A/D conversion is disabled           
		CloseADC(); 

		//Verification of non-existence of external signal          
		if((IR_RX_L_2)!=0)
        {
            Delay10TCYx (50);		                                            //Delay of 500 us
            SENSOR=0;
            break;
		}
			
		case OBS_CENTER_L:

		   //Verification of non-existence of external signal            
		   if((IR_RX_L_1)!=0)
           {
                Delay10TCYx (50);		                                            //Delay of 500 us	
		   
                //The variable to be returned is set to 0.          
                SENSOR=0;
                break;
		   }
		
		   //The ADC channel 1 is selected          
		   OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH1 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_2ANA);

		   //An infrared light pulse is sent for the obstacle detection           
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
		
		  //The acquisition time of the A / D converter is expected          
		   ConvertADC();                                                        // The conversion begins
		   while( BusyADC() );                                                  //Until it is completed it does not continue with the program
		
		   //Reading of the left central sensor         
		   SENSOR=ADRESH;
		   	
		   //The end of the infrared light pulse          
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Se espera 500 us
		
		   //A/D conversion is disabled           
		   CloseADC();

		   //Verification of non-existence of external signal           
		   if((IR_RX_L_1)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us	
		    
                //The variable to be returned is set to 0.			   
                SENSOR=0;
                break;
		   } 	
	
		break;		

		case OBS_CENTER_R:
		
		   //Verification of non-existence of external signal            
		   if((IR_RX_R_1)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
		   }
		
		   //The ADC channel 11 is selected          
	       OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH11 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_12ANA);

		   //An infrared light pulse is sent for the obstacle detection           
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
		
		   //The acquisition time of the A / D converter is expected           
		   ConvertADC();                                                        // The conversion begins
		   while( BusyADC() );                                                  //Until it is completed it does not continue with the program
		
		   //Reading of the right central sensor          
		   SENSOR=ADRESH;
		   	
		   //The end of the infrared light pulse          
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Delay of 500 us
		
		   //A/D conversion is disabled          
		   CloseADC(); 	

		    //Verification of non-existence of external signal          
		   if((IR_RX_R_1)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
		   }	   
	
		break;
	
		case OBS_SIDE_R:

		   //Verification of non-existence of external signal          
		   if((IR_RX_R_2)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
		   }
		
		   //The ADC channel 10 is selected          
		   OpenADC(ADC_FOSC_4 & ADC_LEFT_JUST & ADC_0_TAD, ADC_CH10 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,ADC_11ANA);

		   //An infrared light pulse is sent for the obstacle detection         
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
		
		   //The acquisition time of the A / D converter is expected      
		   ConvertADC();                                                        // The conversion begins
		   while( BusyADC() );                                                  //Until it is completed it does not continue with the program
		
		   //Reading of the right side sensor          
		   SENSOR=ADRESH;
		   	
		   //The end of the infrared light pulse           
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Delay of 500 us
		
		   //A/D conversion is disabled          
		   CloseADC(); 

		   //Verification of non-existence of external signal           
		   if((IR_RX_R_2)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
		   }

		break;
    default:
	return(0);		
	}
    
    //The value of the sensor is returned    
    return (SENSOR);	
}

//*****************************************************



//*****************************************************
//*                 SEN_OBS_DIG                       *
//*****************************************************
//*   Description: It returns if an obstacle has been *
//*  detected on the right or left side of the Moway. *
//*****************************************************
//*Input variables:         -OBS_SIDE_L               *
//*                         -OBS_CENTRAL_L            *
//*                         -OBS_CENTRAL_R	          *			
//*                         -OBS_SIDE_R         	  *
//*Output variables:                                  *
//*Output:                  -SEN_OBS_CENTER_R         *
//*                         -SEN_OBS_CENTER_L         *
//*                         -SEN_OBS_SIDE_R           *
//*                         -SEN_OBS_SIDE_L           *
//*****************************************************

unsigned char SEN_OBS_DIG (unsigned char OBS_TO_CHECK)
{

	//Declaration of the variables to be used   
	unsigned char SENSOR=0;
   
	WDTCONbits.ADSHR=1;
	ANCON0=0b11111111;
	ANCON1=0b11111111;
	WDTCONbits.ADSHR=0;

    //It checks which of the four sensors is going to be tested 
	switch (OBS_TO_CHECK)
    {
		case OBS_SIDE_L:

		   //Verification of non-existence of external signal           
		   if((IR_RX_L_2)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	   }
	
		   //An infrared light pulse is sent for the obstacle detection          
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
	
		   //Reading of the left side sensor	   
		   SENSOR=IR_RX_L_2;
			
		   //The end of the infrared light pulse          
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Delay of 500 us		
	
		   //Verification of non-existence of external signal           
	       if((IR_RX_L_2)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	   }
		break;
	 
   		case OBS_CENTER_L:
	
		   //Verification of non-existence of external signal            
		   if((IR_RX_L_1)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	   }
	
		   //An infrared light pulse is sent for the obstacle detection        
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
	
		   //Reading of the left central sensor	   
		   SENSOR=IR_RX_L_1;
			
		   //The end of the infrared light pulse         
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Delay of 500 us		
	
		   //Verification of non-existence of external signal          
	       if((IR_RX_L_1)!=0)
            {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	    }
		break;
	   
		case OBS_CENTER_R:
			
		   //Verification of non-existence of external signal            
		   if((IR_RX_R_1)!=0)
           {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	   }
	
		   //An infrared light pulse is sent for the obstacle detection           
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
	
		   //Reading of the right central sensor	   
		   SENSOR=IR_RX_R_1;
			
		   //The end of the infrared light pulse           
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Delay of 500 us		
	
		  //Verification of non-existence of external signal          
	       if((IR_RX_R_1)!=0)
            {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	    }
		break;

		case OBS_SIDE_R:
	
		   //Verification of non-existence of external signal           
		   if((IR_RX_R_2)!=0)
            {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   	    }
	
		   //An infrared light pulse is sent for the obstacle detection          
		   IR_TX=1;
		   Delay10TCYx (12);		                                            //Delay of 120 us
	
		   //Reading of the right side sensor          
	       SENSOR=IR_RX_R_2;
	    	
		   //The end of the infrared light pulsea           
		   IR_TX=0;
		   Delay10TCYx (50);		                                            //Delay of 500 us		
	
		   //Verification of non-existence of external signal           
	       if((IR_RX_R_2)!=0)
            {
                Delay10TCYx (50);		                                        //Delay of 500 us
                SENSOR=0;
                break;
	   		}
		break;
    default:
	return(0);
	}
		
    //The value of the sensor is returned   
    return (SENSOR);	
}

