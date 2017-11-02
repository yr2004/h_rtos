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
//Filename:   @  user.c                                             
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


TaskInterfaceInfoS OS_TaskInterface;    


//***********************************************************************
//** function:     % OS_Get_TaskInterface
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
BYTE OS_Get_TaskInterface(BYTE type)
{
    BYTE *p;

    p = (BYTE *)&OS_TaskInterface;
    p = (p + type);
    return(*p);
}



//***********************************************************************
//** function:     % OS_Set_TaskInterface
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void OS_Set_TaskInterface(BYTE type,BYTE code)
{
    BYTE *p;

    p = (BYTE *)&OS_TaskInterface;
    p = (p + type);
    *p = code;
}



  
     
     