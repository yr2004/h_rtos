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
//Filename:   @  i2c.c                                             
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
#include ".\driver\I2C.h"


/* ����ΪI2C����ʱ����Ҫ�ı��� */
volatile  BYTE  I2C_sla;           // �ӻ���ַ(��������ַ)
volatile  BYTE  I2C_suba;          // �ӵ�ַ
volatile  BYTE  *I2C_buf;          // ���ݻ�����ָ�� (������ʱ�ᱻ����)
volatile  BYTE  I2C_num;           // �������ݸ��� (�ᱻ����)
volatile  BYTE  I2C_end;           // ����������־��Ϊ1ʱ��ʾ����������Ϊ0xFFʱ��ʾ����ʧ�� (�ᱻ����)
volatile  BYTE  I2C_suba_en;       // �ӵ�ַʹ�ܿ��ƣ�������ʱ������Ϊ1��д����ʱ������Ϊ2 (�ᱻ����)


//***********************************************************************
//** function:     % I2c_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void  I2c_Exception(void)
{  BYTE  sta;

   sta = I2STAT;                    // ����I2C״̬��
   switch(sta)
   {  case  0x08:                   // ��������ʼ����
            if(1==I2C_suba_en) 
            {
               I2DAT = I2C_sla&0xFE;    // ָ���ӵ�ַ��ʱ����д���ַ
            }
            else 
            {
               I2DAT = I2C_sla;                     // ����ֱ�ӷ��ʹӻ���ַ
               I2CONCLR = 0x28;        // SI=0
            }
            break;
            
      case  0x10:
            I2DAT = I2C_sla;        // ���������ߺ󣬷��ʹӵ�ַ
            I2CONCLR = 0x28;        // SI=0
            break;
   
      case  0x18:                   // �ѷ���SLA+W�����ѽ���Ӧ��
            if(0==I2C_suba_en)      // ���ӵ�ַ����ֱ�ӷ�������
            {  if(I2C_num>0)
               {  
                  I2DAT = *I2C_buf++;
                  I2CONCLR = 0x28; 
                  I2C_num--;
               }
               else
               {  
                  I2CONSET = 0x10;  // �����ݷ��ͣ���������
                  I2CONCLR = 0x28;
                  I2C_end = 1;      // �������߲���������־
               }
               break;
            }
            if(1==I2C_suba_en)      // �����ӵ�ַ
            { 
               I2DAT = I2C_suba;
               I2CONCLR = 0x28;
            }
            if(2==I2C_suba_en)
            { 
               I2DAT = I2C_suba;
               I2CONCLR = 0x28;
               I2C_suba_en = 0;     // �ӵ�ַ������
            }
            break;
            
      case  0x28:                   // �ѷ���I2C���ݣ������յ�Ӧ��
            if(0==I2C_suba_en)      // ���ӵ�ַ����ֱ�ӷ�������
            {  if(I2C_num>0)
               {  
                  I2DAT = *I2C_buf++;
                  I2CONCLR = 0x28; 
                  I2C_num--;
               }
               else
               {  
                  I2CONSET = 0x10;  // �����ݷ��ͣ���������
                  I2CONCLR = 0x28;
                  I2C_end = 1; 
               }
               break;
            }
            if(1==I2C_suba_en)      // ����ָ����ַ������������������
            { 
               I2CONSET = 0x20;
               I2CONCLR = 0x08;
               I2C_suba_en = 0;     // �ӵ�ַ������
            }
            break;
   
   
      case  0x20:
      case  0x30:
      case  0x38:
            I2CONCLR = 0x28;        // ���߽��벻��Ѱַ��ģʽ
            I2C_end = 0xFF;         // ���߳���,���ñ�־
            break;
   
   
      case  0x40:                   // ������SLA+R�����ѽ��յ�Ӧ��
            if(1==I2C_num)          // ���һ�ֽڣ��������ݺ��ͷ�Ӧ���ź�
            {  
               I2CONCLR = 0x2C;     // AA=0�����յ����ݺ������Ӧ��
            }
            else                    // �������ݲ�����Ӧ���ź�
            {  
               I2CONSET = 0x04;     // AA=1�����յ����ݺ����Ӧ��
               I2CONCLR = 0x28;
            }
            break;
            
      case  0x50:
            *I2C_buf++ = I2DAT;     // ��ȡ����
            I2C_num--;
            if(1==I2C_num)
            {
               I2CONCLR = 0x2C;     // AA=0�����յ����ݺ������Ӧ��
            }
            else
            {  
               I2CONSET = 0x04;     // AA=1�����յ����ݺ����Ӧ��
               I2CONCLR = 0x28;
            }
            break;
      
      case  0x58:
            *I2C_buf++ = I2DAT;     // ��ȡ���һ�ֽ�����
            I2CONSET = 0x10;        // ��������
            I2CONCLR = 0x28;
            I2C_end = 1; 
            break;
      
      case  0x48:
            I2CONCLR = 0x28;        // ���߽��벻��Ѱַ��ģʽ
            I2C_end = 0xFF; 
            break;
            
      default: 
            break;
   }
   

   VICVectAddr = 0x00;              // �жϴ������
}



//***********************************************************************
//** function:     % I2c_SendByte
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
BYTE  I2c_SendByte(BYTE Address, BYTE Data)
{  /* �������� */
   I2C_sla = Address;		// д������������ַ
   I2C_buf = &Data;		// �����͵�����
   I2C_num = 1;			// ����1�ֽ�����
   I2C_suba_en = 0;		// ���ӵ�ַ
   I2C_end = 0;
   
   I2CONCLR = 0x2C;
   I2CONSET = 0x60;             // ����Ϊ����������������
   
   while(0==I2C_end);
   
   if(1==I2C_end) 
      return(1);
   else
      return(0);
}



//***********************************************************************
//** function:     % I2c_SendStr
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
BYTE  I2c_SendStr(BYTE Address, BYTE SubAddress, BYTE *Buffer, BYTE Num)
{  /* �������� */
   I2C_sla = Address;		// д������������ַ
   I2C_suba = SubAddress;		// �ӵ�ַ
   I2C_buf = Buffer;			
   I2C_num = Num;	
   I2C_suba_en = 2;		// ���ӵ�ַд
   I2C_end = 0;
   
   I2CONCLR = 0x2C;
   I2CONSET = 0x60;             // ����Ϊ����������������
   
   while(0==I2C_end);
   
   if(1==I2C_end) 
      return(1);
   else 
      return(0);
}



//***********************************************************************
//** function:     % I2c_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
BYTE  I2c_RcvByte(BYTE Address, BYTE *Data)
{  /* �������� */
   I2C_sla = Address+1;		// ��������������ַ
   I2C_buf = Data;
   I2C_num = 1;
   I2C_suba_en = 0;		// ���ӵ�ַ
   I2C_end = 0;
   
   I2CONCLR = 0x2C;
   I2CONSET = 0x60;             // ����Ϊ����������������
   
   while(0==I2C_end);
   
   if(1==I2C_end)
      return(1);
   else 
      return(0);
}



//***********************************************************************
//** function:     % I2c_Exception
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
BYTE  I2c_RcvStr(BYTE Address, BYTE SubAddress, BYTE *Buffer, BYTE Num)
{ 
   if(0==Num) 
      return(0);
   
   /* �������� */
   I2C_sla = Address+1;		// ��������������ַ
   I2C_suba = SubAddress;		
   I2C_buf = Buffer;
   I2C_num = Num;
   I2C_suba_en = 1;		// ���ӵ�ַ��
   I2C_end = 0;
   
   I2CONCLR = 0x2C;
   I2CONSET = 0x60;             // ����Ϊ����������������
   
   while(0==I2C_end);
   
   if(1==I2C_end) 
      return(1);
   else 
      return(0);
}

