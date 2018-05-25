#ifndef __LIB_MOT_MOWAY_H
    #define __LIB_MOT_MOWAY_H

    #include "p18f87j50.h"
    #include "delays.h"

    void MOT_CONFIG(void);
    char MOT_STR(char MOT_VEL,char FWDBACK,char COMTYPE,char MOT_T_DIST);
    char MOT_CHA_VEL(char MOT_VEL,char FWDBACK,char RL,char COMTYPE,char MOT_T_DIST);
    char MOT_ROT(char MOT_VEL,char FWDBACK,char MOT_CENWHEEL,char RL,char COMTYPE,char MOT_T_ANG);
    char MOT_CUR(char MOT_VEL,char FWDBACK,char MOT_RAD,char RL,char COMTYPE,char MOT_T_DIST);
    char MOT_STOP(void);
    char MOT_RST(char RST_COM);
    char MOT_FDBCK(char STATUS_COM);
    void Start_I2C2 (void);
    char IN_ACK_NACK2 (void);
    void Stop_I2C2 (void);
    char Read_I2C2 (void);
    void Write_I2C2 (unsigned char dato);
    void OUT_ACK2 (void);
    void OUT_NACK2 (void);
    char MOT_SND_I2C_1D(char MOT_DATA_0);
    char MOT_SND_I2C_3D(char MOT_DATA_0,char MOT_DATA_1,char MOT_DATA_2);
    char MOT_SND_I2C_4D(char MOT_DATA_0,char MOT_DATA_1,char MOT_DATA_2,char MOT_DATA_3);

    //**************************************************
    //*                 DEFINITIONS                    *
    //**************************************************
    
    //*******************PORTE************************//
    #define SDA_SOFT      PORTEbits.RE1                                         //  PIN_E1
    #define SCL_SOFT      PORTEbits.RE0                                         //	PIN_E0
    #define MOT_END       PORTEbits.RE7                                         //	PIN_E7

    //*******************TRISE************************//
    #define SCL_TRIS      TRISEbits.TRISE0                                      //	TRISE,0
    #define SDA_TRIS      TRISEbits.TRISE1                                      //	TRISE,1
    #define MOT_END_TRIS  TRISEbits.TRISE7                                      //	TRISE,7

    //Engine module adress
    #define   MOT_DIR         0x10

    //Comands
    //Byte MOT_COMAND                nºbit    7   6   5   4   3   2   1   0
    //                                       --------------------------------
    //Movement commands
    #define   COM_STR         0x00   //      "0   0   0   0   0   0   CT  RL"
    #define   COM_CHA_VEL     0x01   //      "0   0   0   0   0   1   CT  RL"
    #define   COM_ROT         0x02   //      "0   0   0   0   1   0   CT  RL"
    #define   COM_CUR         0x03   //      "0   0   0   0   1   1   CT  RL"
    #define   COM_STOP        0x04   //      "0   0   0   1   0   0   CT  RL"

    //Information commands
    #define   STATUS_T        0x00   //      "1   0   0   0   0   0   0   0 "
    #define   STATUS_A        0x01   //      "1   0   0   0   0   0   0   1 "
    #define   STATUS_V_R      0x02   //      "1   0   0   0   0   0   1   0 "
    #define   STATUS_V_L      0x03   //      "1   0   0   0   0   0   1   1 "
    #define   STATUS_D_R      0x04   //      "1   0   0   0   0   1   0   0 "
    #define   STATUS_D_L      0x05   //      "1   0   0   0   0   1   0   1 "
    #define   STATUS_KM       0x06   //      "1   0   0   0   0   1   1   0 "

    //Reset commands   
    #define   RST_T           0x00   //      "1   1   1   1   0   0   0   0 "
    #define   RST_D           0x01   //      "1   1   1   1   0   0   0   1 "
    #define   RST_KM          0x02   //      "1   1   1   1   0   0   1   0 "

    //Parameters    
    #define   RIGHT           1
    #define   LEFT            0

    #define   DISTANCE        0
    #define   TIME            1
    #define   ANGLE           0

    #define   FWD             1
    #define   BACK            0

    #define   CENTER          1
    #define   WHEEL           0

    //**************************************************
#endif

