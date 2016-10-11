/*
 * SpeedControl.h
 *
 *  Created on: Sep 23, 2016
 *      Author: Adam
 */


#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWM2.h"
#include "PwmLdd2.h"
#include "FC321.h"
#include "stdlib.h"

#ifndef SOURCES_SPEEDCONTROL_H_
#define SOURCES_SPEEDCONTROL_H_

void updateSpeedControl();
void countSpeed();
void setSpinSpeed(float targetSpeed);

#endif /* SOURCES_SPEEDCONTROL_H_ */
