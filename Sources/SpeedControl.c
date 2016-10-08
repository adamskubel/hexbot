/*
 * SpeedControl.c
 *
 *  Created on: Sep 23, 2016
 *      Author: Adam
 */

#include "SpeedControl.h"



uint16_t lastTime=0;
float speed = 0;

void countSpeed()
{
	uint16_t time;
	FC321_GetTimeMS(&time);

	int delay = (int)(time - lastTime);

	speed = (1000.0f/(float)delay); //hz
	lastTime = time;
}

float ratio = 0;
float errorInt = 0;
float targetSpeed = 0;//Hz

void updateSpeedControl()
{
	if (abs(targetSpeed) < 0.1f) {
		stopSpin();
		return;
	}

	float error = (targetSpeed - speed);

	errorInt += error;

	if (errorInt > 100.0f) errorInt = 100.0f;
	else if (errorInt < -100.0f) errorInt = -100.0f;

	errorInt = errorInt * 0.99f;

	ratio += (error * 0.3f) + (errorInt * 0.04f);

	if (ratio < 0) ratio = 0;
	if (ratio > 1.0f) ratio = 1.0f;

	PWM1_SetRatio16((uint16_t)((float)0x7FFF * ratio));

}

void setSpinSpeed(float speed)
{
	targetSpeed = speed;
	errorInt = 0;

	if (abs(targetSpeed) < 0.1f) {
		stopSpin();
	}
}

void stopSpin()
{
	PWM1_SetRatio16(0);
	PWM2_SetRatio16(0);
}
