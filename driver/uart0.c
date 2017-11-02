//*******************************************************************************//
//Filename:   @  rtc.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//
#include ".\boot\LPC2210.h"
#include ".\include\datatype.h"
#include ".\include\kernel.h"
#include ".\driver\spi.h"
#include ".\driver\I2C.h"
#include ".\driver\rtc.h"
#include ".\driver\uart0.h"

#define IN_UART0
//#include "config.h"

static BYTE UART0SendBuf[(UART0_SEND_QUEUE_LENGTH + sizeof(BYTE) - 1) / sizeof(BYTE)];

//static OS_EVENT *Uart0Sem;

/*********************************************************************************************************
** ��������: Uart0WriteFull
** ��������: ���ݶ���д��������� 
** �䡡��: Buf:ָ�����ݶ���
**        Data:��Ҫ��ӵ�����
**        Mod: ��ӷ�ʽ
** �䡡��:TRUE  :�ɹ�
**        FALSE:ʧ��
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
BYTE Uart0WriteFull(DataQueue *Buf, QUEUE_DATA_TYPE Data, BYTE Mod)
{
    WORD temp;
    
    Mod = Mod;
    
    temp = QueueSize((void *)Buf);
    while (temp <= QueueNData((void *)Buf))         /* �ȴ����ݶ��в��� */
    {
        //OSTimeDly(2);
    }
    return QueueWrite((void *)Buf, Data);           /* ����������� */
}

/*********************************************************************************************************
** ��������: UART0Init
** ��������: ��ʼ��UART0 
** �䡡��: bps��������
**
** �䡡��:TRUE  :�ɹ�
**        FALSE:ʧ��
** ȫ�ֱ���: Uart0Sem
** ����ģ��: QueueCreate,OSSemCreate
********************************************************************************************************/
BYTE UART0Init(UINT bps)
{
    WORD Fdiv;
    
    PINSEL0 = (PINSEL0 & 0xfffffff0) | 0x05;    /* ѡ��ܽ�ΪUART0 */

    U0LCR = 0x80;                               /* ������ʷ�Ƶ���ӼĴ��� */
    Fdiv = (Fpclk / 16) / bps;                  /* ���ò����� */
    U0DLM = Fdiv / 256;							
	U0DLL = Fdiv % 256;						
    U0LCR = 0x03;                               /* ��ֹ���ʷ�Ƶ���ӼĴ��� */
                                                /* ������Ϊ8,1,n */
	U0IER = 0x05;                               /* ������պͷ����ж� */
    U0FCR = 0x87;                               /* ��ʼ��FIFO */
    if (QueueCreate((void *)UART0SendBuf,
                     sizeof(UART0SendBuf),
                     NULL,
                     (BYTE (*)())Uart0WriteFull)
                     == NOT_OK)
    {
        return FALSE;
    }
   // Uart0Sem = OSSemCreate(0);
    if (Uart0Sem != NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

} 

/*********************************************************************************************************
** ��������: UART0Putch
** ��������: ����һ���ֽ�����
** �䡡��: Data�����͵���������
** �䡡��:��
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
void UART0Putch(BYTE Data)
{
    BYTE temp;
    
    QueueWrite((void *)UART0SendBuf, Data);         /* ������� */
    //OS_ENTER_CRITICAL();
    if ((U0LSR & 0x00000020) != 0)
    {                                               /* UART0���ͱ��ּĴ����� */
        QueueRead(&temp, UART0SendBuf);             /* ���������ӵ����� */
        U0THR = temp;
        U0IER = U0IER | 0x02;                       /* �������ж� */
    }
    //OS_EXIT_CRITICAL();
} 

/*********************************************************************************************************
** ��������: UART0Write
** ��������: ���Ͷ���ֽ�����
** �䡡��: Data:�������ݴ洢λ��
**        NByte:�������ݸ���
** �䡡��:��
** ȫ�ֱ���: ��
** ����ģ��: UART0Putch
********************************************************************************************************/
void UART0Write(BYTE *Data, WORD NByte)
{
    //OS_ENTER_CRITICAL();
    while (NByte-- > 0)
    {
        UART0Putch(*Data++);
    }
   // OS_EXIT_CRITICAL();
} 

/*********************************************************************************************************
** ��������: UART0Getch
** ��������: ����һ���ֽ�
** �䡡��: ��
** �䡡��: ���յ�������
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
BYTE UART0Getch(void)
{
    BYTE err;

    //OS_ENTER_CRITICAL();
    while ((U0LSR & 0x00000001) == 0)
    {                                           /* û���յ����� */
        U0IER = U0IER | 0x01;                   /* ��������ж� */
       // OSSemPend(Uart0Sem, 0, &err);           /* �ȴ��������� */
    }
    err = U0RBR;                                /* ��ȡ�յ������� */
    //OS_EXIT_CRITICAL();
    return err;
} 

/*********************************************************************************************************
** ��������: UART0_Exception
** ��������: UART0�жϷ������
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: QueueRead,OSSemPost
********************************************************************************************************/
void UART0_Exception(void)
{
    BYTE IIR, temp, i;
    
    //OS_ENTER_CRITICAL();

    while(((IIR = U0IIR) & 0x01) == 0)
    {                                                   /* ���ж�δ������ */
        switch (IIR & 0x0e)
        {
            case 0x02:                                  /* THRE�ж�    */
                for (i = 0; i < UART0_FIFO_LENGTH; i++) /* ����FIFO������� */
                {
                    if (QueueRead(&temp, UART0SendBuf) == QUEUE_OK)
                    {
                        U0THR = temp;
                    }
                    else
                    {
                        U0IER = U0IER & (~0x02);        /* ���пգ����ֹ�����ж� */
                    }
                }
                break;
            case 0x04:                                  /* �������ݿ��� */
                //OSSemPost(Uart0Sem);                    /* ֪ͨ�������� */
                U0IER = U0IER & (~0x01);                /* ��ֹ���ռ��ַ���ʱ�ж� */
                break;
            case 0x06:                                  /* ������״̬   */
                temp = U0LSR;
                break;
            case 0x0c:                                  /* �ַ���ʱָʾ */
               // OSSemPost(Uart0Sem);                    /* ֪ͨ�������� */
                U0IER = U0IER & (~0x01);                /* ��ֹ���ռ��ַ���ʱ�ж� */
                break;
            default :
                break;
        }
    } 
    VICVectAddr = 0;            // ֪ͨ�жϿ������жϽ���
   // OS_EXIT_CRITICAL();
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
