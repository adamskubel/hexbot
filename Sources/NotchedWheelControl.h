/*
 * NotchedWheelControl.h
 *
 *  Created on: Oct 5, 2016
 *      Author: Adam
 */

#ifndef SOURCES_NOTCHEDWHEELCONTROL_H_
#define SOURCES_NOTCHEDWHEELCONTROL_H_

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PWM3.h"
#include "PWM4.h"
#include "WAIT1.h"
#include "LightControl.h"
#include "EInt2.h"
#include "SEGGER_RTT.h"

void onNotch();
void initializeWheel(bool direction);
void jogWheel(int direction, int ratio);
void stopWheel();
void moveToNotch(int notchIndex);



#endif /* SOURCES_NOTCHEDWHEELCONTROL_H_ */
