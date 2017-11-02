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
//Filename:   @  rtc.c                                             
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
#include ".\driver\spi.h"
#include ".\driver\I2C.h"
#include ".\driver\rtc.h"


#define IN_RTC
//#include "config.h"

//***********************************************************************
//** function:     % init_RTC
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_RTC(void)  
{
    CCR = 1;
    PREINT = Fpclk / 32768 - 1;
    PREFRAC = Fpclk - (Fpclk / 32768) * 32768;
}



//***********************************************************************
//** function:     % getdate
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void getdate(struct date *today)
{
    OS_DisableInterrupt();
    today->da_year = YEAR;
    today->da_mon = MONTH;
    today->da_day = DOM;
    today->da_dow = DOW;
    OS_EnableInterrupt();
}



//***********************************************************************
//** function:     % gettime
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void gettime(struct time *now)
{
    OS_DisableInterrupt();
    now->ti_hour = HOUR;
    now->ti_min = MIN;
    now->ti_sec = SEC;
    now->ti_hund = (CTC * 100) / 32768;
    OS_EnableInterrupt();
}



//***********************************************************************
//** function:     % setdate
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void setdate(struct date *today)
{
    OS_DisableInterrupt();
    YEAR = today->da_year;
    MONTH = today->da_mon;
    DOM = today->da_day;
    DOW = today->da_dow;
    OS_EnableInterrupt();
}



//***********************************************************************
//** function:     % settime
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void settime(struct time *now)
{
    OS_DisableInterrupt();
    HOUR = now->ti_hour;
    MIN = now->ti_min;
    SEC = now->ti_sec;
    OS_EnableInterrupt();
}



