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
//Filename:   @  task01_main.h                                             
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
#include ".\include\OS_task.h"
#include ".\user\main.h"
#include ".\driver\spi.h"

#ifndef __Task01main__
#define __Task01main__

/*************************************************************************/
/*                         Typedef                                       */
/*************************************************************************/
/* Base */
typedef struct {
    BYTE  len;      /* Length           */
    BYTE  cmdres;   /* Command/Response */
    BYTE  data[6];  /* data             */
} tMsg;

/* Command */
typedef struct {
    BYTE  len;      /* Length   */
    BYTE  cmd;      /* Command  */
    BYTE  msgid;    /* MsgId    */
    BYTE  reserved; /* Reserved */
} tMsg_Cmd;

/* Response */
typedef struct {
    BYTE  len;      /* Length   */
    BYTE  res;      /* Response */
    BYTE  result;   /* Result   */
    BYTE  data[5];  /* Data     */
} tMsg_Res;

/* Messgae */
typedef struct {
    BYTE  Size;                   /* Size          */
    BYTE  WrPtr;                  /* Write Pointer */
    BYTE  RdPtr;                  /* Read  Pointer */
    BOOL  NonSpace;               /* Non Space     */
    BYTE  Data[sizeof(tMsg) * 3]; /* Message Data  */
} tMsgBox;

/* Task Table */
typedef struct {
    BYTE (*ready)(void); /* Ready Task */
    BYTE (*erorr)(void); /* Error Task */
} tTask;

/* Cmd Table */
typedef struct {
    LPCHAR logmsg;       /* Log Msg  */
    BYTE   (*cmd)(void); /* Cmd Task */
    const  tTask  *task; /*     Task */
} tCmd;

#if (SERVICE_MODE==1)
/* Task Infomation */
typedef struct {
    BYTE cmdReq;      /* 04:Command Request */
    BYTE cmd;         /* 05:Command         */
    BYTE phase;       /* 06:Phase           */
    BYTE state;       /* 07:State           */
    BYTE msgId;       /* 08:Message ID      */
    tMsgBox msgBox;   /* 09:Msg Box         */
} tTaskInfo;
#endif

void task01_main(void);

#endif






