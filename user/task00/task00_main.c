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
//Filename:   @  task00_main.c                                             
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
#include ".\user\task00\task00_main.h"
#include ".\user\task01\task01_main.h"
#include ".\user\task02\task02_main.h"

Fuction_State_T SCB_Execute_State;

//***********************************************************************
//** function:     % Task00_SCB01  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB01[]=
{
    {task00_SCB01_seq01  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_001, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
    //{task00_SCB01_seq02  ,{MS_10   ,0x0000    ,0x0000   }, { SEQ_003, SEQ_001, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_002 */
    //{task00_SCB01_seq03  ,{0x0000  ,0x0000    ,0x0000   }, { SEQ_004, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_003 */
    //{task00_SCB01_seq04  ,{MS_10   ,0x0000    ,0x0000   }, { SEQ_001, SEQ_001, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_004 */     
};     

//***********************************************************************
//** function:     % Task00_SCB02  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB02[]=
{
    {task00_SCB02_seq01  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
	//{task00_SCB01_seq02  ,{MS_10	,0x0000    ,0x0000	 }, { SEQ_003, SEQ_001, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_002 */
	//{task00_SCB01_seq03  ,{0x0000	,0x0000    ,0x0000	 }, { SEQ_004, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_003 */
	//{task00_SCB01_seq04  ,{MS_10	,0x0000    ,0x0000	 }, { SEQ_001, SEQ_001, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_004 */	 
}; 

//***********************************************************************
//** function:     % Task00_SCB03  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB03[]=
{
    {task00_SCB03_seq01  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
	//{task00_SCB01_seq02  ,{MS_10	,0x0000    ,0x0000	 }, { SEQ_003, SEQ_001, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_002 */
	//{task00_SCB01_seq03  ,{0x0000	,0x0000    ,0x0000	 }, { SEQ_004, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_003 */
	//{task00_SCB01_seq04  ,{MS_10	,0x0000    ,0x0000	 }, { SEQ_001, SEQ_001, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_004 */	 
}; 

//***********************************************************************
//** function:     % Task00_SCB01_err  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB01_Err[]=
{
    {task00_SCB01_seq01_err  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
}; 

//***********************************************************************
//** function:     % Task00_SCB02_err  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB02_Err[]=
{
    {task00_SCB02_seq01_err  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
}; 

//***********************************************************************
//** function:     % Task00_SCB03_err  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB03_Err[]=
{
    {task00_SCB03_seq01_err  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
}; 

//***********************************************************************
//** function:     % Task00_SCB01_other  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB01_Other[]=
{
    {task00_SCB01_seq01_other  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
}; 

//***********************************************************************
//** function:     % Task00_SCB02_other  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB02_Other[]=
{
    {task00_SCB02_seq01_other  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
}; 

//***********************************************************************
//** function:     % Task00_SCB03_other  task SCB control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
SUB_SCB_TBL Task00_SCB03_Other[]=
{
    {task00_SCB03_seq01_other  ,{MS_1    ,0x0000    ,0x0000   }, { SEQ_002, SEQ_END, SEQ_ILL, SEQ_ILL, SEQ_ILL }},  /* SEQ_001 */
};  

//***********************************************************************
//** function:     % SCB_Tbl  status control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//*********************************************************************** 
const SCB_TBL SCB_Manage_Tbl[3][Max_SCB_Num]=
{
/* normal */
   { {SCB_002,(SUB_SCB_TBL *) Task00_SCB01           },      /*SCB_001*//*  System Initial */
     {SCB_003,(SUB_SCB_TBL *) Task00_SCB02           },      /*SCB_002*//*  */
     {SCB_004,(SUB_SCB_TBL *) Task00_SCB03           },      /*SCB_003*//*  */
   },  
     
/* error */     
   { {SCB_002,(SUB_SCB_TBL *) Task00_SCB01_Err       },      /*SCB_001*//*  */
     {SCB_003,(SUB_SCB_TBL *) Task00_SCB02_Err       },      /*SCB_002*//*  */
     {SCB_004,(SUB_SCB_TBL *) Task00_SCB03_Err       },      /*SCB_003*//*  */
   },       

/* other states */      
   { {SCB_002,(SUB_SCB_TBL *) Task00_SCB01_Other     },      /*SCB_001*//*  */
     {SCB_003,(SUB_SCB_TBL *) Task00_SCB01_Other     },      /*SCB_002*//*  */
     {SCB_004,(SUB_SCB_TBL *) Task00_SCB01_Other     },      /*SCB_003*//*  */
   },  
         
};     

//***********************************************************************
//** function:     % Task_Cmd_Decode()
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//*********************************************************************** 
void task_cmd_decode(void)
{
    BYTE  cmd;
    cmd = OS_Get_TaskInterface(Command);
    if(cmd == Task_Cmd_idle)
    {
      
    }
      
    if(cmd == Task_Cmd_00)
    {
            
    }  
}

//***********************************************************************
//** function:     % SCB_StateMachine   status control block
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************      
void SCB_table_state_machine(void)   
{
    UINT  i;
    UINT  j;
    
    i = SCB_Execute_State.SCB_state;
    j = SCB_Execute_State.SCB_numb;
            
    if( SCB_Execute_State.seq_numb != SEQ_END)
    {        
        sub_SCB_execute((SCB_Manage_Tbl[i][j].tbl + SCB_Execute_State.seq_numb));
      
    }
    else
    {
        SCB_Execute_State.seq_numb = 0x0000;
        SCB_Execute_State.SCB_numb = SCB_Manage_Tbl[i][j].next_SCB_no;
        i = SCB_Execute_State.SCB_state;
        j = SCB_Execute_State.SCB_numb;      

        sub_SCB_execute((SCB_Manage_Tbl[i][j].tbl + SCB_Execute_State.seq_numb));     
    }  
}

//***********************************************************************
//** function:     % sub_SCB_execute    Seq execute
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void sub_SCB_execute(SUB_SCB_TBL  *p)
{
    UINT  result;

    result = p->func();            /* Call Function taskXX_SCBXX_seqXX() */
    
    if(result != SEQ_ERR)
    {
    	SCB_Execute_State.seq_numb = p->next_sub_SCB_no[result];
    }
    
    if(result == SEQ_ERR)
    {
        SCB_Execute_State.seq_numb  = SEQ_001;
        SCB_Execute_State.SCB_state = SCB_STA_002;
    }    
}

//***********************************************************************
//** function:     % task00_main
//** Description:  %
//** input:        %
//** output:       %
//** data:         %
//** editor:       % harrimanhao
//***********************************************************************
void task00_main(void)
{
    SCB_Execute_State.SCB_state  = SCB_STA_001;
    SCB_Execute_State.SCB_numb   = SCB_001;
    SCB_Execute_State.seq_numb   = SEQ_001;
          
    OS_EnableInterrupt();           
    for(;;)
    {
        task_cmd_decode();
        for(;;)
        {
            SCB_table_state_machine();
        }      
    }      
}




