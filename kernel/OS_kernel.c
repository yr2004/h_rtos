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
//Filename:   @  kernl.c                                             
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
#include ".\user\main.h"

void OS_Schedule_Task(void);
void _OS_Modify_Task(void);

#define OS_Dead          0
#define OS_Ready         1
#define OS_Run           2
#define OS_Wait_Event    3
#define OS_Wait_Time     4
#define OS_Sleep         5

enum    
{
    eRegiMax = 16
};

vULONG   Iram_system_timer;
vULONG   Iram_timer3_counter;
vBYTE    Iram_Intercept_Task;
vBYTE    Iram_send_event_semphore;
vBYTE    Iram_irq_flag;

UINT    OS_System_Event[OS_Task_Max];
UINT    OS_Regi[OS_Task_Max][eRegiMax];
BYTE    OS_Task_No;
BYTE    OS_Task_State[OS_Task_Max];
UINT    OS_Rem_Stack[OS_Task_Max];
UINT    OS_Init_Stack_Ptr[OS_Task_Max];
BYTE    OS_W_Task_Id;
FUNCPTR OS_W_Func;
BYTE    OS_Previous_Task_No;

//***********************************************************************
//** function:     % OS_Save_CPU_Register
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
extern void OS_Save_CPU_Register(void);

//***********************************************************************
//** function:     % OS_Restore_CPU_Register
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
extern void OS_Restore_CPU_Register(void);

//***********************************************************************
//** function:     % OS_Create_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Create_Task(BYTE Task_Id,FUNCPTR func,UINT *init_stack_ptr,USHORT stack_size)
{
    BYTE    i;

    init_stack_ptr += ((stack_size / 4) - 1);
    *init_stack_ptr = (UINT)func;
    init_stack_ptr--;

    for(i = 0;i < eRegiMax;i++) 
    {
    	OS_Regi[Task_Id][i] = 0L;
    }
    OS_Regi[Task_Id][13] = (UINT)init_stack_ptr;       /* intilaize register       */

//  system_event[Task_Id]   = 0x0L;
    OS_Task_State[Task_Id]  = OS_Ready;

    Iram_Intercept_Task = 0xFF;
}

//***********************************************************************
//** function:     % OS_Change_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Change_Task(BYTE Task_Id,FUNCPTR func)
{
    OS_W_Task_Id = Task_Id;
    OS_W_Func = func;

    _OS_Modify_Task();

    if(OS_W_Task_Id == OS_Task_No)
    {
        OS_Restore_CPU_Register();
    }
}

//***********************************************************************
//** function:     % _OS_Modify_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void _OS_Modify_Task(void)
{
    BYTE    i;
    UINT   *init_stack_ptr;
    USHORT  stack_size;

    init_stack_ptr = OS_Task_Tbl[OS_W_Task_Id].stack_ptr;
    stack_size     = ((OS_Task_Tbl[OS_W_Task_Id].stack_size / 4) - 1);

    init_stack_ptr     += stack_size;
    *init_stack_ptr = (UINT)OS_W_Func;
    init_stack_ptr--;

    for(i = 0;i < eRegiMax;i++) 
    {
        OS_Regi[OS_W_Task_Id][i] = 0L;
    }
	
    OS_Regi[OS_W_Task_Id][13] = (UINT)init_stack_ptr;     /* intilaize register       */

//  system_event[OS_W_Task_Id] = 0x0L;
    OS_Task_State[OS_W_Task_Id] = OS_Ready;
}

//***********************************************************************
//** function:     % OS_Start_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Start_Task(BYTE Start_Task_Id)
{
    OS_Task_No = Start_Task_Id;
    OS_Previous_Task_No = Start_Task_Id;
    OS_Task_State[OS_Task_No] = OS_Run;
    OS_Restore_CPU_Register();
}

//***********************************************************************
//** function:     % OS_End_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_End_Task(void)
{
    OS_Task_State[OS_Task_No] = OS_Dead;
    while(1) 
    {
        OS_Exit_Task();
    }
}

//***********************************************************************
//** function:     % OS_Delete_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Delete_Task(BYTE Task_Id)
{
    OS_Task_State[Task_Id] = OS_Dead;
}

//***********************************************************************
//** function:     % OS_Sleep_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Sleep_Task(BYTE Task_Id)
{
    OS_Task_State[Task_Id] = OS_Sleep;
    if(Task_Id == OS_Task_No)
    {
        while(OS_Task_State[Task_Id] == OS_Sleep) 
        {
            OS_Exit_Task();
        }
    }
}

//***********************************************************************
//** function:     % OS_Resume_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Resume_Task(BYTE Task_Id)
{
    OS_Task_State[Task_Id] = OS_Ready;
}

//***********************************************************************
//** function:     % OS_Exit_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Exit_Task(void)
{
    OS_Save_CPU_Register();
    /* Check if current task stack overflow before
           switch to next stack */
    if ((*(BYTE *)OS_Init_Stack_Ptr[OS_Task_No]) != (OS_Task_No+1))
    {
        //send_msg54(SHOW_DEBUG_MSG,'S','T','O',OS_Task_No);
        while(1)
        {
        }
    }
    OS_Schedule_Task();
//  CheckStack();
    OS_Restore_CPU_Register();
}

//***********************************************************************
//** function:     % OS_Schedule_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Schedule_Task(void)
{
    OS_Task_State[OS_Task_No] = OS_Ready;

    /* Check if the high priority task executes " MDF-1" */
    if( Iram_Intercept_Task != 0xFF )
    {
        OS_Previous_Task_No = OS_Task_No;
        OS_Task_No = Iram_Intercept_Task;
        Iram_Intercept_Task = 0xFF;
        OS_Task_State[OS_Task_No] = OS_Run;
        return;
    }

    OS_Task_No = OS_Previous_Task_No;

    while(1)
    {
        OS_Task_No++;
        if(OS_Task_No >= OS_Task_Max) 
        {
            OS_Task_No = 0;
        }
        if(OS_Task_State[OS_Task_No] == OS_Ready)  
        {
			break;
        }
        if(OS_Task_State[OS_Task_No] == OS_Wait_Time)    
        {
            break;
        }
        if(OS_Task_State[OS_Task_No] == OS_Wait_Event)   
        {
            break;
        }
    }

    OS_Previous_Task_No = OS_Task_No;

    OS_Task_State[OS_Task_No] = OS_Run;
}

//***********************************************************************
//** function:     % WaitTimer
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
/*-----------------------------------------------------------------------------
 *
 * Module: WaitTimer()
 * Description:Wait for a long time while other thread can still running.
 *             If one need a very accurate and short delay use DelaymS() or Delay100uS() instead.
 *             For servo state change delay please use SetDelayTimer().
 *             timer <= actual delay time < timer + 1
 *
 *----------------------------------------------------------------------------*/
void WaitTimer(UINT timer)
{
    UINT clock, temp_IE;

    temp_IE = OS_Get_Interrupt_Mask();    /* disable interrupts */
    OS_DisableInterrupt();
    clock = Iram_system_timer;
    OS_Set_Interrupt_Mask(temp_IE);       /* restore interrupts */

    OS_Task_State[OS_Task_No] = OS_Wait_Time;

    while (ReadTimer(&clock) <= timer)
    {
        OS_Exit_Task();
    }

    OS_Task_State[OS_Task_No] = OS_Run;
}

//***********************************************************************
//** function:     % StartTimer
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void StartTimer(UINT *clock)
{
    UINT   temp_IE;

    temp_IE = OS_Get_Interrupt_Mask();    /* disable interrupts */
    OS_DisableInterrupt();
    *clock = (UINT)Iram_system_timer;
    OS_Set_Interrupt_Mask(temp_IE);       /* restore interrupts */

}

//***********************************************************************
//** function:     % StartTimer3
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void StartTimer3(UINT *clock)
{
    UINT   temp_IE;

    temp_IE = OS_Get_Interrupt_Mask();    /* disable interrupts */
    OS_DisableInterrupt();
    *clock = (UINT)Iram_timer3_counter;
    OS_Set_Interrupt_Mask(temp_IE);       /* restore interrupts */
}

//***********************************************************************
//** function:     % ReadTimer
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
UINT ReadTimer(UINT *clock)
{
    UINT temp_IE, temp;

    temp_IE = OS_Get_Interrupt_Mask();    /* disable interrupts */
    OS_DisableInterrupt();
    temp = (Iram_system_timer >= *clock)? ((UINT)Iram_system_timer - *clock) : ((UINT)Iram_system_timer + (~(*clock)));
    OS_Set_Interrupt_Mask(temp_IE);       /* restore interrupts */

    return (temp);
}

//***********************************************************************
//** function:     % ReadTimer3
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
UINT ReadTimer3(UINT *clock)
{
    UINT temp_IE, temp;

    temp_IE = OS_Get_Interrupt_Mask();    /* disable interrupts */
    OS_DisableInterrupt();
    temp = ((UINT)Iram_timer3_counter - *clock) * 250L;
    OS_Set_Interrupt_Mask(temp_IE);       /* restore interrupts */

    return (temp);
}

//***********************************************************************
//** function:     % OS_Init_Stack
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Init_Stack(BYTE Task_Id,UINT *init_stack_ptr)
{
    OS_Init_Stack_Ptr[Task_Id] = (UINT)init_stack_ptr;

}

//***********************************************************************
//** function:     % OS_Entry_Intercept_Task
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Entry_Intercept_Task(BYTE Task_Id)
{
    Iram_Intercept_Task = Task_Id;

}




