/*
***********************************************************************************
*                                        H-OS
*                                The Real-Time Kernel
*                                   TASK MANAGEMENT
*
*                      (c) Copyright 2007-2077, Harriman Hao
*                                 All Rights Reserved
*/
//*******************************************************************************//
//Filename:   @  modem.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//

#define NOT_INIT_MODEM      0x00
#define NOT_FIND_MODEM      0x01
#define MODEM_CLOSE         0x02
#define MODEM_RING          0x03
#define MODEM_CONNECT       0x05


#ifndef IN_MODEM

extern uint8 GetModemState(void);
extern uint8 ModemWrite(char *Data, uint16 NByte);
extern uint8 ModemGetch(void);
extern uint8 ModemDialUp(char Number[]);
extern uint8 ModemDialDown(void);
extern uint8 ModemInit(uint32 bps);
extern void UART1_Exception(void);

#endif

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
