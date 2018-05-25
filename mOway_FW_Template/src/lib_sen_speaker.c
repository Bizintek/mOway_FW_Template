//******************************************************************************
//*    lib_sen_speaker.c                                                       *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    Moway robot speaker with the C18 compiler.                              *
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

#include "lib_sen_speaker.h"
#include "delays.h"

//*****************************************************



//*****************************************************
//*              SEN_SPEAKER_CONFIG       	          *
//*****************************************************
//*		Description:Configuration of the speaker.     *
//* 	     	                                      *
//*****************************************************

void SEN_SPEAKER_CONFIG(void)
{
    //TRIS configuration
    //********************TRISB**********************//	   
    SPEAKER_TRIS=0;  
}

//*****************************************************



//*****************************************************
//*                  SEN_SPEAKER                      *	
//*****************************************************
//* Descripción:It activates the buzzer to the        * 
//*			indicated time and frequency 			  *
//*****************************************************
//*Input Variables:      -SEN_SPEAKER_FREQ  (Tabla)   *          
//*					   	 -SEN_SPEAKER_TIME  (100ms)   *                           
//*					   	 -SEN_SPEAKER_ON_OFF		  *
//*Output Variables:                                  *
//*Output:   			 -1: Data ok				  *
//*						 -0: Data wrong      		  *
//*****************************************************

unsigned char SEN_SPEAKER ( unsigned char SEN_SPEAKER_FREQ, unsigned char SEN_SPEAKER_TIME, unsigned char SEN_SPEAKER_ON_OFF)
{
	//It checks if the received time is ok or not (0-255)   
	if(SEN_SPEAKER_ON_OFF==SPEAKER_TIME && SEN_SPEAKER_TIME==0)
        return(0);
    
	//PR2 controls the frequency   
	PR2=SEN_SPEAKER_FREQ;	
	
	//CCPR2L controls the duty   
	SEN_SPEAKER_FREQ=SEN_SPEAKER_FREQ & 0b11111110;	
	CCPR2L=(SEN_SPEAKER_FREQ>>1); 	
		
	SPEAKER=0;
		
	T2CONbits.TMR2ON=1;
	T2CONbits.T2CKPS0=1;
	T2CONbits.T2CKPS1=1;
	
	if(SEN_SPEAKER_ON_OFF==SPEAKER_ON || SEN_SPEAKER_ON_OFF==SPEAKER_TIME)
		CCP2CON=0x3F;	
		
	while(SEN_SPEAKER_TIME>0 && SEN_SPEAKER_ON_OFF==SPEAKER_TIME) 	
	{
		Delay10KTCYx (10);		                                                //Delay of 100 ms
		SEN_SPEAKER_TIME--;
	}
	if(SEN_SPEAKER_ON_OFF==SPEAKER_TIME || SEN_SPEAKER_ON_OFF==SPEAKER_OFF)
	   	CCP2CON=0;

	return(1);
}






