#ifndef __SENS_SPEAKER_H
    #define __SENS_SPEAKER_H

    #include "p18f87j50.h"  

    void SEN_SPEAKER_CONFIG(void);
    unsigned char SEN_SPEAKER ( unsigned char SEN_SPEAKER_FREQ, unsigned char SEN_SPEAKER_TIME, unsigned char SEN_SPEAKER_ON_OFF);

    //********************PORTB***********************// 
    #define   SPEAKER           PORTBbits.RB3                               	//PORTB,3

    //********************TRISB***********************//   
    #define   SPEAKER_TRIS         TRISBbits.TRISB3                             //TRISB,3

    //******Variables to check speaker mode***********//  
    #define		SPEAKER_OFF		0		
    #define		SPEAKER_ON		1		
    #define 	SPEAKER_TIME	2	

    //************************************************//
#endif	