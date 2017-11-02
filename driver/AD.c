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
//Filename:   @  ADDA.c                                             
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
#include ".\driver\AD.h"



//***********************************************************************
//** function:     % init_AD
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_AD(void)  
{
   ADCR = (1 << 0)                     |		// SEL = 1 ，选择通道0
          ((Fpclk / 1000000 - 1) << 8) | 		// CLKDIV = Fpclk / 1000000 - 1 ，即转换时钟为1MHz
          (0 << 16)                    |		// BURST = 0 ，软件控制转换操作
          (0 << 17)                    | 		// CLKS = 0 ，使用11clock转换
          (1 << 21)                    | 		// PDN = 1 ， 正常工作模式(非掉电转换模式)
          (0 << 22)                    | 		// TEST1:0 = 00 ，正常工作模式(非测试模式)
          (1 << 24)                    | 		// START = 1 ，直接启动ADC转换
          (0 << 27);							// EDGE = 0 (CAP/MAT引脚下降沿触发ADC转换)

}



//***********************************************************************
//** function:     % Read_AD
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
LONG Read_AD(BYTE channel)
{
    LONG ADC_Data;

    ADCR = (ADCR&0xFFFFFF00)|channel|(1 << 24);	// set AIN channel and start first read
    while( (ADDR&0x80000000)==0 );			    // wait for read end
    ADCR = ADCR | (1 << 24);					// start agin
    while( (ADDR&0x80000000)==0 );
    ADC_Data = ADDR;							// read AIN channel

    return(ADC_Data);
}












