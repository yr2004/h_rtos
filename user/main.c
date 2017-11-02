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
//Filename:   @  main.c                                             
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


int main(void)
{
    UINT i, j;
    UINT dwData = 0;
   
    for(i = 0;i < OS_Task_Max;i++)
    {
        dwData=(i+1);
        dwData|=(dwData<<8);
        dwData|=dwData<<16;
        for(j = 0; j < (OS_Task_Tbl[i].stack_size / 4); j++)
        {
            (OS_Task_Tbl[i].stack_ptr)[j] = dwData;
        }
        OS_Create_Task(OS_Task_Tbl[i].task_id_no,OS_Task_Tbl[i].task_main,
                     OS_Task_Tbl[i].stack_ptr,OS_Task_Tbl[i].stack_size); /* Task entrey */
        OS_Init_Stack(OS_Task_Tbl[i].task_id_no,OS_Task_Tbl[i].stack_ptr);    /* stack checker init */
    }

    OS_Start_Task(0);               /* Task start */
}
