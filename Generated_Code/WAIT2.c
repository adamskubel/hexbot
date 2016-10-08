/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : WAIT2.c
**     Project     : HexLEDTest
**     Processor   : MK22FN512VLH12
**     Component   : Wait
**     Version     : Component 01.069, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-06, 15:59, # CodeGen: 63
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : WAIT2
**          SDK                                            : KSDK1
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Disabled
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void WAIT2_Wait10Cycles(void);
**         Wait100Cycles  - void WAIT2_Wait100Cycles(void);
**         WaitCycles     - void WAIT2_WaitCycles(uint16_t cycles);
**         WaitLongCycles - void WAIT2_WaitLongCycles(uint32_t cycles);
**         Waitms         - void WAIT2_Waitms(uint16_t ms);
**         Waitus         - void WAIT2_Waitus(uint16_t us);
**         Waitns         - void WAIT2_Waitns(uint16_t ns);
**         WaitOSms       - void WAIT2_WaitOSms(void);
**
**     License   : Open Source (LGPL)
**     Copyright : Erich Styger, 2013-2016, all rights reserved.
**     Web       : www.mcuoneclipse.com
**     This an open source software implementing waiting routines using Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file WAIT2.c
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup WAIT2_module WAIT2 module documentation
**  @{
*/         

/* MODULE WAIT2. */

#include "WAIT2.h"


/*
** ===================================================================
**     Method      :  WAIT2_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__attribute__((naked, no_instrument_function)) void WAIT2_Wait10Cycles(void)
{
  /* This function will wait 10 CPU cycles (including call overhead). */
  /*lint -save -e522 function lacks side effect. */
  /* NOTE: Cortex-M0 and M4 have 1 cycle for a NOP */
  /* Compiler is GNUC */
  __asm (
   /* bl Wai10Cycles() to here: [4] */
   "nop   \n\t" /* [1] */
   "nop   \n\t" /* [1] */
   "nop   \n\t" /* [1] */
   "bx lr \n\t" /* [3] */
  );
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  WAIT2_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__attribute__((naked, no_instrument_function)) void WAIT2_Wait100Cycles(void)
{
  /* This function will spend 100 CPU cycles (including call overhead). */
  /*lint -save -e522 function lacks side effect. */
  __asm (
   /* bl to here:               [4] */
   "push {r0}   \n\t"        /* [2] */
   "movs r0, #0 \n\t"        /* [1] */
   "loop:       \n\t"
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "add r0,#1   \n\t"        /* [1] */
   "cmp r0,#9   \n\t"        /* [1] */
   "bls loop    \n\t"        /* [3] taken, [1] not taken */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "pop {r0}    \n\t"        /* [2] */
   "bx lr       \n\t"        /* [3] */
  );
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  WAIT2_WaitCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (16bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT2_WaitCycles(uint16_t cycles)
{
  /*lint -save -e522 function lacks side effect. */
  while(cycles > 100) {
    WAIT2_Wait100Cycles();
    cycles -= 100;
  }
  while(cycles > 10) {
    WAIT2_Wait10Cycles();
    cycles -= 10;
  }
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  WAIT2_WaitLongCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT2_WaitLongCycles(uint32_t cycles)
{
  /*lint -save -e522 function lacks side effect. */
  while(cycles>60000) {
    WAIT2_WaitCycles(60000);
    cycles -= 60000;
  }
  WAIT2_WaitCycles((uint16_t)cycles);
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  WAIT2_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
void WAIT2_Waitms(uint16_t ms)
{
  /*lint -save -e522 function lacks side effect. */
  uint32_t msCycles; /* cycles for 1 ms */

  /* static clock/speed configuration */
  msCycles = WAIT2_NofCyclesMs(1, WAIT2_INSTR_CLOCK_HZ);
  while(ms>0) {
    WAIT2_WaitLongCycles(msCycles);
    ms--;
  }
  /*lint -restore */
}
/*
** ===================================================================
**     Method      :  WAIT2_Waitus (component Wait)
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT2_Waitns (component Wait)
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT2_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if 0
void WAIT2_WaitOSms(void)
{
  /* Method is implemented as macro in the header file */
}
#endif

/* END WAIT2. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
