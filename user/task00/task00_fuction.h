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
//Filename:   @  task00_main.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//
#include ".\boot\LPC2210.h"
#include ".\include\datatype.h"
#include ".\include\OS_kernel.h"
#include ".\include\OS_task.h"
#include ".\user\main.h"
#include ".\driver\spi.h"

#ifndef __Task00Fuction__
#define __Task00Fuction__

UINT task00_SCB01_seq01(void);
UINT task00_SCB02_seq01(void);
UINT task00_SCB03_seq01(void);

UINT task00_SCB01_seq01_err(void);
UINT task00_SCB02_seq01_err(void);
UINT task00_SCB03_seq01_err(void);

UINT task00_SCB01_seq01_other(void);
UINT task00_SCB02_seq01_other(void);
UINT task00_SCB03_seq01_other(void);


#endif









