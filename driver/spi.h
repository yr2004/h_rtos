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
/**��        ��: ��COS-II��LPC210x��SPI��ģʽ�ײ�����ͷ�ļ�
**              ʹ�÷������£�
**              SPIInit(xx);      //��ʼ��ʱ���ã�ֻ��һ��
**              ....
**              SPIStart();
**              ����ӻ�;
**              ���SPIRW(yy);
**              ��ֹ�ӻ�;
**              SPIEnd();   
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/


#define   HC595_CS       0x00000100             /* P0.8��Ϊ74HC595��Ƭѡ */
#define SPI_MOD   SPI_CPHA_ONE | SPI_CPOL_HIGH | SPI_LSBF_BIT7  /* SPIģʽ */

/* ϵͳ����, Fosc��Fcclk��Fcco��Fpclk���붨��*/
#define Fosc            11059200                    //����Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define Fcclk           (Fosc * 4)                  //ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1             //VPBʱ��Ƶ�ʣ�ֻ��Ϊ(Fcclk / 4)��1 ~ 4��



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

