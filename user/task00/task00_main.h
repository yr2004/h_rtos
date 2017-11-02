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


#ifndef __Task00main__
#define __Task00main__

#define Task_Cmd_idle    0x00
#define Task_Cmd_00      0x00
#define Task_Cmd_01      0x01
#define Task_Cmd_02      0x02
#define Task_Cmd_03      0x03
#define Task_Cmd_04      0x04
#define Task_Cmd_05      0x05
#define Task_Cmd_06      0x06
#define Task_Cmd_07      0x07
#define Task_Cmd_08      0x08

#define Max_SCB_Num 4

typedef struct
{
	UINT  SCB_state;
	UINT  SCB_numb;
	UINT  seq_numb;          //sub status numb
}Fuction_State_T;


void task00_main(void);
void task_cmd_decode(void);
void SCB_table_state_machine(void);  
void sub_SCB_execute(SUB_SCB_TBL  *p);

#endif









