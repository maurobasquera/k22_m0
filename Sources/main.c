/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM22-M1
**     Processor   : MK22FN512VLH12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-08, 15:45, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "MCUC1.h"
#include "KSDK1.h"
#include "timestamp.h"
#include "reset.h"
#include "red.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "green.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "timeout.h"
#include "RealTimeLdd2.h"
#include "blue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "delay.h"
#include "TU1.h"
#include "TU2.h"
#include "sleepModbus.h"
#include "indicationModbus.h"
#include "BitIoLdd4.h"
#include "enableModbus.h"
#include "BitIoLdd5.h"
#include "modbusSerial.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "main_header.h"
#include "modbusMaster.h"

unsigned int rs1 = 16;
unsigned int rs2 = 78;
unsigned int rs3 = 23;
unsigned int rs4 = 55;

unsigned int rr1 = 0;
unsigned int rr2 = 0;
unsigned int rr3 = 0;
unsigned int rr4 = 0;

unsigned char ID = 1;
unsigned char FC = 16;
unsigned int AD = 0;
unsigned int REG_NUM = 4;

unsigned int regs_send[4];
unsigned int regs_receive[4];

void blink_blue();
void poll_modbus();
void time_stamp();
void modbus_master(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM);

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/

	PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  modbus_configure();

for(;;) {

	time_stamp();
//	blink_blue();

	regs_send[0] = rs1;
	regs_send[1] = rs2;
	regs_send[2] = rs3;
	regs_send[3] = rs4;

	poll_modbus();
	modbus_master(ID,FC,AD,REG_NUM);

	rr1 = regs_receive[0];
	rr2 = regs_receive[1];
	rr3 = regs_receive[2];
	rr4 = regs_receive[3];

}

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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


