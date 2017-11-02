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
//Filename:   @  Target.c                                             
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



void IRQ_interrupt_00(void)
{
}


void IRQ_interrupt_01(void)
{
}


void IRQ_interrupt_02(void)
{
}


void IRQ_interrupt_03(void)
{
}


void IRQ_interrupt_04(void)
{
}


void IRQ_interrupt_05(void)
{
}



void IRQ_interrupt_06(void)
{
}


void IRQ_interrupt_07(void)
{
}


void IRQ_interrupt_08(void)
{
}


void IRQ_interrupt_09(void)
{
}


void IRQ_interrupt_0A(void)
{
}


void IRQ_interrupt_0B(void)
{
}


void IRQ_interrupt_0C(void)
{
}


void IRQ_interrupt_0D(void)
{
}


void IRQ_interrupt_0E(void)
{
}


void IRQ_interrupt_0F(void)
{
}










void FIQ_interrupt_00(void)
{
}



//-----------------------------------------------------------------------------;
// This is an indirect call table. input is the "priority" of the current      ;
// interrupt. Output is to call the current interrupt.                         ;
//                                                                             ;
// This table has to agree with the setting inside "InitializeInterrupts", which is  ;
// inside file named "InitARM.c"                                               ;
//-----------------------------------------------------------------------------;
/*void (* const func_isr_tbl[16])(void) = {
    IRQ_interrupt_00,          // priority 0
    IRQ_interrupt_01,          // priority 1
    IRQ_interrupt_02,          // priority 2    
    IRQ_interrupt_03,          // priority 3
    IRQ_interrupt_04,          // priority 4
    IRQ_interrupt_05,          // priority 5
    IRQ_interrupt_06,          // priority 6
    IRQ_interrupt_07,          // priority 7
    IRQ_interrupt_08,          // priority 8    
    IRQ_interrupt_09,          // priority 9
    IRQ_interrupt_0A,          // priority 10
    IRQ_interrupt_0B,          // priority 11
    IRQ_interrupt_0C,          // priority 12    
    IRQ_interrupt_0D,          // priority 13
    IRQ_interrupt_0E,          // priority 14
    IRQ_interrupt_0F,          // priority 15
   
};*/



//***********************************************************************
//** function:     % C_IRQ_Handler
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void C_IRQ_Handler(void)
{

    BYTE    temp;
    
    temp = VICVectAddr;
    //*temp;
    
    //temp = VICIRQStatus;
    //(*(func_isr_tbl[temp]))();
}



//***********************************************************************
//** function:     % C_FIQ_Handler
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void C_FIQ_Handler(void)
{

    FIQ_interrupt_00();

}



//***********************************************************************
//** function:     % init_SPI
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_SPI(void)  
{


}



//***********************************************************************
//** function:     % init_I2C
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_I2C(void)  
{


}



//***********************************************************************
//** function:     % init_UART
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_UART(void)  
{


}



//***********************************************************************
//** function:     % init_Time
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_Time(void)  
{


}



//***********************************************************************
//** function:     % init_Modem
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_Modem(void)  
{


}




//***********************************************************************
//** function:     % init_Interrupt
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void init_Interrupt(void)  
{


}




//***********************************************************************
//** function:     % User_System_Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void User_System_Init(void)
{


/* 设置系统各部分时钟 */
    PLLCON = 1;
#if (Fpclk / (Fcclk / 4)) == 1
    VPBDIV = 0;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
    VPBDIV = 2;
#endif
#if (Fpclk / (Fcclk / 4)) == 4
    VPBDIV = 1;
#endif

#if (Fcco / Fcclk) == 2
    PLLCFG = ((Fcclk / Fosc) - 1) | (0 << 5);
#endif
#if (Fcco / Fcclk) == 4
    PLLCFG = ((Fcclk / Fosc) - 1) | (1 << 5);
#endif
#if (Fcco / Fcclk) == 8
    PLLCFG = ((Fcclk / Fosc) - 1) | (2 << 5);
#endif
#if (Fcco / Fcclk) == 16
    PLLCFG = ((Fcclk / Fosc) - 1) | (3 << 5);
#endif
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
   // while((PLLSTAT & (1 << 10)) == 0);
    PLLCON = 3;
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    
    /* 设置存储器加速模块 */
    MAMCR = 0;
#if Fcclk < 20000000
    MAMTIM = 1;
#else
#if Fcclk < 40000000
    MAMTIM = 2;
#else
    MAMTIM = 3;
#endif
#endif
    MAMCR = 2;
    
    /* set lpc2210 pins fuction:
    PINSEL0 EINT1~EINT2 timer1 PWM4/PWM6 SPI0 I2C UART0
    PINSEL1 AIN0~AIN3 GPIO-P0.16~P0.25
     */    
  PINSEL0 = 0xAAAA5555;    
  PINSEL1 = 0x2A800000;    
    
/*    
    init_AD();    
    init_GPIO();    
    init_SPI();    
    init_I2C();    
    init_RTC();
    init_UART();
    init_Time();    
    init_Modem();    
    init_Interrupt();    
*/        
    
/* 设置实时时钟 */
    CCR = 1;
    PREINT = Fpclk / 32768 - 1;
    PREFRAC = Fpclk - (Fpclk / 32768) * 32768;
    YEAR = 2003;
    MONTH = 6;
    DOM = 2;   
    
     
    /* 初始化VIC */
    VICIntEnClr  = 0xFFFFFFFF;
    VICVectAddr  = 0x00000000;
    VICIntSelect = 0x00000000;
    VICIntEnable = 0x0000FFFF;
    VICIntSelect = 0;
    
    
    T0IR = 0xffffffff;
    T0TCR = 0X02;
    
        
    VICVectAddr0 = (int)IRQ_interrupt_00;
    VICVectAddr1 = (int)IRQ_interrupt_01;    
    VICVectAddr2 = (int)IRQ_interrupt_02;    
    VICVectAddr3 = (int)IRQ_interrupt_03;    
    VICVectAddr4 = (int)IRQ_interrupt_04;    
    VICVectAddr5 = (int)IRQ_interrupt_05;
    VICVectAddr6 = (int)IRQ_interrupt_06;    
    VICVectAddr7 = (int)IRQ_interrupt_07;    
    VICVectAddr8 = (int)IRQ_interrupt_08;    
    VICVectAddr9 = (int)IRQ_interrupt_09; 
    VICVectAddr10 = (int)IRQ_interrupt_0A;
    VICVectAddr11 = (int)IRQ_interrupt_0B;    
    VICVectAddr12 = (int)IRQ_interrupt_0C;    
    VICVectAddr13 = (int)IRQ_interrupt_0D;    
    VICVectAddr14 = (int)IRQ_interrupt_0E;     
    VICVectAddr15 = (int)IRQ_interrupt_0F;
    
    VICVectCntl0 = 0x00000020;
    VICVectCntl1 = 0x00000021;  
    VICVectCntl2 = 0x00000022;
    VICVectCntl3 = 0x00000023;
    VICVectCntl4 = 0x00000024;
    VICVectCntl5 = 0x00000025;   
    VICVectCntl6 = 0x00000026;
    VICVectCntl7 = 0x00000027;     
    VICVectCntl8 = 0x00000028;
    VICVectCntl9 = 0x00000029;    
    VICVectCntl10 = 0x0000002A;
    VICVectCntl11 = 0x0000002B; 
    VICVectCntl12 = 0x0000002C;
    VICVectCntl13 = 0x0000002D;    
    VICVectCntl14 = 0x0000002E;
    VICVectCntl15 = 0x0000002F;      
    
    
    

}





/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
