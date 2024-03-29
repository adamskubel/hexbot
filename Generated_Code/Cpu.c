/** ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Cpu.c
**     Project     : HexLEDTest
**     Processor   : MK22FN512VLH12
**     Component   : MK22FN512LH12
**     Version     : Component 01.048, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Datasheet   : K22P121M120SF7RM, Rev. 1, March 24, 2014
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-11, 23:35, # CodeGen: 66
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         SetOperationMode - LDD_TError Cpu_SetOperationMode(LDD_TDriverOperationMode OperationMode,...
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

/* {Default RTOS Adapter} No RTOS includes */
#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
** ===================================================================
**     Method      :  Common_Init (component MK22FN512LH12)
**     Description :
**         Initialization of registers for that there is no 
**         initialization component.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if CPU_COMMON_INIT
void Common_Init(void)
{
  /* Common initialization of registers which initialization is required 
     for proper functionality of components in the project but initialization
     component which would be configuring these registers is missing 
     in the project. 
     Add associated initialization component to the project to avoid 
     initialization of registers in the Common_Init().
     Also, after reset value optimization property affects initialization of 
     registers in this method (see active generator configuration 
     Optimizations\Utilize after reset values property or enabled processor 
     component Common settings\Utilize after reset values property) */
  /* Enable clock gate of peripherals initialized in Common_Init() */
  /* SIM_SCGC5: PORTC=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

  /* PORTC_PCR1: ISF=0,IRQC=0x0B,LK=0,DSE=0,ODE=0,PFE=0,SRE=0,PE=1,PS=1 */
  PORTC_PCR1 = (uint32_t)((PORTC_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x04) |
                PORT_PCR_LK_MASK |
                PORT_PCR_DSE_MASK |
                PORT_PCR_ODE_MASK |
                PORT_PCR_PFE_MASK |
                PORT_PCR_SRE_MASK
               )) | (uint32_t)(
                PORT_PCR_IRQC(0x0B) |
                PORT_PCR_PE_MASK |
                PORT_PCR_PS_MASK
               ));
  /* PORTC_PCR2: ISF=0,IRQC=0x0B,LK=0,DSE=0,ODE=1,PFE=0,SRE=0,PE=1,PS=1 */
  PORTC_PCR2 = (uint32_t)((PORTC_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x04) |
                PORT_PCR_LK_MASK |
                PORT_PCR_DSE_MASK |
                PORT_PCR_PFE_MASK |
                PORT_PCR_SRE_MASK
               )) | (uint32_t)(
                PORT_PCR_IRQC(0x0B) |
                PORT_PCR_ODE_MASK |
                PORT_PCR_PE_MASK |
                PORT_PCR_PS_MASK
               ));

  /* Disable clock gate of peripherals initialized in Common_Init() */
  /* SIM_SCGC5: PORTC=0 */
  SIM_SCGC5 &= (uint32_t)~(uint32_t)(SIM_SCGC5_PORTC_MASK);
}

#endif /* CPU_COMMON_INIT */

/*
** ===================================================================
**     Method      :  Components_Init (component MK22FN512LH12)
**     Description :
**         Initialization of components (with exception for Peripheral
**         Initialization Components which are initialized in 
**         Peripherals_Init() method).
**         For example, if automatic initialization feature 
**         is enabled in LDD component then its Init method call 
**         is executed in Components_Init() method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if CPU_COMPONENTS_INIT
void Components_Init(void)
{
  /* ### GPIO_LDD "BitsIoLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)BitsIoLdd1_Init(NULL);
  /* ### PWM_LDD "PwmLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)PwmLdd1_Init(NULL);
  /* ### PWM_LDD "PwmLdd2" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)PwmLdd2_Init(NULL);
  /* ### Asynchro serial "AS1" init code ... */
  AS1_Init();
  /* ### GPIO_LDD "BitsIoLdd2" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)BitsIoLdd2_Init(NULL);
  /* ### Asynchro serial "AS0" init code ... */
  AS0_Init();
  /* ### Asynchro serial "AS2" init code ... */
  AS2_Init();
  /* ### KinetisSDK "KSDK1" init code ... */
  /* Write code here ... */
  /* ### Asynchro serial "ASLP" init code ... */
  ASLP_Init();
  /* ### GPIO_LDD "BitsIoLdd3" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)BitsIoLdd3_Init(NULL);
  /* ### ExtInt_LDD "ExtIntLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)ExtIntLdd1_Init(NULL);
  /* ### TimerInt_LDD "TimerIntLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)TimerIntLdd1_Init(NULL);
  /* ### TimerInt "TI1" init code ... */
  /* ### RealTime_LDD "RealTimeLdd1" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)RealTimeLdd1_Init(NULL);
  /* ### ExtInt_LDD "ExtIntLdd2" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)ExtIntLdd2_Init(NULL);
  /* ### PWM_LDD "PwmLdd3" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)PwmLdd3_Init(NULL);
  /* ### PWM_LDD "PwmLdd4" component auto initialization. Auto initialization feature can be disabled by component property "Auto initialization". */
  (void)PwmLdd4_Init(NULL);
  /* ### SeggerRTT "RTT1" init code ... */
  RTT1_Init();
  /* ### CriticalSection "CS1" init code ... */
  /* ### Shell "CLS1" init code ... */
  CLS1_Init(); /* initialize shell */
}
#endif /* CPU_COMPONENTS_INIT */

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_PORTC (component MK22FN512LH12)
**
**     Description :
**         This ISR services the ivINT_PORTC interrupt shared by several 
**         components.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_PORTC)
{
    ExtIntLdd1_Interrupt();              /* Call the service routine */
    ExtIntLdd2_Interrupt();              /* Call the service routine */
}

/*
** ===================================================================
**     Method      :  Cpu_INT_NMIInterrupt (component MK22FN512LH12)
**
**     Description :
**         This ISR services the Non Maskable Interrupt interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_NMIInterrupt)
{
  Cpu_OnNMI();
}


#ifdef __cplusplus
}
#endif

/* END Cpu. */

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
