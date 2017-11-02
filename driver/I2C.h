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
//Filename:   @  i2c.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//


#ifndef __I2C__
#define __I2C__


extern void  I2c_Exception(void);
extern BYTE  I2c_SendByte(BYTE Address, BYTE Data);
extern BYTE  I2c_SendStr(BYTE Address, BYTE SubAddress, BYTE *Buffer, BYTE Num);
extern BYTE  I2c_RcvByte(BYTE Address, BYTE *Data);
extern BYTE  I2c_RcvStr(BYTE Address, BYTE SubAddress, BYTE *Buffer, BYTE Num);


#endif

