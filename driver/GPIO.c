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
//Filename:   @  GPIO.c                                             
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
#include ".\driver\GPIO.h"



//***********************************************************************
//** function:     % init_GPIO
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_GPIO(void)  
{
    LONG GPIO_Data;
    
    GPIO_Data = 0x1F0000;
    
    IO0DIR = GPIO_Data;


}



//***********************************************************************
//** function:     % Set_GPIO
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void Set_GPIO(BYTE channel,BYTE value)
{
    LONG GPIO_Data;
        
    GPIO_Data = IO0SET;    
        
    if(value==1)
      {
       IO0SET = (GPIO_Data|(1 << channel));
      }
    else
      {
       IO0CLR = (GPIO_Data|(1 << channel));
      }

}



//***********************************************************************
//** function:     % Read_GPIO
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
LONG Read_GPIO()
{
    LONG GPIO_Data;
    
    GPIO_Data = IO0PIN;
    
    return(GPIO_Data);
}




