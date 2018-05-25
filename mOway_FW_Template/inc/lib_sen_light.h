#ifndef __SENSOR_LUZ_H
    #define __SENSOR_LUZ_H
    #include "p18f87j50.h"  

    void SEN_LIGHT_CONFIG(void);
    unsigned char SEN_LIGHT(void);

    //*******************PORTA************************//   
    #define   LIGHT_SEN		PORTAbits.RA0                                       //PORTA,0

    //*******************TRISA************************//   
    #define   LIGHT_SEN_TRIS       TRISAbits.TRISA0                             //TRISA,0

    //************************************************//
#endif

