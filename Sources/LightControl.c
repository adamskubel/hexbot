/*
 * LightControl.c
 *
 *  Created on: Oct 5, 2016
 *      Author: Adam
 */
#include "LightControl.h"

byte ledVal = 0;

void blinky(int dir)
{
	if ((ledVal & 0x3F) == 0)
		ledVal = 1;

	Bits1_PutVal(ledVal);

	if (dir >= 0)
		ledVal = ledVal << 1;
	else
		ledVal = ledVal >> 1;
}

void setLightValue(byte value)
{
	Bits1_PutVal(0x3F & value);
}

void spinLight()
{
	for (int i=0;i<6;i++)
	{
		blinky(1);
		WAIT1_Waitms(300);
	}
}
