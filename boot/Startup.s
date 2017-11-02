;*
;*//**********************************************************************************
;*                                        H-OS
;*                                The Real-Time Kernel
;*                                   TASK MANAGEMENT
;*
;*                      (c) Copyright 2007-2077, Harriman Hao
;*                                 All Rights Reserved
;*
;**//*******************************************************************************//
;**//Filename:   @  Startup.s                                             
;**//            @
;**//Revision:   @  1.0
;**//            @
;**//Data:       @  2008.7.16
;**//            @
;**//Editor:     @  harrimanhao
;**//*******************************************************************************//


Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F ; available on ARM Arch 4 and later

I_Bit           EQU     0x80 ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40 ; when F bit is set, FIQ is disabled


; --- Amount of memory (in bytes) allocated for stacks

Len_FIQ_Stack   EQU     0   ; Uncomment this line when ENABLE_FIQ == 0
; Len_FIQ_Stack   EQU     128   ;Uncomment this line when ENABLE_FIQ == 1
Len_ABT_Stack   EQU     0
Len_UND_Stack   EQU     0
Len_SVC_Stack   EQU     0
Len_IRQ_Stack   EQU     256
Len_USR_Stack   EQU     64

; Add lengths >0 for FIQ_Stack, ABT_Stack, UND_Stack if you need them.
; Offsets will be loaded as immediate values.
; Offsets must be 8 byte aligned.

Offset_FIQ_Stack     EQU     0
Offset_ABT_Stack     EQU     Offset_FIQ_Stack + Len_FIQ_Stack
Offset_UND_Stack     EQU     Offset_ABT_Stack + Len_ABT_Stack
Offset_SVC_Stack     EQU     Offset_UND_Stack + Len_UND_Stack
Offset_IRQ_Stack     EQU     Offset_SVC_Stack + Len_SVC_Stack
Offset_USR_Stack     EQU     Offset_IRQ_Stack + Len_IRQ_Stack



PINSEL2     EQU 0xE002C014

BCFG0       EQU 0xFFE00000
BCFG1       EQU 0xFFE00004
BCFG2       EQU 0xFFE00008
BCFG3       EQU 0xFFE0000C

MEMMAP      EQU 0xE01FC040

;

    IMPORT  __main                          ;C语言主程序入口 
    IMPORT  User_System_Init                 ;目标板基本初始化
    IMPORT  top_of_stacks
    IMPORT  bottom_of_heap
    
    
;

    EXPORT ResetHandler
    EXPORT  __user_initial_stackheap
;/*******************************************************************************************
;** function:     % ENTRY
;**
;** Description:  %
;**
;** input:        %
;**
;** output:       %
;**
;** data:         %
;**
;** editor:       % harrimanhao
;**------------------------------------------------------------------------------------------
;********************************************************************************************/
    CODE32

    AREA    Startup,CODE,READONLY
        ENTRY

        LDR     pc, =Instruct_2

Instruct_2
;
        LDR     R0, =PINSEL2
    IF :DEF: EN_CRP
        LDR     R1, =0x0f814910
    ELSE
        LDR     R1, =0x0f814914
    ENDIF
        STR     R1, [R0]

        LDR     R0, =BCFG0
        LDR     R1, =0x1000ffef
        STR     R1, [R0]

        LDR     R0, =BCFG1
        LDR     R1, =0x1000ffef
        STR     R1, [R0]



;/*******************************************************************************************
;** function:     % ResetHandler
;**
;** Description:  %
;**
;** input:        %
;**
;** output:       %
;**
;** data:         %
;**
;** editor:       % harrimanhao
;**------------------------------------------------------------------------------------------
;********************************************************************************************/
ResetHandler

; --- Initialize stack pointer registers
; Enter each mode in turn and set up the stack pointer

;        IMPORT  top_of_stacks       ; defined in stack.s and located by scatter file
        LDR     r0, =top_of_stacks
        
        MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit ; no interrupts
        SUB     sp, r0, #Offset_FIQ_Stack

        MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit ; no interrupts
        SUB     sp, r0, #Offset_IRQ_Stack

; --- Now change to User mode and set up User mode stack, if needed
;       MSR     CPSR_c, #Mode_USR:OR:F_Bit ; enable IRQ interrupts
        MSR     CPSR_c, #Mode_USR          ; enable IRQ/FIQ interrupts
        SUB     sp, r0, #Offset_USR_Stack



        BL      User_System_Init         ;目标板基本初始化
                                          ;跳转到c语言入口
        B       __main
;/*******************************************************************************************
;** function:     % __user_initial_stackheap
;**
;** Description:  %
;**
;** input:        %
;**
;** output:       %
;**
;** data:         %
;**
;** editor:       % harrimanhao
;**------------------------------------------------------------------------------------------
;********************************************************************************************/
__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
    MOV   pc,lr
    
    
    
    END
