#ifndef __SENS_LINEA_H
    #define __SENS_LINEA_H

    #include "p18f87j50.h" 
    
    void SEN_LINE_CONFIG(void);
    unsigned char SEN_LINE_ANALOG (unsigned char LINE_TO_CHECK);
    unsigned char SEN_LINE_DIG(unsigned char LINE_TO_CHECK);
  
    //*********************PORTA**********************//
    #define   LINE_RX_R     PORTAbits.RA2                                       //PORTA,2
    #define   LINE_RX_L     PORTAbits.RA5                                       //PORTA,5

    //*********************PORTD**********************//   
    #define   LINE_TX           PORTDbits.RD1                                   //PORTD,1

    //*********************TRISA**********************//   
    #define   LINE_RX_R_TRIS       TRISAbits.TRISA2                             //TRISA,2
    #define   LINE_RX_L_TRIS       TRISAbits.TRISA5                             //TRISA,5

    //*********************TRISD**********************//   
    #define   LINE_TX_TRIS         TRISDbits.TRISD1                             //TRISD,1

    //**Variables to indicate the line to be checked**//
    #define 	LINE_L			0
    #define		LINE_R			1

    //************************************************//
#endif
    
