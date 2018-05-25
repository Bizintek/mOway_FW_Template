#ifndef __LED_CONTROL_H
    #define __LED_CONTROL_H

    #include "p18f87j50.h"  

    void SEN_LED_CONFIG(void);
    void LED_FRONT_ON(void);
    void LED_FRONT_OFF(void);
    void LED_FRONT_ON_OFF(void);
    void LED_BRAKE_ON(void);
    void LED_BRAKE_OFF(void);
    void LED_BRAKE_ON_OFF(void);
    void LED_TOP_RED_ON(void);
    void LED_TOP_RED_OFF(void);
    void LED_TOP_RED_ON_OFF(void);
    void LED_TOP_GREEN_ON(void);
    void LED_TOP_GREEN_OFF(void);
    void LED_TOP_GREEN_ON_OFF(void);

    //*********************PORTB**********************//
    #define   LED_TOP_RED       PORTBbits.RB5                                   //PORTB,5
    #define   LED_TOP_GREEN     PORTBbits.RB6                                   //PORTB,6

    //*********************PORTC**********************//
    #define   LED_FRONT		PORTCbits.RC7                                       //PORTC,7

    //*********************PORTE**********************//
    #define   LED_BRAKE		PORTEbits.RE5                                       //PORTE,5

    //*********************TRISB**********************//
    #define   LED_TOP_RED_TRIS     TRISBbits.TRISB5                             //TRISB,5
    #define   LED_TOP_GREEN_TRIS   TRISBbits.TRISB6                             //TRISB,6

    //*********************TRISC**********************//
    #define   LED_FRONT_TRIS       TRISCbits.TRISC7                             //TRISC,7

    //*********************TRISE**********************//
    #define   LED_BRAKE_TRIS	   TRISEbits.TRISE5                             //TRISE,5

    //************************************************//
#endif