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
   ADCR = (1 << 0)                     |		// SEL = 1 ��ѡ��ͨ��0
          ((Fpclk / 1000000 - 1) << 8) | 		// CLKDIV = Fpclk / 1000000 - 1 ����ת��ʱ��Ϊ1MHz
          (0 << 16)                    |		// BURST = 0 ���������ת������
          (0 << 17)                    | 		// CLKS = 0 ��ʹ��11clockת��
          (1 << 21)                    | 		// PDN = 1 �� ��������ģʽ(�ǵ���ת��ģʽ)
          (0 << 22)                    | 		// TEST1:0 = 00 ����������ģʽ(�ǲ���ģʽ)
          (1 << 24)                    | 		// START = 1 ��ֱ������ADCת��
          (0 << 27);							// EDGE = 0 (CAP/MAT�����½��ش���ADCת��)

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












