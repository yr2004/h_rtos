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
//Filename:   @  spi.c                                             
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
#include ".\driver\spi.h"



//***********************************************************************
//** function:     % Spi_0_Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void Spi_0_Init(BYTE Fdiv)
{
    PINSEL0 = (PINSEL0 & 0xffff00ff) | 0x5500;  

    S0PCCR = Fdiv & 0xfe;                    
    
    S0PCR = (0<<3)|                         //CPHA=0                    
            (1<<4)|                         //CPOL=1  
            (1<<5)|                         //MSTR=1  
            (0<<6)|                         //LSBF=0  
            (0<<7);                         //SPIE=0                   
}



//***********************************************************************
//** function:     % Spi_0_ReadWrite
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
BYTE Spi_0_ReadWrite(BYTE Data)
{
     S0PDR = Data;
     
     while( 0==(S0PSR&0x80) );		// 等待SPIF置位，即等待数据发送完毕
   
     return(S0PDR);

}



//***********************************************************************
//** function:     % SPI_0_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void Spi_0_Exception(void)
{
    BYTE temp, temp1;
    
    OS_DisableInterrupt();
    temp = S0PSR;
    if ((temp & 0x80) != 0)
    {
        temp1 = S0PDR;
    }
    
    if ((temp & 0x10) != 0)
    {
        S0PCR = (0<<3)|                         //CPHA=0                    
                (1<<4)|                         //CPOL=1  
                (1<<5)|                         //MSTR=1  
                (0<<6)|                         //LSBF=0  
                (0<<7);                         //SPIE=0  
    }
    S0PINT = 0x01;    
    VICVectAddr = 0;            
    OS_EnableInterrupt();
}






