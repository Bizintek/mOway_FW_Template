#ifndef __BATERIA_H
    #define __BATERIA_H

    #include "p18f87j50.h" 

    void SEN_BATTERY_CONFIG(void);
    unsigned char SEN_BATTERY(void);

    //Battery level

    #define   MIN_BAT_ADC		   				132                             //Mínimun of battery equal to 3.3 V
    #define   MAX_BAT_ADC		   				162                             //Máximun of battery equal to 4.2 V
    #define   DIV_100_MAX_BAT_ADC_MIN_BAT_ADC   3


    //*********************PORTH**********************//
    #define   NTC           PORTHbits.RH5                                       //PORTH,5
    #define	  BATTERY_IN   	PORTHbits.RH6                                       //PORTH,6

    //*********************TRISH**********************//
    #define   NTC_TRIS             TRISHbits.TRISH5                             //TRISH,5
    #define	  BATTERY_TRIS         TRISHbits.TRISH6                             //TRISH,6
    
    //************************************************//
#endif








