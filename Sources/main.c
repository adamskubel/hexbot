/* ###################################################################
 **     Filename    : main.c
 **     Project     : HexLEDTest
 **     Processor   : MK22FN512VLH12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-09-19, 21:58, # CodeGen: 0
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
#include "Bits1.h"
#include "BitsIoLdd1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWM2.h"
#include "PwmLdd2.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "Uart1Switch.h"
#include "BitsIoLdd2.h"
#include "AS0.h"
#include "ASerialLdd2.h"
#include "AS2.h"
#include "ASerialLdd3.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "ASLP.h"
#include "ASerialLdd4.h"
#include "LPUartSwitch.h"
#include "BitsIoLdd3.h"
#include "EInt1.h"
#include "ExtIntLdd1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU2.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "EInt2.h"
#include "ExtIntLdd2.h"
#include "PWM3.h"
#include "PwmLdd3.h"
#include "TU4.h"
#include "PWM4.h"
#include "PwmLdd4.h"
#include "RTT1.h"
#include "WAIT2.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "TU3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "stdlib.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "SerialCommunicator.h"
#include "NotchedWheelControl.h"
#include "SpeedControl.h"
#include "LightControl.h"

int getHundreds(float val){
	return (int)((val - ((float)((int)val)))*100.0f);
}

int getIntArg(int defaultValue){

	char * end;
	char * arg = strtok(NULL," ");
	if (arg == NULL)
		return defaultValue;
	return strtol(arg,&end,10);
}

float getFloatArg()
{
	char * end;
	char * arg = strtok(NULL," ");
	return strtof(arg,&end);
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */

	PWM1_SetRatio16(0);
	PWM2_SetRatio16(0);
	PWM3_SetRatio16(0);
	PWM4_SetRatio16(0);
	WAIT1_Waitms(2000);


	const char * SetLightCommand = "setLight";
	const char * SpinCommand = "spin";
	const char * NotchCommand = "moveNotch";
	const char * HaltCommand = "halt";
	const char * InvalidArguments = "ArgFail\0";
	const char * InvalidCommand = "InvalidCommand\0";
	const char * WheelRotateCommand = "jog\0";
	const char * WheelInitCommand = "InitWheel\0";
	const char * WheelMoveCommand = "MoveWheel\0";




	char data[64];
	unsigned dataSize = 64;

	for (;;) {
		SEGGER_RTT_WaitKey();
		unsigned read = SEGGER_RTT_Read(0,data,dataSize);
		char * token;
		char * end;

		char * d2;
		d2 = malloc(sizeof(char)*(read+1));
		strncpy(d2,data,read);

//		SEGGER_RTT_printf(0,"Rcv: '%s'\n",d2);

		token = strtok(d2," ");
		if (token == NULL)
			continue;

		if (strcmp(token,SetLightCommand) == 0)
		{
			char * arg = strtok(NULL," ");
			if (arg != NULL)
				setLightValue((byte)strtol(arg, &end,2));
			else
				SEGGER_RTT_printf(0,InvalidArguments);
		}
		else if (strcmp(token,"cw") == 0)
		{
			jogWheel(-1, 0x7FFF);
			WAIT1_Waitms(1000);
			stopWheel();
		}
		else if (strcmp(token,"ccw") == 0)
		{
			jogWheel(1, 0x7FFF);
			WAIT1_Waitms(1000);
			stopWheel();
		}
		else if (strcmp(token,"brake") == 0)
		{
			setSpinSpeed(0);
			unsigned overshoot = (unsigned)getIntArg(0);
			setOvershoot(overshoot);
			jogWheel(-1, 0xFFFF);
			setLightValue(HEXLIGHT_BRAKE_START);
			WAIT1_Waitms(3000);
			setOvershoot(0);
			stopWheel();
		}
		else if (strcmp(token,"recover") == 0)
		{
			jogWheel(1, 0xFFFF);
			WAIT1_Waitms(3000);
			stopWheel();
		}
		else if (strcmp(token,SpinCommand) == 0)
		{
			char * arg = strtok(NULL," ");
			SEGGER_RTT_printf(0,"Arg='%s'",arg);
			float speed = strtof(arg, &end);
			setSpinSpeed(speed);
			SEGGER_RTT_printf(0,"SpinSpeed %d/100 hz\n",(int)(100*speed));
		}
		else if (strcmp(token,NotchCommand) == 0)
		{
			char * arg = strtok(NULL," ");
			int notch = ((int)strtol(arg, &end,10));
			moveToNotch(notch);
		}
		else if (strcmp(token,HaltCommand) == 0)
		{
			stopWheel();
			setSpinSpeed(0);
		}
		else if (strcmp(token,WheelRotateCommand) == 0){
			char * dirArg = strtok(NULL," ");
			char * ratioArg = strtok(NULL," ");
			char * timeArg = strtok(NULL," ");
			if (dirArg == NULL || ratioArg == NULL || timeArg == NULL)
				SEGGER_RTT_printf(0,InvalidArguments);
			else
			{
				jogWheel(strtol(dirArg,&end,10),strtof(ratioArg,&end)*(float)0x7FFF);
				long wait = strtol(timeArg,&end,10);
				if (wait < 0) wait = 0;
				if (wait > 20000) wait = 20000;
				WAIT1_Waitms(wait);
				stopWheel();
			}
		}
		else if (strcmp(token, WheelInitCommand) == 0){
			char * dirArg = strtok(NULL," ");
			if (dirArg == NULL)
				SEGGER_RTT_printf(0,InvalidArguments);
			else {
				initializeWheel(strtol(dirArg,&end,10));
			}
		}
		else if (strcmp(token, WheelMoveCommand) == 0){
			char * notchArg = strtok(NULL," ");
			if (notchArg == NULL)
				SEGGER_RTT_printf(0,InvalidArguments);
			else {
				moveToNotch(strtol(notchArg,&end,10));
			}
		}
		else if (strcmp(token,"test") == 0){
			char * delayArg = strtok(NULL," ");
			char * speedArg = strtok(NULL," ");
			char * overshootArg = strtok(NULL," ");

			unsigned delay = 10000;
			unsigned overshoot = 0;
			float spinSpeed = 5;
			if (delayArg != NULL)
				delay = strtol(delayArg,&end,10);
			if (speedArg != NULL)
				spinSpeed = strtof(speedArg,&end);
			if (overshootArg != NULL)
				overshoot = strtol(overshootArg,&end,10);

			for (int s=0;s<64;s++){
				WAIT1_Waitms(delay/64);
				setLightValue((byte)s);
			}

			errorBlink();


			bool ready = FALSE;
			setSpinSpeed(spinSpeed);
			for (int s=0;s<10;s++){
				WAIT1_Waitms(2000);
				if (abs(getAvgSpeed() - spinSpeed) < 0.5f || getAvgSpeed() > spinSpeed)
				{
					ready = TRUE;
					break;
				}
			}
			int peakSpeed = (int)getAvgSpeed();
			int peakInstSpeed = (int)getInstSpeed();

			setSpinSpeed(0);

			//Brake
			setOvershoot(overshoot);
			jogWheel(1,0xFFFF);
			WAIT1_Waitms(3000);
			setOvershoot(0);
			stopWheel();

			//Recover wheel
			WAIT1_Waitms(500);
			jogWheel(-1,0xFFFF);
			WAIT1_Waitms(3000);
			stopWheel();

			if (ready){
				spinLight();
				setLightValue(HEXLIGHT_TEST_COMPLETE);
			}
			else
			{
				SEGGER_RTT_printf(0,"Peak avg speed was %d",peakSpeed);
				SEGGER_RTT_printf(0,"Peak inst speed was %d",peakInstSpeed);
				errorBlink();
				setLightValue(HEXLIGHT_TOO_SLOW);
			}
		}
		else if (strcmp(token,"getSpeed") == 0){
			SEGGER_RTT_printf(0,"AvgSpeed = %d.%d\n",(int)getAvgSpeed(), getHundreds(getAvgSpeed()));
			SEGGER_RTT_printf(0,"InstSpeed = %d.%d\n",(int)(getInstSpeed()),getHundreds(getInstSpeed()));
		}
		else if (strcmp(token,"sleep") == 0){
			Cpu_SetOperationMode(DOM_SLEEP,NULL,NULL);
		}
		else {
			SEGGER_RTT_printf(0,"%s",InvalidCommand);
		}

		free(d2);

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
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
