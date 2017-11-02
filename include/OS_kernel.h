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


#ifndef __Kernel__
#define __Kernel__


#define READ_REG(Register) (Register)
#define WRITE_REG(Register, Data) (Register = (Data))

#define OS_DisableInterrupt()         (WRITE_REG(VICIntEnClr,0xFFFFFFFF))
#define OS_EnableInterrupt()          (WRITE_REG(VICIntEnClr,0x00000000))
#define OS_Get_Interrupt_Mask()       (READ_REG(VICIntEnable))
#define OS_Set_Interrupt_Mask(mask)   (WRITE_REG(VICIntEnable,mask))


typedef void (*FUNCPTR)(void);

typedef struct
{
    BYTE        task_id_no;
    FUNCPTR     task_main;
    UINT       *stack_ptr;
    USHORT      stack_size;
}OS_Task_Entry_TBL;



void    OS_Create_Task(BYTE Task_Id,FUNCPTR func,UINT *init_stack_ptr,USHORT stack_size);
void    OS_Change_Task(BYTE Task_Id,FUNCPTR func);

void    OS_Start_Task(BYTE Start_Task_Id);
void    OS_Exit_Task(void);
void    OS_End_Task(void);
void    OS_Delete_Task(BYTE Task_Id);

void    OS_Sleep_Task(BYTE Task_Id);
void    OS_Resume_Task(BYTE Task_Id);
void    StartTimer(UINT *clock);
UINT   ReadTimer(UINT *clock);
void    StartTimer3(UINT *clock);
UINT   ReadTimer3(UINT *clock);

void    WaitTimer(UINT timer);
void    OS_Init_Stack(BYTE Task_Id,UINT *init_stack_ptr);
void    CheckStack(void);
void    OS_Entry_Intercept_Task(BYTE Task_Id);

#define OS_Task_Max     4

extern const OS_Task_Entry_TBL OS_Task_Tbl[OS_Task_Max];





#endif 
