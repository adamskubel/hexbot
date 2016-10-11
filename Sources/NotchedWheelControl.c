/*
 * NotchedWheelControl.c
 *
 *  Created on: Oct 5, 2016
 *      Author: Adam
 */
#include "NotchedWheelControl.h"


#define STATE_WAITING 7
#define STATE_MOVING 8

#define STATE_FORWARD_SEARCH 1
#define STATE_REVERSE_SEARCH 2
#define STATE_SEARCH_COMPLETE 3
#define STATE_JOGGING 9

#define SEARCH_RATIO 0x7FFF
#define EXIT_SEARCH_TIME 1000
#define LOCAL_SEARCH_TIME 800

#define INIT_INVALID 0
#define INIT_POSITIVE 1
#define INIT_NEGATIVE -1

byte state = 0,notches = 0;
unsigned initState = 0;
int currentNotch = -1, rotatingDirection;


void rotate(int direction, int ratio);

void onNotch(){

	switch (state){
	case STATE_FORWARD_SEARCH:
		stopWheel();
		state = STATE_SEARCH_COMPLETE;
		initState = INIT_POSITIVE;
		currentNotch = 1;
		SEGGER_RTT_printf(0,"FWD_Notch: %d\n",currentNotch);
		break;
	case STATE_REVERSE_SEARCH:
		stopWheel();
		state = STATE_SEARCH_COMPLETE;
		initState = INIT_POSITIVE;
		currentNotch = 0;
		SEGGER_RTT_printf(0,"REV_Notch: %d\n",currentNotch);
		break;
	case STATE_MOVING:
		currentNotch = 1 - currentNotch;
		stopWheel();
		state = STATE_WAITING;
		SEGGER_RTT_printf(0,"Arrived at notch %d\n",currentNotch);
		SEGGER_RTT_printf(0,"SlotVal = %d\n", EInt2_GetVal());
		break;
	case STATE_JOGGING:
		stopWheel();
		state = STATE_WAITING;
		break;
	}

}

void errorBlink()
{
	for (int i = 0; i < 10; i++) {
		WAIT1_Waitms(200);
		setLightValue(0xFF);
		WAIT1_Waitms(200);
		setLightValue(0x00);
	}
}

/**
 * Algorithm to find a home point and motor polarity
 *
 * 1. Apply low current in CW direction, wait
 * 2. If notches were counted, keep going
 * 3. Stop if five notches received -> END
 * 4. Stop if no notches received for N seconds
 * 5. Rotate CCW until first notch -> END
 *
 */
void initializeWheel(bool reverse)
{
	//Local search first
	initState = INIT_INVALID;

	EInt2_SetEdge(EDGE_RISING);

	state = (reverse) ? STATE_REVERSE_SEARCH : STATE_FORWARD_SEARCH;
	rotate((reverse) ? -1 : 1, SEARCH_RATIO);
	WAIT1_Waitms(LOCAL_SEARCH_TIME);
	stopWheel();
	if (state != STATE_SEARCH_COMPLETE){
		state = (!reverse) ? STATE_REVERSE_SEARCH : STATE_FORWARD_SEARCH;
		rotate((!reverse) ? -1 : 1,SEARCH_RATIO);
		WAIT1_Waitms(LOCAL_SEARCH_TIME);
		stopWheel();
	}

	if (state == STATE_SEARCH_COMPLETE)
	{
		spinLight();
		SEGGER_RTT_printf(0,"Init_1");
		state = STATE_WAITING;
	}
	else if (EInt2_GetVal() == 0)
	{
		state = (reverse) ? STATE_REVERSE_SEARCH : STATE_FORWARD_SEARCH;
		rotate((reverse) ? -1 : 1, SEARCH_RATIO);
		WAIT1_Waitms(2000);
		stopWheel();

		if (state == STATE_SEARCH_COMPLETE)
		{
			spinLight();
			SEGGER_RTT_printf(0,"Init_2");
			state = STATE_WAITING;
		}
		else
		{
			state = STATE_WAITING;
			errorBlink();
			SEGGER_RTT_printf(0,"Init2_Fail: SlotVal = %d", EInt2_GetVal());
		}
	}
	else {
		state = STATE_WAITING;
		errorBlink();
		SEGGER_RTT_printf(0,"Init_Fail: SlotVal = %d", EInt2_GetVal());
	}

}

void jogWheel(int dir, int ratio){
	state = STATE_JOGGING;
	rotate(dir,ratio);
}

void moveToNotch(int targetNotch)
{
	if (initState != INIT_INVALID && state == STATE_WAITING && (targetNotch == 0 || targetNotch == 1))
	{
		if (targetNotch == currentNotch){
			stopWheel();
			return;
		}

		int dir = 0;
		if (currentNotch == 0)
			dir = (initState == INIT_POSITIVE) ? 1 : -1;
		else if (currentNotch == 1)
			dir = (initState == INIT_NEGATIVE) ? -1 : 1;

		state = STATE_MOVING;
		rotate(dir,SEARCH_RATIO);
	}
	else
	{
		SEGGER_RTT_printf(0,"Can't move not ready!");
	}
}

void stopWheel()
{
	rotate(0,0);
}

void rotate(int direction, int ratio)
{
	if (direction > 0)
	{
		rotatingDirection = 1;
		PWM4_SetRatio16(0);
		PWM3_SetRatio16(ratio);
	}
	else if (direction < 0)
	{
		rotatingDirection = -1;
		PWM4_SetRatio16(ratio);
		PWM3_SetRatio16(0);
	}
	else
	{
		rotatingDirection = 0;
		PWM3_SetRatio16(0);
		PWM4_SetRatio16(0);
	}
}










































