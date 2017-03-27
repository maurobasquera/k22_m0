/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : sleepModbus.c
**     Project     : FRDM22-M1
**     Processor   : MK22FN512VLH12
**     Component   : Wait
**     Version     : Component 01.069, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-27, 11:04, # CodeGen: 247
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : sleepModbus
**          SDK                                            : KSDK1
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Disabled
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void sleepModbus_Wait10Cycles(void);
**         Wait100Cycles  - void sleepModbus_Wait100Cycles(void);
**         WaitCycles     - void sleepModbus_WaitCycles(uint16_t cycles);
**         WaitLongCycles - void sleepModbus_WaitLongCycles(uint32_t cycles);
**         Waitms         - void sleepModbus_Waitms(uint16_t ms);
**         Waitus         - void sleepModbus_Waitus(uint16_t us);
**         Waitns         - void sleepModbus_Waitns(uint16_t ns);
**         WaitOSms       - void sleepModbus_WaitOSms(void);
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
** @file sleepModbus.c
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup sleepModbus_module sleepModbus module documentation
**  @{
*/         

/* MODULE sleepModbus. */

#include "sleepModbus.h"


/*
** ===================================================================
**     Method      :  sleepModbus_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__attribute__((naked, no_instrument_function)) void sleepModbus_Wait10Cycles(void)
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
**     Method      :  sleepModbus_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__attribute__((naked, no_instrument_function)) void sleepModbus_Wait100Cycles(void)
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
**     Method      :  sleepModbus_WaitCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (16bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void sleepModbus_WaitCycles(uint16_t cycles)
{
  /*lint -save -e522 function lacks side effect. */
  while(cycles > 100) {
    sleepModbus_Wait100Cycles();
    cycles -= 100;
  }
  while(cycles > 10) {
    sleepModbus_Wait10Cycles();
    cycles -= 10;
  }
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  sleepModbus_WaitLongCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void sleepModbus_WaitLongCycles(uint32_t cycles)
{
  /*lint -save -e522 function lacks side effect. */
  while(cycles>60000) {
    sleepModbus_WaitCycles(60000);
    cycles -= 60000;
  }
  sleepModbus_WaitCycles((uint16_t)cycles);
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  sleepModbus_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
void sleepModbus_Waitms(uint16_t ms)
{
  /*lint -save -e522 function lacks side effect. */
  uint32_t msCycles; /* cycles for 1 ms */

  /* static clock/speed configuration */
  msCycles = sleepModbus_NofCyclesMs(1, sleepModbus_INSTR_CLOCK_HZ);
  while(ms>0) {
    sleepModbus_WaitLongCycles(msCycles);
    ms--;
  }
  /*lint -restore */
}
/*
** ===================================================================
**     Method      :  sleepModbus_Waitus (component Wait)
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
**     Method      :  sleepModbus_Waitns (component Wait)
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
**     Method      :  sleepModbus_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if 0
void sleepModbus_WaitOSms(void)
{
  /* Method is implemented as macro in the header file */
}
#endif

/* END sleepModbus. */

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
