/* ###################################################################
**     Filename    : Events.c
**     Project     : FRDM22-M1
**     Processor   : MK22FN512VLH12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-13, 15:29, # CodeGen: 30
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         PWM1_OnEnd               - void PWM1_OnEnd(void);
**         modbusSerial_OnError     - void modbusSerial_OnError(void);
**         modbusSerial_OnRxChar    - void modbusSerial_OnRxChar(void);
**         modbusSerial_OnTxChar    - void modbusSerial_OnTxChar(void);
**         modbusSerial_OnFullRxBuf - void modbusSerial_OnFullRxBuf(void);
**         modbusSerial_OnFreeTxBuf - void modbusSerial_OnFreeTxBuf(void);
**         adc_OnEnd                - void adc_OnEnd(void);
**         adc_OnCalibrationEnd     - void adc_OnCalibrationEnd(void);
**         Cpu_OnNMI                - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  PWM1_OnEnd (module Events)
**
**     Component   :  PWM1 [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  modbusSerial_OnError (module Events)
**
**     Component   :  modbusSerial [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void modbusSerial_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  modbusSerial_OnRxChar (module Events)
**
**     Component   :  modbusSerial [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void modbusSerial_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  modbusSerial_OnTxChar (module Events)
**
**     Component   :  modbusSerial [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void modbusSerial_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  modbusSerial_OnFullRxBuf (module Events)
**
**     Component   :  modbusSerial [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void modbusSerial_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  modbusSerial_OnFreeTxBuf (module Events)
**
**     Component   :  modbusSerial [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void modbusSerial_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK22FN512LH12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PWM1_OnEnd (module Events)
**
**     Component   :  PWM1 [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/

void TI1_OnInterrupt(LDD_TUserData *UserDataPtr)
{
}

/*
** ===================================================================
**     Event       :  TU1_OnCounterRestart (module Events)
**
**     Component   :  TU1 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/


void TU1_OnCounterRestart(LDD_TUserData *UserDataPtr)
{

}

/*
** ===================================================================
**     Event       :  timestamp_OnCounterRestart (module Events)
**
**     Component   :  timestamp [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void timestamp_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	extern int count_1ms;
	extern int count_10ms;
	extern int count_100ms;
	extern int count_200ms;
	extern int count_500ms;
	extern int count_1s;

	count_1ms++;
	count_10ms++;
	count_100ms++;
	count_200ms++;
	count_500ms++;
	count_1s++;
}

/*
** ===================================================================
**     Event       :  reset_OnPortEvent (module Events)
**
**     Component   :  reset [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/

void reset_OnPortEvent(LDD_TUserData *UserDataPtr)
{
	extern unsigned int error_total;
	extern unsigned int transmission_Flag;

	red_Off();
	error_total = 0;
	transmission_Flag = 1;

}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
