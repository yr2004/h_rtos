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
//Filename:   @  main.c                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//

#define IN_MODEM
#include "config.h"
static OS_EVENT *ModemSem, *Uart1Send, *Uart1Get;
static uint8 ModemState;

//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************

void UART1Init(uint32 bps)
{
    uint16 Fdiv;
    
    PINSEL0 = (PINSEL0 & 0x0000ffff) | 0x55550000;  /* ѡ��ܽ�ΪUART0 */

    U1LCR = 0x80;                                   /* ������ʷ�Ƶ���ӼĴ��� */
    Fdiv = (Fpclk / 16) / bps;                      /* ���ò����� */
    U1DLM = Fdiv / 256;							
	U1DLL = Fdiv % 256;						
    U1LCR = 0x03;                                   /* ��ֹ���ʷ�Ƶ���ӼĴ��� */
                                                    /* ������Ϊ8,1,n */
	U1IER = 0x0f;                                   /* ������պͷ����ж� */
    U1FCR = 0x87;                                   /* ��ʼ��FIFO */
    U1MCR = 0x03;
    Uart1Send = OSSemCreate(1);
    Uart1Get = OSSemCreate(0);

}

//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 GetModemState(void)
{
    return ModemState;
} 

//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 ModemWrite(char *Data, uint16 NByte)
{
    uint8 err,i;
    
    OSSemPend(ModemSem, 0, &err);
    while (NByte > 0)
    {
        OSSemPend(Uart1Send, 0, &err);
        for (i = 0; i < 8; i++)
        {
            U1THR = *Data++;
            NByte--;
            if (NByte == 0)
            {
                break;
            }
        }
    }
    OSSemPost(ModemSem);
    return ModemState;
} 

//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 ModemGetch(void)
{
    uint8 rt;

    OS_ENTER_CRITICAL();
    while ((U1LSR & 0x00000001) == 0)
    {                                           /* û���յ����� */
        U1IER = U1IER | 0x01;                   /* ��������ж� */
        OSSemPend(Uart1Get, 0, &rt);
    }
    rt = U1RBR;                                 /* ��ȡ�յ������� */
    OS_EXIT_CRITICAL();

    return rt;
} 
//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 ModemDialUp(char Number[])
{
    char *cp;
    uint8 i;
    uint8 err;
    
    if (ModemState == MODEM_CLOSE)
    {
        while ((U1LSR & 0x00000001) != 0)
        {
            err = U1RBR;
        }
        ModemWrite("ATD", 3);
        i = 0;
        cp = Number;
        while (*cp++ != 0)
        {
            i++;
        }
        ModemWrite(Number, i);
        ModemWrite("\r\n", 2);

        U1IER = U1IER | 0x01;                   /* ��������ж� */
        for (i = 0; i < 120; i++)
        {
            OSTimeDly(OS_TICKS_PER_SEC);
            if (ModemState == MODEM_CONNECT)
            {
                break;
            }
        }
    }
    return ModemState;
}
//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 ModemDialDown(void)
{
    U1MCR = 0x02;
    OSTimeDly(OS_TICKS_PER_SEC / 10);
    U1MCR = 0x03;
    OSTimeDly(OS_TICKS_PER_SEC / 10);
    return ModemState;
}

//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 ModemCommand(char *Command)
{
    char *cp;
    uint8 i,err;
    
    if (ModemState == MODEM_CLOSE)
    {
        while ((U1LSR & 0x00000001) != 0)
        {
            err = U1RBR;
        }
        
        cp = Command;
        i = 0;
        while(*cp++ != 0)
        {
            i++;
        }
        ModemWrite(Command, i);
        ModemWrite("\r\n", 2);
        i = ModemGetch();
        if (i == 'A' || i == 'a')
        {
            while (1)
            {
                err = i;
                i = ModemGetch();
                if (err == 'O' || err == 'o')
                if (i == 'K' || i == 'k')
                {
                    i = ModemGetch();
                    i = ModemGetch();
                    break;
                }
            }
        }
        else
        {
            while (1)
            {
                if (i == '0')
                {
                    break;
                }
                i = ModemGetch();
                i = ModemGetch();
            }
        }
    }
    return ModemState;
}
//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
uint8 ModemInit(uint32 bps)
{
    ModemState = MODEM_CLOSE;
    UART1Init(bps);
    ModemSem = OSSemCreate(1);
    if (ModemSem != NULL)
    {
        if ((U1MSR & 0x30) != 0x30)
        {
            OSTimeDly(OS_TICKS_PER_SEC);
            if ((U1MSR & 0x30) != 0x30)
            {
                ModemState = NOT_FIND_MODEM;
            }
        }
        if (ModemState == MODEM_CLOSE)
        {
            ModemCommand("ATE0");
            ModemCommand("ATV0");
            ModemCommand("AT&C1");
            ModemCommand("AT&D2");
            ModemCommand("AT&R0");
            ModemCommand("AT&S0");
            ModemCommand("ATS0=2");
        }
    }
    else
    {
        ModemState = NOT_INIT_MODEM;
    }
    return ModemState;
}

//***********************************************************************
//** function:     % UART1Init
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void UART1_Exception(void)
{
    uint8 IIR, temp;
    
    OS_ENTER_CRITICAL();
    while(((IIR = U1IIR) & 0x01) == 0)
    {                                                   /* ���ж�δ������ */
        switch (IIR & 0x0e)
        {
            case 0x00:                                  /* Modem״̬�仯 �ж�    */
                if ((U1MSR & 0x80) != 0)
                {
                    ModemState = MODEM_CONNECT;
                }
                else
                {
                    ModemState = MODEM_CLOSE;
                }
                if ((U1MSR & 0x40) != 0)
                {
                    ModemState = MODEM_RING;
                }
                if ((U1MSR & 0x30) != 0x30)
                {
                    ModemState = NOT_FIND_MODEM;
                }
                break;
            case 0x02:                                  /* THRE�ж�    */
                OSSemPost(Uart1Send);
                break;
            case 0x04:                                  /* �������ݿ��� */
                OSSemPost(Uart1Get);
                U1IER &= (~0x01);                       /* ��ֹ���ռ��ַ���ʱ�ж� */
                break;
            case 0x06:                                  /* ������״̬   */
                temp = U1LSR;
                break;
            case 0x0c:                                  /* �ַ���ʱָʾ */
                OSSemPost(Uart1Get);
                U1IER &= (~0x01);                       /* ��ֹ���ռ��ַ���ʱ�ж� */
                break;
            default :
                break;
        }
    } 
    VICVectAddr = 0;            // ֪ͨ�жϿ������жϽ���
    OS_EXIT_CRITICAL();
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
