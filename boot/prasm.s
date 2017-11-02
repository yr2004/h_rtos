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
;**//Filename:   @  prasm.s                                             
;**//            @
;**//Revision:   @  1.0
;**//            @
;**//Data:       @  2008.7.16
;**//            @
;**//Editor:     @  harrimanhao
;**//*******************************************************************************//

        AREA prcon, CODE, READONLY
        ENTRY

        EXPORT OS_Save_CPU_Register
        EXPORT OS_Restore_CPU_Register
        EXPORT Save_SP_register
        EXPORT Restore_SP_register
        IMPORT regi
        IMPORT Process_No
        IMPORT dwOrgStack
        IMPORT dwPrnStack
;//*******************************************************************************
;//** function:     % Save_SP_register
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
Save_SP_register
        CODE16
        PUSH {r0}
        PUSH {r1}
        PUSH {r2}
        LDR  r0,=dwOrgStack
        MOV  r1, SP
        STR  r1, [r0, #0]
        LDR  r0,=dwPrnStack
        LDR  r2, [r0, #0]
        MOV  SP, r2
        LDR  r0, [r1, #12]
        STR  r0, [r2, #0]
        LDR  r0, [r1, #16]
        STR  r0, [r2, #4]
        LDR  r0, [r1, #20]
        STR  r0, [r2, #8]
        LDR  r0, [r1, #24]
        STR  r0, [r2, #12]
        LDR  r0, [r1, #28]
        STR  r0, [r2, #16]
        LDR  r0, [r1, #32]
        STR  r0, [r2, #20]
        LDR  r0, [r1, #36]
        STR  r0, [r2, #24]
        MOV  PC, LR



;//*******************************************************************************
;//** function:     % Save_SP_register
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
Restore_SP_register
        CODE16
        LDR  r0,=dwOrgStack
        LDR  r1, [r0, #0]
        MOV  SP, r1
        POP  {r2}
        POP  {r1}
        POP  {r0}
        MOV  PC, LR



;//*******************************************************************************
;//** function:     % Save_SP_register
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
OS_Save_CPU_Register
        CODE16                          ; Subsequent instructions are Thumb
        PUSH {r1}                       ;
        PUSH {r0}                       ;                                 (Push "orginal r1" and "orginal r0" into stack)
        ADR  r0,Save_CPU_ARM            ; Processor starts -> ARM
        BX   r0                         ; ARM Change

        CODE32
        
        
        
;//*******************************************************************************
;//** function:     % Save_CPU_ARM
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
Save_CPU_ARM                            ; Subsequent instructions are ARM
        LDR  r1,=Process_No             ; r0 = &fRegi[Process_No][0]
        LDRB r1,[r1,#0]
        LDR  r0,=regi
        ADD  r0,r0,r1,LSL #6            ;                                 ( 2^6 = 64, eRegiMax = 16 = 64 bytes)
                                        ;                                 ( make "r0" points to regi[Process_No][0])

        LDMFD SP!,{r1}                  ; r0[0] = regi0;                  ( pop the "orginal r0" to "r1")
        STR  r1,[r0]                    ;                                 ( put the "orginal r0" to regi[Process_No][0] )

        ADD  r0,r0,#4                   ; r0[1] = r1...r13                ( make "r0" points to regi[Process_No][1] )
        LDMFD SP!,{r1}                  ; r0[0] = regi0;                  ( pop the "orginal r1" to "r1" )
;
;       STMIA r0,{r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14}        ;( put "orginal r1-14" to regi[Process_No][1-14] )
        STMIA r0,{r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13}

        ADR  r0,Save_CPU_Thumb + 1      ; Processor starts -> Thumb       ( Load the address and set the least significant bit )

        BX   r0                         ; Thumb Change



;//*******************************************************************************
;//** function:     % Save_CPU_Thumb
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
Save_CPU_Thumb
        CODE16                          ; Subsequent instructions are Thumb
        MOV PC,LR                       ;                                 ( ret )



;//*******************************************************************************
;//** function:     % OS_Restore_CPU_Register
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
OS_Restore_CPU_Register
        CODE16                          ; Subsequent instructions are Thumb
        ADR  r0,Restore_CPU_ARM         ; Processor starts -> ARM         ( Load the address and "clear" the least significant bit )
        BX   r0                         ; ARM Change

        CODE32
        
        
        
;//*******************************************************************************
;//** function:     % Restore_CPU_ARM
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
Restore_CPU_ARM                         ; Subsequent instructions are ARM
        LDR  r1,=Process_No             ; r0 = &fRegi[Process_No][0]
        LDRB r1,[r1,#0]
        LDR  r0,=regi
        ADD  r0,r0,r1,LSL #6            ;                                 ( 2^6 = 64, eRegiMax = 16 = 64 bytes)
                                        ; r0...r13 = r[0]                 ( make "r0" points to regi[Process_No][0])
;
;       LDMIA r0,{r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14}     ;( get "orginal r0-14" from regi[Process_No][0-14] )
        LDMIA r0,{r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13}

;
;       STMFD SP!,{LR}                  ; PUSH LR
        STMFD SP!,{r0}                  ; PUSH r0
        ADR  r0,Restore_CPU_Thumb + 1   ; Processor starts -> Thumb
        BX   r0                         ; Thumb Change



;//*******************************************************************************
;//** function:     % Restore_CPU_Thumb
;//**
;//** Description:  %
;//**
;//** input:        %
;//**
;//** output:       %
;//**
;//** data:         %
;//**
;//** editor:       % harrimanhao
;//**
;//*******************************************************************************
Restore_CPU_Thumb
        CODE16                          ; Subsequent instructions are Thumb

        POP {r0}
;
;       POP {PC}
        MOV PC,LR                       ;                                 ( LR is r14 )


        END
