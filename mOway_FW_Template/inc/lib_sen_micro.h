#ifndef __SENS_MICRO_H
    #define __SENS_MICRO_H
    
    #include "p18f87j50.h"  

    void SEN_MICRO_CONFIG(void);
    unsigned char SEN_MIC_ANALOG (void);
    unsigned char SEN_MIC_DIG (void);

    //********************PORTH***********************//    
    #define   MIC_IN        PORTHbits.RH7                                       //PORTH,7

    //********************TRISH***********************//
    #define   MIC_IN_TRIS          TRISHbits.TRISH7                             //TRISH,7

    //************************************************//
#endif