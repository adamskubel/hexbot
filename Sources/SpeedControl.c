/*
 * SpeedControl.c
 *
 *  Created on: Sep 23, 2016
 *      Author: Adam
 */

#include "SpeedControl.h"



const unsigned WheelCounts = 8;

unsigned lastDelay = 0;
float instSpeed = 0;
float errorInt = 0;
float targetSpeed = 0;//Hz
float avgSpeed = 0;
bool canCount = FALSE;

void stopSpin();
void reset();

void countSpeed()
{
	if (!canCount)
	{
		canCount = TRUE;
		FC321_Reset();
		return;
	}
//	uint16_t time;
//	FC321_GetTimeUS(&time);

//	if (lastTime < time)
//	{
	uint16_t delay; // = (uint16_t)(time - lastTime);
	FC321_GetTimeMS(&delay);

	lastDelay = delay;
	FC321_Reset();
//	}

//	lastTime = time;
}


void updateSpeedControl()
{
	if (abs(targetSpeed) < 0.1f) {
		stopSpin();
		return;
	}

	if (lastDelay > 0 && lastDelay < 1000) {
		instSpeed = (1000.0f / (float) lastDelay);
	} else {
		instSpeed = 0;
	}

	float error = (targetSpeed - instSpeed);
	avgSpeed = avgSpeed * 0.5f + instSpeed*0.5f;
	errorInt += error;

	if (errorInt > 100.0f) errorInt = 100.0f;
	else if (errorInt < 0) errorInt = 0;

	errorInt = errorInt * 0.99f;

	float ratio = (error * 0.3f) + (errorInt * 0.02f);

	if (ratio < 0) ratio = 0;
	if (ratio > 1.0f) ratio = 1.0f;

	PWM1_SetRatio16((uint16_t)((float)0xFFFF * ratio));

}

void setSpinSpeed(float newSpeed)
{
	targetSpeed = newSpeed*(float)WheelCounts;
	if (abs(targetSpeed) < 0.1f) {
		stopSpin();
		EInt1_Disable();
	} else {
		EInt1_Enable();
	}
	reset();
}

float getAvgSpeed(){
	return avgSpeed/((float)WheelCounts);
}

float getInstSpeed() {
	return instSpeed/((float)WheelCounts);
}

void reset()
{
	canCount = 0;
	avgSpeed = 0;
	instSpeed = 0;
	lastDelay = 0;
	errorInt = 0;
}

void stopSpin()
{
	PWM1_SetRatio16(0);
	PWM2_SetRatio16(0);
}
