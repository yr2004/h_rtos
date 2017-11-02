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
//Filename:   @  user.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//

#include ".\include\datatype.h"

#ifndef __User__
#define __User__


#define SEQ_EX0         0
#define SEQ_EX1         1
#define SEQ_EX2         2
#define SEQ_EX3         3
#define SEQ_EX4         4
#define SEQ_BUSY        5


#define BASE_TIME   1000                /* 1ms */
#define BASE_COUNT  (1000/BASE_TIME)

#define SEC_1       ((  1*BASE_COUNT)*1000)
#define SEC_2       ((  2*BASE_COUNT)*1000)
#define SEC_3       ((  3*BASE_COUNT)*1000)
#define SEC_4       ((  4*BASE_COUNT)*1000)
#define SEC_5       ((  5*BASE_COUNT)*1000)
#define SEC_6       ((  6*BASE_COUNT)*1000)
#define SEC_9       ((  9*BASE_COUNT)*1000)
#define SEC_10      (( 10*BASE_COUNT)*1000)
#define SEC_15      (( 15*BASE_COUNT)*1000)
#define SEC_30      (( 30*BASE_COUNT)*1000)
#define SEC_60      (( 60*BASE_COUNT)*1000)
#define MS_1        ((  1*BASE_COUNT)     )
#define MS_2        ((  2*BASE_COUNT)     )
#define MS_3        ((  3*BASE_COUNT)     )
#define MS_4        ((  4*BASE_COUNT)     )
#define MS_5        ((  5*BASE_COUNT)     )
#define MS_6        ((  6*BASE_COUNT)     )
#define MS_7        ((  7*BASE_COUNT)     )
#define MS_8        ((  8*BASE_COUNT)     )
#define MS_9        ((  9*BASE_COUNT)     )
#define MS_10       (( 10*BASE_COUNT)     )
#define MS_11       (( 11*BASE_COUNT)     )
#define MS_12       (( 12*BASE_COUNT)     )
#define MS_13       (( 13*BASE_COUNT)     )
#define MS_14       (( 14*BASE_COUNT)     )
#define MS_15       (( 15*BASE_COUNT)     )
#define MS_16       (( 16*BASE_COUNT)     )
#define MS_17       (( 17*BASE_COUNT)     )
#define MS_18       (( 18*BASE_COUNT)     )
#define MS_19       (( 19*BASE_COUNT)     )
#define MS_20       (( 20*BASE_COUNT)     )
#define MS_21       (( 21*BASE_COUNT)     )
#define MS_22       (( 22*BASE_COUNT)     )
#define MS_23       (( 23*BASE_COUNT)     )
#define MS_24       (( 24*BASE_COUNT)     )
#define MS_25       (( 25*BASE_COUNT)     )
#define MS_30       (( 30*BASE_COUNT)     )
#define MS_35       (( 35*BASE_COUNT)     )
#define MS_40       (( 40*BASE_COUNT)     )
#define MS_45       (( 45*BASE_COUNT)     )
#define MS_50       (( 50*BASE_COUNT)     )
#define MS_55       (( 55*BASE_COUNT)     )
#define MS_60       (( 60*BASE_COUNT)     )
#define MS_65       (( 65*BASE_COUNT)     )
#define MS_70       (( 70*BASE_COUNT)     )
#define MS_75       (( 75*BASE_COUNT)     )
#define MS_80       (( 80*BASE_COUNT)     )
#define MS_85       (( 85*BASE_COUNT)     )
#define MS_90       (( 90*BASE_COUNT)     )
#define MS_92       (( 92*BASE_COUNT)     )
#define MS_95       (( 95*BASE_COUNT)     )
#define MS_100      ((100*BASE_COUNT)     )
#define MS_110      ((110*BASE_COUNT)     )
#define MS_120      ((120*BASE_COUNT)     )
#define MS_150      ((150*BASE_COUNT)     )
#define MS_160      ((160*BASE_COUNT)     )
#define MS_180      ((180*BASE_COUNT)     )
#define MS_184      ((184*BASE_COUNT)     )
#define MS_200      ((200*BASE_COUNT)     )
#define MS_205      ((205*BASE_COUNT)     )
#define MS_210      ((210*BASE_COUNT)     )
#define MS_215      ((215*BASE_COUNT)     )
#define MS_220      ((220*BASE_COUNT)     )
#define MS_225      ((225*BASE_COUNT)     )
#define MS_230      ((230*BASE_COUNT)     )
#define MS_240      ((240*BASE_COUNT)     )
#define MS_250      ((250*BASE_COUNT)     )
#define MS_255      ((255*BASE_COUNT)     )
#define MS_260      ((260*BASE_COUNT)     )
#define MS_300      ((300*BASE_COUNT)     )
#define MS_350      ((350*BASE_COUNT)     )
#define MS_400      ((400*BASE_COUNT)     )
#define MS_500      ((500*BASE_COUNT)     )
#define MS_700      ((700*BASE_COUNT)     )
#define MS_800      ((800*BASE_COUNT)     )
#define MS_1000     ((1000*BASE_COUNT)    )
#define MS_1300     ((1300*BASE_COUNT)    )
#define TIMER_STOP  (0xFFFF)

#define SCB_NOP             0x0FE0
#define SEQ_ILL             0x001F

#define SEQ_ERR             0x00FE
#define SEQ_001             0x0000
#define SEQ_002             0x0001
#define SEQ_003             0x0002
#define SEQ_004             0x0003
#define SEQ_005             0x0004
#define SEQ_006             0x0005
#define SEQ_007             0x0006
#define SEQ_END             0x00FF

#define SCB_001             0x0000
#define SCB_002             0x0001
#define SCB_003             0x0002
#define SCB_004             0x0003
#define SCB_005             0x0004
#define SCB_006             0x0005
#define SCB_007             0x0006

#define SCB_STA_001             0x0000
#define SCB_STA_002             0x0001
#define SCB_STA_003             0x0002

typedef struct sub_SCB_arg_tbl
{
    UINT      arg[3];
}SUB_SCB_ARG_TBL;


typedef struct sub_SCB_tbl
{
    UINT      			(*func)(void);
    SUB_SCB_ARG_TBL 	sub_SCB_arg;
    UINT      			next_sub_SCB_no[5];
}SUB_SCB_TBL;


typedef struct SCB_tbl   //SCB table
{
    UINT      next_SCB_no;
    SUB_SCB_TBL     *tbl;
}SCB_TBL;


void sub_SCB_execute (SUB_SCB_TBL  *p);
void SCB_table_state_machine(void);  


#endif 