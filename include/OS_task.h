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
//Filename:   @  kernel.c                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//

#include ".\include\datatype.h"
#include ".\user\main.h"


#ifndef __Task__
#define __Task__


#define State           0
#define ExecutionState  1
#define Command         2
#define Parameter1      3
#define Parameter2      4
#define Parameter3      5
#define Parameter4      6
#define Parameter5      7
#define Parameter6      8
#define Parameter7      9
#define Parameter8      10
#define Parameter9      11
#define Parameter10     12


typedef unsigned char TaskStatesT;
#define Task_StateDead         0
#define Task_StateReady        1
#define Task_StateRun          2
#define Task_StateWaitEvent    3
#define Task_StateWaitTime     4
#define Task_StateSleep        5

typedef unsigned char TaskExecutionStateT;
#define Task_ExecutionReady    0
#define Task_ExecutionBusy     1
#define Task_ExecutionError    2

typedef unsigned char TaskCommandsT;
#define Task_CmdIdle           0xFF
#define Task_CmdInit           0x00
#define Task_CmdStart          0x01
#define Task_CmdStop           0x02
#define Task_Cmd003            0x03
#define Task_Cmd004            0x04
#define Task_Cmd005            0x05

typedef struct 
{
    TaskStatesT            TaskState;
    TaskExecutionStateT    TaskExecutionState;
    TaskCommandsT          TaskCommand;
    BYTE                   TaskParameters[10];
} TaskInterfaceInfoS;

extern TaskInterfaceInfoS OS_TaskInterface;

BYTE OS_Get_TaskInterface(BYTE type);
void OS_Set_TaskInterface(BYTE type,BYTE code);

void task_00(void);
void task_01(void);
void task_02(void);




#endif 
