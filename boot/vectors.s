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
;**//Filename:   @  vectors.s                                             
;**//            @
;**//Revision:   @  1.0
;**//            @
;**//Data:       @  2008.7.16
;**//            @
;**//Editor:     @  harrimanhao
;**//*******************************************************************************//

        AREA Vect, CODE, READONLY

; *****************
; Exception Vectors
; *****************

; Note: LDR PC instructions are used here, though branch (B) instructions
; could also be used, unless the ROM is at an address >32MB.

        ENTRY
;----------------------------------------------------------------------------
;       Begin of ARM Vector Table
;----------------------------------------------------------------------------
        LDR     PC, Reset_Addr
        LDR     PC, Undefined_Addr
        LDR     PC, SWI_Addr
        LDR     PC, Prefetch_Addr
        LDR     PC, Abort_Addr
        NOP                             ; Reserved vector
        LDR     PC, IRQ_Addr
        LDR     PC, FIQ_Addr
;----------------------------------------------------------------------------
;       End of ARM Vector Table
;----------------------------------------------------------------------------

        IMPORT  ResetHandler           
        IMPORT  C_IRQ_Handler          
        IMPORT  C_FIQ_Handler          

Reset_Addr      DCD     ResetHandler
Undefined_Addr  DCD     Undefined_Handler
SWI_Addr        DCD     SWI_Handler
Prefetch_Addr   DCD     Prefetch_Handler
Abort_Addr      DCD     Abort_Handler
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler


; ************************
; Exception Handlers
; ************************

; exception handler for undefined instructions

Undefined_Handler
       B       Undefined_Handler

SWI_Handler
        B       SWI_Handler

Prefetch_Handler
       B       Prefetch_Handler
;		SUBS	PC,R14,#4

Abort_Handler
        B       Abort_Handler

IRQ_Handler
        SUB     lr, lr, #4          ; reserved for PC
        STMFD   sp!, {r0-r12, lr}
        BL      C_IRQ_Handler
        LDMFD   sp!, {r0-r12, pc}^  ; Get spsr from stack

FIQ_Handler
;        B       FIQ_Handler
        SUB     lr, lr, #4          ; reserved for PC
        STMFD   sp!, {r0-r7, lr}
        BL      C_FIQ_Handler
        LDMFD   sp!, {r0-r7, pc}^  ; Get spsr from stack


        END

