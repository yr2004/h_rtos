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
//Filename:   @  datatype.h                                             
//            @
//Revision:   @  1.0
//            @
//Data:       @  2008.7.16
//            @
//Editor:     @  harrimanhao
//*******************************************************************************//
#ifndef __Datatype__
#define __Datatype__

typedef unsigned int    bool;
typedef unsigned char   BOOL;           /* 1 BYTE  0x00 ~ 0xFF                      */
typedef unsigned char   BYTE;           /* 1 BYTE  0x00 ~ 0xFF                      */
typedef signed char     SBYTE;          /* 1 BYTE  -128 ~ +127                      */
typedef unsigned short  USHORT;         /* 2 bytes 0x0000 ~ 0xFFFF                  */
typedef unsigned short  WORD;           /* 2 bytes 0x0000 ~ 0xFFFF                  */
typedef signed short    SHORT;          /* 2 bytes -32768(0x8000) ~ +32767(0x7FFF)  */
typedef unsigned int    UINT;           /* 4 bytes 0x0000 ~ 0xFFFFFFFF              */
typedef signed int      INT;            /* 4 bytes unsigned int                      */
typedef unsigned long   ULONG;          /* 4 bytes 0x00000000 ~ 0xFFFFFFFF          */
typedef signed long     LONG;           /* 4 bytes -2147483648(0x80000000) ~ +2147483647(0x7FFFFFFF) */

/* volatile signed and unsigned definition */    /* ARM compiler define                      */
typedef volatile unsigned char  vBOOL;           /* 1 BYTE  0x00 ~ 0xFF                      */
typedef volatile unsigned char  FLAG;
typedef volatile unsigned char  vBYTE;           /* 1 BYTE  0x00 ~ 0xFF                      */
typedef volatile signed char    vSBYTE;          /* 1 BYTE  -128 ~ +127                      */
typedef volatile unsigned short vUSHORT;         /* 2 bytes 0x0000 ~ 0xFFFF                  */
typedef volatile signed short   vSHORT;          /* 2 bytes -32768(0x8000) ~ +32767(0x7FFF)  */
typedef volatile unsigned int   vUINT;           /* 4 bytes 0x0000 ~ 0xFFFFFFFF              */
typedef volatile signed int     vINT;            /* 4 bytes unsigned int                     */
typedef volatile unsigned long  vULONG;          /* 4 bytes 0x00000000 ~ 0xFFFFFFFF          */
typedef volatile signed long    vLONG;           /* 4 bytes -2147483648(0x80000000) ~ +2147483647(0x7FFFFFFF) */

typedef signed char     *   LPCHAR;
typedef signed short    *   LPSHORT;
typedef signed long     *   LPLONG;
typedef unsigned char   *   LPBYTE;
typedef unsigned short  *   LPWORD;
typedef unsigned long   *   LPDWORD;
typedef void            *   LPVOID;

#define CONST       const

/* BOOLEAN expressions */
#define FALSE   0
#define TRUE    1

#endif 