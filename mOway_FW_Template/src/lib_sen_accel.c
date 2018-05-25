//******************************************************************************
//*    lib_sen_accel.c                                                         *
//*    version: 5.0.1                                                          *
//*    This library contains the necessary functions to manage the             *
//*    Moway robot accelerometer with the C18 compiler.                        *
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

#include "lib_sen_accel.h"
#include "delays.h"

//*****************Global variables********************
//*****************************************************
//*         Accelerometer SPI: MMA7455                *
//*         Accelerometer I2C: MMA8452                *
//*****************************************************

unsigned char   type_accelerometer  =   ACCELEROMETER_I2C;                      //Type of accelerometer: I2C or SPI

//*****************************************************



//*****************************************************
//*                 SEN_ACCE_XYZ_READ                 *
//*****************************************************
//*	   Description: It returns the accelerometer      *
//*					x,y,z value.                      *
//*****************************************************
//*Input variables:         -ACCE_CHECK_X			  *
//*                         -ACCE_CHECK_Y			  *
//*                         -ACCE_CHECK_Z		      *
//*Output variables:        -SEN_ACCE_X               *
//*                         -SEN_ACCE_Y               *
//*                         -SEN_ACCE_Z               *
//*Output:			   	 					 		  *
//*                         -0:Incorrect reading	  *
//*                         -(1-255):Correct reading  *
//*****************************************************

unsigned char SEN_ACCE_XYZ_READ(unsigned char ACCE_TO_CHECK)
{
	//Variables
	
    unsigned char SENSOR=0;
	unsigned char ACCE_ADRESS=0;
	unsigned char ACCE_DATA_OUT=0;
	unsigned char ACCE_NO_HIGH=255;
	unsigned char ACCE_NO_LOW=255;
	unsigned char ACCE_DATA_IN=0;
    
    switch(type_accelerometer)
    {
        case ACCELEROMETER_SPI:
           
            //The accelerometer is turn on "measure" mode
            ACCE_ADRESS=MCTL;
            ACCE_DATA_OUT=0b00000101;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	

            //It checks if the axes are calculated on time            
            while(ACCE_NO_HIGH>0)
            {
                ACCE_NO_LOW--;
                while(ACCE_NO_LOW>0)
                {
                    if(ACCE_INT1_DRDY==1)
                    {
                        break;
                    }
                    else
                    { 
                        ACCE_NO_LOW--; 
                    }
                }
                if(ACCE_INT1_DRDY==1)
                { 
                    break;
                }
                ACCE_NO_HIGH--;
                if(ACCE_NO_HIGH==0)
                {
                    //The accelerometer goes back to "pulse detection" mode                  
                    ACCE_ADRESS=MCTL;
                    ACCE_DATA_OUT=0b01000011;
                    ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT);
                    return (0);
                }
                else
                {
                    ACCE_NO_LOW=255;
                }
            }
            
            //It selects the axes to be calculated           
            switch (ACCE_TO_CHECK)
            {
                case ACCE_CHECK_X:
                    
                    //X reading                
                    ACCE_ADRESS=XOUT8;
                    ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
                    SENSOR= ACCE_DATA_IN ^ 0b10000000;
                break;

                case ACCE_CHECK_Y:
                    
                    //Y reading               
                    ACCE_ADRESS=YOUT8;
                    ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
                    SENSOR=ACCE_DATA_IN ^ 0b10000000;
                break;

                case ACCE_CHECK_Z:
                    
                    //Z reading               
                    ACCE_ADRESS=ZOUT8;
                    ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
                    SENSOR=ACCE_DATA_IN ^ 0b10000000;
                break;
            }

            //The accelerometer goes back to "pulse detection" mode          
            ACCE_ADRESS=MCTL;
            ACCE_DATA_OUT=0b01000011;
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT);
            break;
        
        case ACCELEROMETER_I2C:
                      
            //Chek if there is a new value            
            while(ACCE_NO_HIGH>0)
            {
                ACCE_NO_LOW--;
                while(ACCE_NO_LOW>0)
                {
                    if(ACCE_INT1_DRDY==1)
                    {
                        break;
                    }
                    else
                    { 
                        ACCE_NO_LOW--; 
                    }
                }
                if(ACCE_INT1_DRDY==1)
                {
                    break;
                }
                ACCE_NO_HIGH--;
                if(ACCE_NO_HIGH==0)
                {
                    return (0);
                }
                else
                {
                    ACCE_NO_LOW=255;
                }
            }
            
            /*************Read accelerometer (measurement)************/            
            switch (ACCE_TO_CHECK)
            {
                case ACCE_CHECK_X:
                    
                    //X reading                    
                    ACCE_ADRESS=X_REGISTER;
                    ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
                    SENSOR=ACCE_DATA_IN ^ 0b10000000;
                break;
                
                case ACCE_CHECK_Y:
                    
                    //Y reading                   
                    ACCE_ADRESS=Y_REGISTER;
                    ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
                    SENSOR=ACCE_DATA_IN ^ 0b10000000;
                break;
                
                case ACCE_CHECK_Z:
                    
                    //Z reading                   
                    ACCE_ADRESS=Z_REGISTER;
                    ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
                    SENSOR=ACCE_DATA_IN ^ 0b10000000;                 
                break;
            }
                         
        break;    
    }			
    return (SENSOR);
	
}

//;*****************************************************



//;*****************************************************
//;*                 SEN_ACCE_CHECK_TAP          	   *	
//;*****************************************************
//;*Description: It verifies if Moway has beaten on not*
//;*****************************************************
//;*Input variables:                                   *
//;*Output variables:            -SEN_ACCE_TAP	       *
//;*****************************************************

unsigned char SEN_ACCE_CHECK_TAP(void)
{
	//Variables
	unsigned char ACCE_ADRESS=0;
	unsigned char SEN_ACCE_TAP=0;
	unsigned char ACCE_DATA_OUT=0;								
	unsigned char ACCE_DATA_IN=0;

    switch(type_accelerometer)
    {
        case ACCELEROMETER_SPI:
           
            //Reading of the interruptions register            
            ACCE_ADRESS=DETSRC;
            ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
            SEN_ACCE_TAP= ACCE_DATA_IN & 0b00000011;

            //It checks if it is a Tap or a Tap tap            
            if(SEN_ACCE_TAP==0b00000011 || SEN_ACCE_TAP==0b00000010)
            {
                SEN_ACCE_TAP=SEN_ACCE_TAP & 0b00000010;
            }

            //Interruptions cleaning            
            ACCE_ADRESS=INTRST;
            ACCE_DATA_OUT=0b00000011;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);		

            //Interruptions cleaning           
            ACCE_ADRESS=INTRST;
            ACCE_DATA_OUT=0b00000000;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);		

            Delay10KTCYx (5);	                                                //Delay of 50 ms
            Delay10KTCYx (5);	                                                //Delay of 50 ms
            Delay10KTCYx (5);	                                                //Delay of 50 ms
            Delay10KTCYx (5);	                                                //Delay of 50 ms
            Delay10KTCYx (5);	                                                //Delay of 50 ms
        break;

        case ACCELEROMETER_I2C:
            
             // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            ACCE_ADRESS=PULSE_SRC_REGISTER;
            ACCE_DATA_IN=ACCE_READ(ACCE_ADRESS);
            SEN_ACCE_TAP= ACCE_DATA_IN & 0b00001000;
            
            //It return the value: 0 if it is a tap_tap and 1 if it is an only tap            
            if(SEN_ACCE_TAP ==  0)
            {
                SEN_ACCE_TAP=1;
            }
            else
            {
                SEN_ACCE_TAP=0;
            }
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             SSP2CON2bits.PEN = 1; //STOP I2C
             while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));         //Wait I2C
        break;
    }
    
	//It return the value: 0 if it is a tap_tap and 1 if it is an only tap    
	return (SEN_ACCE_TAP);		
}

//*****************************************************



//*****************************************************
//*              ACCE_WRITE(data1, data2)			  *
//*****************************************************
//*		Description:Writting condition to  			  *
//* 	make possible the communication with the      * 
//*     accelerometer module.                   	  *
//*****************************************************

void ACCE_WRITE(unsigned char data1, unsigned char data2)
{
	static unsigned char SEN_ACCE_BYTE_OUT_1;						
	static unsigned char SEN_ACCE_BYTE_OUT_2;	
	static unsigned char SEN_ACCE_BYTE_IN_2;	
	static unsigned char SEN_ACCE_BYTE_IN_1;

    switch(type_accelerometer)
    {
        case ACCELEROMETER_SPI:
            ACCE_CSN_TRIS=0;
            ACCE_CSN=0;
            Delay10TCYx (90);					                                //Delay_900us
            SEN_ACCE_BYTE_OUT_1=(data1<<1);
            SEN_ACCE_BYTE_OUT_1=SEN_ACCE_BYTE_OUT_1 | 0b10000000;                                                                                                                                                                                        
            SEN_ACCE_BYTE_OUT_2=data2;

            SSP2BUF=SEN_ACCE_BYTE_OUT_1;		                                //Load send data
            while(SSP2STATbits.BF!=1)	{};		                                //wait

            SEN_ACCE_BYTE_IN_1=SSP2BUF;			                                //Store received data

            SSP2BUF=SEN_ACCE_BYTE_OUT_2;		                                //Load send data
            while(SSP2STATbits.BF!=1)	{};		                                //wait

            SEN_ACCE_BYTE_IN_2=SSP2BUF;
            ACCE_CSN=1;
        break;
        
        case ACCELEROMETER_I2C:
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            
            //ST Device Address[6:0] W
            SSP2BUF =   ADDRESS_NEW_ACCEL_WRITE;   
            
            //Register Address[7:0]
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2BUF = data1;                                                    //Register
           
            //Data[7:0]
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2BUF = data2;                                                    //Data

            SSP2CON2bits.ACKSTAT    =   1;
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C            
        break;
    }	
}

//*****************************************************



//*****************************************************
//*              ACCE_CHECK_TYPE(void)			      *
//*****************************************************
//*		Description:Reading register to               *
//* 	check I2C comunication.                  	  *
//* 	ACK: I2C.                                 	  *
//* 	NACK: SPI.                                 	  *
//*****************************************************

void ACCE_CHECK_TYPE(void)
{
    unsigned char ack_accel;
    
    while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));                  //Wait I2C
    SSP2CON2bits.SEN    = 1;
    while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));                  //Wait I2C
    ack_accel=ACCE_READ(WHO_I_AM_REGISTER);   
    SSP2CON2bits.PEN = 1;                                                       //STOP I2C
    while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));                  //Wait I2C
    
    if(ack_accel == 0x2A)
    {
        type_accelerometer  =   ACCELEROMETER_I2C;
    }
    else
    {
        type_accelerometer  =   ACCELEROMETER_SPI;
    }
}

//*****************************************************



//*****************************************************
//*              ACCE_READ(data)			          *
//*****************************************************
//*		Description:Reading condition to 			  *
//* 	make possible the communication with the      *
//*     accelerometer module.                   	  *
//*****************************************************

unsigned char ACCE_READ(unsigned char data)
{
	static unsigned char SEN_ACCE_BYTE_OUT_1;						
	static unsigned char SEN_ACCE_BYTE_OUT_2;	
	static unsigned char SEN_ACCE_BYTE_IN_2;	
	static unsigned char SEN_ACCE_BYTE_IN_1;
    
    switch(type_accelerometer)
    {
        case ACCELEROMETER_SPI:
            ACCE_CSN_TRIS=0;
            ACCE_CSN=0;
            
            Delay10TCYx (90);                                                   //Delay_900us
            
            SEN_ACCE_BYTE_OUT_1=(data<<1);
            SEN_ACCE_BYTE_OUT_1=SEN_ACCE_BYTE_OUT_1 & 0b01111111;    
            SEN_ACCE_BYTE_OUT_2=0b00000000;
            
            SSP2BUF=SEN_ACCE_BYTE_OUT_1;		                                //Load send data
            while(SSP2STATbits.BF!=1)	{};		                                //wait

            SEN_ACCE_BYTE_IN_1=SSP2BUF;                                         //Store received data

            SSP2BUF=SEN_ACCE_BYTE_OUT_2;                                        //Load send data
            while(SSP2STATbits.BF!=1)	{};                                     //wait

            SEN_ACCE_BYTE_IN_2=SSP2BUF;
            
            ACCE_CSN=1;
        break;
        
        case ACCELEROMETER_I2C:
            
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            //1. ST Device Address[6:0] W            
            SSP2BUF = ADDRESS_NEW_ACCEL_WRITE;
            while(SSP2STATbits.BF!=0){};                                        //Wait 

            //2. Register Address[7:0]            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2BUF = data;
            while(SSP2STATbits.BF!=0){};                                        //Wait         
            
            //3. SR             
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));//Wait I2C
            SSP2CON2bits.RSEN = 1;

            //4. Device Address[6:0] R            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2BUF = ADDRESS_NEW_ACCEL_READ;
            
            //5. Read data            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C              
            SSP2CON2bits.RCEN = 1;
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C     
            
            //Store data
            SEN_ACCE_BYTE_IN_2 =   SSP2BUF;
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            SSP2CON2bits.PEN = 1;                                               //STOP I2C
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
                                                
        break;              
    }	
	return (SEN_ACCE_BYTE_IN_2);
}

//*****************************************************



//*****************************************************
//*              SEN_ACCE_CONFIG			          *
//*****************************************************
//*		Description:Configuration of the  			  *
//* 	accelerometer.    	                          *
//*****************************************************

void SEN_ACCE_CONFIG(void)
{
    //Declaration of the variables to be used	
    unsigned char ACCE_ADRESS=0;
	unsigned char ACCE_DATA_OUT=0;
  
    //First: check if accelerometer is MMA8452 (I2C)
    //I2C configuration:
    //When enabled, SDA and SCL pins must be configured at inputs (SSP2CON1.SSPEN)	    
     ACCEL_SCL_TRIS =1;
     ACCEL_SDA_TRIS =1;
     
 	//I2C module configuration    
 	SSP2STAT=0b00000000;                          //400Khz and I2C
    SSP2CON1=0b00101000;                          //Enable SDA y SCL as serial port pins. I2C MAster mode. Clock: Fosc/(4*(SSPAD+1))
 	SSP2CON2=0b00000000; 
 	
    SSP2ADD =   0; 
     
    //Read register   
     ACCE_CHECK_TYPE();
    
    switch(type_accelerometer)
    {
        case ACCELEROMETER_SPI:
             
            ACCE_SDI_TRIS=1;		   
            ACCE_SDO_TRIS=0;		   
            ACCE_SCL_TRIS=0;		   
            ACCE_CSN_TRIS=0;
 		   
            //SPI module configuration           
            SSP2STAT=0b11000000; 
            SSP2CON2=0b00000000;
            SSP2CON1=0b00100000;
             
            //Accelerometer configuration for the pulse detection            
            ACCE_ADRESS=MCTL;	
            ACCE_DATA_OUT= 0b01000011 ;	//b'01000011';
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT );	
 
            //Configuratio for TAP
            //Sense configuration            
            ACCE_ADRESS=PDTH;
            ACCE_DATA_OUT=ACCE_TAP_SENSI ;
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT );
 
            //Pulse window           
            ACCE_ADRESS=PW;
            ACCE_DATA_OUT=ACCE_TAP_WINDOW;
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT );
 
            //Latency with the second pulse             
            ACCE_ADRESS=LT;
            ACCE_DATA_OUT=ACCE_TAP_LAT;
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT );		
 
            //Second pulse window            
            ACCE_ADRESS=TW;
            ACCE_DATA_OUT=ACCE_TAP_WINDOW;
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT );	
 
            //Interruptions assignment            
            ACCE_ADRESS=CTL1;
            ACCE_DATA_OUT=0b00000100;	                                        //b'00000100';
            ACCE_WRITE(ACCE_ADRESS, ACCE_DATA_OUT );	
        
        break;
         
        case ACCELEROMETER_I2C:
             
            /*******************************************************************
            * Accelerometer must be in Standby mode to be configured           *
            * Default value: standby                                           *
            *******************************************************************/
            //thres, Tap, window,latency
             
            /****** Accelerometer configuration for the pulse detection********/
             
            //1. Enable X and Y and Z Double and Single Pulse 
            
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=0b01111111; 
            ACCE_ADRESS = PULSE_CFG_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C           
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            /******************************************************************/
             
            //2. Set threshol
            
            //Threshold X
             
            // Start I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=ACCE_TAP_SENS_THR_I2C; 
            ACCE_ADRESS = PULSE_THSX_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C            
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Threshold Y
             
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=ACCE_TAP_SENS_THR_I2C; 
            ACCE_ADRESS = PULSE_THSY_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C           
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Threshold Z
             
            // Start I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
           
            ACCE_DATA_OUT=ACCE_TAP_SENS_THR_I2C; 
            ACCE_ADRESS = PULSE_THSZ_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C            
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            
            /******************************************************************/
             
            //3. Time limit for tap detection          
                         
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
           
            ACCE_DATA_OUT=ACCE_TAP_LIMIT_I2C; 
            ACCE_ADRESS = PULSE_TMLT_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C           
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
                          
            /******************************************************************/
            
            //4. Latency 
             
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=ACCE_TAP_LAT_I2C; 
            ACCE_ADRESS = PULSE_LTCY_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C            
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
                          
            /******************************************************************/
            
            //Second pulse Window
            
            // Start I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=ACCE_TAP_WINDOW_I2C; 
            ACCE_ADRESS = PULSE_WIND_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C            
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
                         
            /******************************************************************/
             
            // Start I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=0b00000010;                                           //8G
            ACCE_ADRESS = PULSE_CFG_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C           
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            /*************Configure accelerometer range************************/
            
            // Start I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            
            ACCE_DATA_OUT=0b00000000;                                           //8G
            ACCE_ADRESS = XYZ_DATA_CFG_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
                                                                                //Stop I2C
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            /*****************Enable Pulse and DRDY interrupt *****************/
           
            // Start I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=0b00001001;
            ACCE_ADRESS = CTRL_REG4_REGISTER;  
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            //Stop I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.PEN = 1; 
             
            /***Configure INT1 as DRDY interrupt and INT2 as pulse interrupt***/
            
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=0b00000001;
            ACCE_ADRESS = CTRL_REG5_REGISTER;
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
             
            //Stop I2C            
            SSP2CON2bits.PEN = 1;           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
                      
            //******************Set up interrupt 1 and 2***********************/
            
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            ACCE_DATA_OUT=0x02;
            ACCE_ADRESS = CTRL_REG3_REGISTER;  
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            //Stop I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.PEN = 1; 
                       
            /****************Turn on accelerometer (measurement)***************/
            
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
            
            
            ACCE_DATA_OUT=0b00000001;                                           //ACCE_DATA_OUT=0b00000011; //Active; 8 bit; 800KHz
            ACCE_ADRESS = CTRL_REG1_REGISTER;                                   //ACCE_DATA_OUT=0b00010011; 
            ACCE_WRITE(ACCE_ADRESS,ACCE_DATA_OUT);	
            
            //Stop I2C           
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.PEN = 1; 
             
            /******************************************************************/
            
            // Start I2C            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C
            SSP2CON2bits.SEN    = 1;
            
            while((SSP2CON2 & 0b00011111) || (SSP2STAT & 0b00000100));          //Wait I2C 
        break;
    }
     
    //Common operations
    
    //*****************TRISB**************************//
    ACCE_INT1_DRDY_TRIS=1;
    ACCE_INT2_TRIS=1;
    PMCONH=0b00000000;
    ACCE_CSN=1;
      
}

//*****************************************************



//*****************************************************
//*              SEN_ACCE_GET_TYPE			          *
//*****************************************************
//*		Description:Returns the accelerometer  	      *
//* 	type.           	                          *
//;****************************************************
//;*Input variables:                                  *
//;*Output variables:            -type_accelerometer  *
//;****************************************************

unsigned char SEN_ACCE_GET_TYPE(void)
{
    return type_accelerometer;
}