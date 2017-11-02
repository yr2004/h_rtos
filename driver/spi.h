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
//Filename:   @  spi.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//
/**描        述: μCOS-II下LPC210x的SPI主模式底层驱动头文件
**              使用方法如下：
**              SPIInit(xx);      //初始化时调用，只能一次
**              ....
**              SPIStart();
**              允许从机;
**              多次SPIRW(yy);
**              禁止从机;
**              SPIEnd();   
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/


#define   HC595_CS       0x00000100             /* P0.8口为74HC595的片选 */
#define SPI_MOD   SPI_CPHA_ONE | SPI_CPOL_HIGH | SPI_LSBF_BIT7  /* SPI模式 */

/* 系统设置, Fosc、Fcclk、Fcco、Fpclk必须定义*/
#define Fosc            11059200                    //晶振频率,10MHz~25MHz，应当与实际一至
#define Fcclk           (Fosc * 4)                  //系统频率，必须为Fosc的整数倍(1~32)，且<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCO频率，必须为Fcclk的2、4、8、16倍，范围为156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1             //VPB时钟频率，只能为(Fcclk / 4)的1 ~ 4倍



#ifndef __SPI__
#define __SPI__

//***********************************************************************
//** function:     % SPI_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
extern void Spi_0_Init(BYTE Fdiv);


         
//***********************************************************************
//** function:     % SPI_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
extern BYTE Spi_0_ReadWrite(BYTE Data);


      
//***********************************************************************
//** function:     % SPI_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
extern void Spi_0_Exception(void);  






#endif

