#ifndef __SENS_OBSTAC_H
    #define __SENS_OBSTAC_H

    #include "p18f87j50.h"  

    void SEN_OBSTAC_CONFIG(void);    
    unsigned char SEN_OBS_ANALOG(unsigned char OBS_TO_CHECK);
    unsigned char SEN_OBS_DIG (unsigned char OBS_TO_CHECK);

    //*******************PORTA************************//    
    #define   IR_RX_L_1     PORTAbits.RA1                                       //PORTA,1
    #define   IR_RX_L_2     PORTAbits.RA3                                       //PORTA,3

    //*******************PORTF************************//  
    #define   IR_RX_R_2     PORTFbits.RF5                                       //PORTF,5
    #define   IR_RX_R_1     PORTFbits.RF6                                       //PORTF,6

    //*******************PORTJ************************//   
    #define   LED_IR        PORTJbits.RJ7                                       //PORTJ,7
    #define   IR_TX         PORTJbits.RJ6                                       //PORTJ,6

    //*******************TRISA************************//
    #define   IR_RX_L_1_TRIS       TRISAbits.TRISA1                             //TRISA,1
    #define   IR_RX_L_2_TRIS       TRISAbits.TRISA3                             //TRISA,3

    //*******************TRISF************************//   
    #define   IR_RX_R_2_TRIS       TRISFbits.TRISF5                             //TRISF,5
    #define   IR_RX_R_1_TRIS       TRISFbits.TRISF6                             //TRISF,6

    //*******************TRISJ************************//  
    #define   LED_IR_TRIS          TRISJbits.TRISJ7                             //TRISJ,7
    #define   IR_TX_TRIS           TRISJbits.TRISJ6                             //TRISJ,6

    //********Variables to indicate the obstacle sensor to be checked********//   
    #define		OBS_CENTER_L	0
    #define		OBS_SIDE_L		1
    #define		OBS_CENTER_R	2
    #define		OBS_SIDE_R		3

    //************************************************//  
#endif


