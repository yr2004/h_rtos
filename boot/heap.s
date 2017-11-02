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
;**//Filename:   @  Heap.s                                             
;**//            @
;**//Revision:   @  1.0
;**//            @
;**//Data:       @  2008.7.16
;**//            @
;**//Editor:     @  harrimanhao
;**//*******************************************************************************//
        AREA    Heap, DATA, NOINIT

        EXPORT bottom_of_heap

bottom_of_heap    SPACE   1

        END

