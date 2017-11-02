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
//Filename:   @  task.c                                             
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
#include ".\user\task00\task00_main.h"
#include ".\user\task01\task01_main.h"
#include ".\user\task02\task02_main.h"

#define task_stack_00_SIZE    800
#define task_stack_01_SIZE    400
#define task_stack_02_SIZE    512

UINT task_stack_00[(task_stack_00_SIZE) / 4];
UINT task_stack_01[(task_stack_01_SIZE) / 4];
UINT task_stack_02[(task_stack_02_SIZE) / 4];

const OS_Task_Entry_TBL OS_Task_Tbl[OS_Task_Max] = 
{
    {0,task00_main        ,&task_stack_00[0]      ,sizeof(task_stack_00) },
    {1,task01_main        ,&task_stack_01[0]      ,sizeof(task_stack_01) },
    {2,task02_main        ,&task_stack_02[0]      ,sizeof(task_stack_02) },
};




