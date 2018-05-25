#ifndef __ACELEROMETRO_H
    #define __ACELEROMETRO_H

    #include "p18f87j50.h" 

    unsigned char SEN_ACCE_XYZ_READ(unsigned char ACCE_TO_CHECK);
    unsigned char SEN_ACCE_CHECK_TAP(void);
    void ACCE_WRITE(unsigned char data1, unsigned char data2);
    unsigned char ACCE_READ(unsigned char data);
    void SEN_ACCE_CONFIG(void);
    unsigned char SEN_ACCE_GET_TYPE(void);

    //Accelerometer configurations
    #define   ACCE_TAP_SENSI		   			0b01110000			
    #define   ACCE_TAP_WINDOW		   			0b01111111			
    #define   ACCE_TAP_LAT		   				0b00000100		

    //I2C 
    #define   ACCE_TAP_SENS_THR_I2C             0b00100000                      //Set Threshold 2g
    #define   ACCE_TAP_LIMIT_I2C	   			0b00000100	                    //Set Time Limit for Tap Detection to 60 ms (LP Mode, 200 Hz ODR, No LPF)		
    #define   ACCE_TAP_LAT_I2C	   				0b01111111	                    //First pulse window. Set Latency Timer to 200 ms. 200ms/5ms = 40 counts	
    #define   ACCE_TAP_WINDOW_I2C               0b01111111                      //Second pulse. Set Time Window for Second Tap to 300 ms. 300 ms/5 ms = 60 counts

    //********************PORTB**********************//

    #define   ACCE_INT1_DRDY	PORTBbits.RB1                                   //PORTB,1
    #define   ACCE_INT2         PORTBbits.RB2                                   //PORTB,2

    //********************PORTD**********************//

    #define   ACCE_SDO          PORTDbits.RD4                                   //PORTD,4
    #define   ACCE_SDI          PORTDbits.RD5                                   //PORTD,5
    #define   ACCE_SCL          PORTDbits.RD6                                   //PORTD,6
    #define   ACCE_CSN      	PORTDbits.RD7                                   //PORTD,7
    #define   ACCEL_SDA_SOFT    PORTDbits.SDA2                                  //PORTD,5
    #define   ACCEL_SCL_SOFT    PORTDbits.SCL2                                  //PORTD,6

    //********************TRISB**********************//
    
    #define   ACCE_INT1_DRDY_TRIS  TRISBbits.TRISB1                             //TRISB,1
    #define   ACCE_INT2_TRIS       TRISBbits.TRISB2                             //TRISB,2

    //********************TRISD**********************//

    #define   ACCE_SDI_TRIS		   TRISDbits.TRISD5                             //TRISD,5
    #define   ACCE_SDO_TRIS		   TRISDbits.TRISD4                             //TRISD,4
    #define   ACCE_SCL_TRIS		   TRISDbits.TRISD6                             //TRISD,6
    #define   ACCE_CSN_TRIS		   TRISDbits.TRISD7                             //TRISD,7
    #define   ACCEL_SCL_TRIS       TRISDbits.TRISD6                             //TRISD,6
    #define   ACCEL_SDA_TRIS       TRISDbits.TRISD5                             //TRISD,5

    //***********Accelerometer register**************//
   
    #define 	XOUT8		0x06
    #define 	YOUT8		0x07
    #define 	ZOUT8		0x08
    #define 	DETSRC		0x0A
    #define 	MCTL		0x16
    #define 	INTRST		0x17
    #define 	CTL1		0x18
    #define 	PDTH		0x1B
    #define 	PW			0x1C
    #define 	LT			0x1D
    #define 	TW			0x1E

    //********Accelerometer I2C registers************//
    
    #define     ADDRESS_NEW_ACCEL_WRITE     0x38
    #define     ADDRESS_NEW_ACCEL_READ      0x39

    #define     STATUS_REGISTER             0x00
    #define     X_REGISTER                  0x01
    #define     Y_REGISTER                  0x03
    #define     Z_REGISTER                  0x05
    #define     XYZ_DATA_CFG_REGISTER       0x0E
    #define     WHO_I_AM_REGISTER           0x0D

    #define     PULSE_CFG_REGISTER          0x21
    #define     PULSE_SRC_REGISTER          0x22
    #define     PULSE_THSX_REGISTER         0x23
    #define     PULSE_THSY_REGISTER         0x24
    #define     PULSE_THSZ_REGISTER         0x25
    #define     PULSE_TMLT_REGISTER         0x26                                //First pulse time window
    #define     PULSE_LTCY_REGISTER         0x27
    #define     PULSE_WIND_REGISTER         0x28                                //Second pulse time window


    #define     CTRL_REG1_REGISTER          0x2A
    #define     CTRL_REG2_REGISTER          0x2B
    #define     CTRL_REG3_REGISTER          0x2C
    #define     CTRL_REG4_REGISTER          0x2D
    #define     CTRL_REG5_REGISTER          0x2E


    //*******Variables to indicate whether accelerometer is I2C or SP******//
    #define     ACCELEROMETER_SPI   0
    #define     ACCELEROMETER_I2C   1



    //*****Variables to indicate the accelerometer axes to be checked******//
    #define 	ACCE_CHECK_X	0
    #define 	ACCE_CHECK_Y	1
    #define 	ACCE_CHECK_Z	2

    //************************************************//
#endif	

