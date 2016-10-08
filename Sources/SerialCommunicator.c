/*
 * SerialCommunicator.c
 *
 *  Created on: Oct 5, 2016
 *      Author: Adam
 */


#include "SerialCommunicator.h"

void faceTest()
{
	byte * s[6];

	s[0] = (byte*) "Sissi #0 is cute!";
	s[1] = (byte*) "Sissi #1 is cute!";
	s[2] = (byte*) "Sissi #2 is cute!";
	s[3] = (byte*) "Sissi #3 is cute!";
	s[4] = (byte*) "Sissi #4 is cute!";
	s[5] = (byte*) "Sissi #5 is cute!";

	Uart1Switch_PutVal(0x00);
	LPUartSwitch_PutVal(0x00);

	uint32_t uart0Face = 0;
	byte uart0[] = { 0, 2, 3};


	int i = 0;
	for (;;) {

		uart0Face = (uart0Face + 1) % 3;
		setUart0Pins(uart0[uart0Face]);

		for (i = 0; i < 14; i++) {
			ASLP_SendChar(s[4][i]);
//			AS2_SendChar(s[5][i]);
			AS0_SendChar(s[uart0[uart0Face]][i]);
//			AS1_SendChar(s[1][i]);
		}

		WAIT1_Waitms(300);
	}
}
