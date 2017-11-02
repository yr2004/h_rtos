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
//Filename:   @  rtc.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//

typedef struct date    
{
    WORD       da_year;        
    BYTE       da_mon;        
    BYTE       da_day;         
    BYTE       da_dow;         
};

typedef struct time    
{
    BYTE       ti_hour;        
    BYTE       ti_min;         
    BYTE       ti_sec;        
    BYTE       ti_hund;        
};

#ifndef __RTC__
#define __RTC__

extern void init_RTC(void);

extern void getdate(struct date *today);

extern void gettime(struct time *now);

extern void setdate(struct date *today);

extern void settime(struct time *now);

#endif

