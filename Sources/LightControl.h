/*
 * LightControl.h
 *
 *  Created on: Oct 5, 2016
 *      Author: Adam
 */

#ifndef SOURCES_LIGHTCONTROL_H_
#define SOURCES_LIGHTCONTROL_H_


#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "Bits1.h"
#include "BitsIoLdd1.h"
#include "WAIT1.h"
#include "LightCodes.h"

void blinky(int dir);
void setLightValue(byte value);
void spinLight();
void errorBlink();


#endif /* SOURCES_LIGHTCONTROL_H_ */
