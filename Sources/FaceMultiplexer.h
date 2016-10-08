/*
 * FaceMultiplexer.h
 *
 *  Created on: Sep 21, 2016
 *      Author: Adam
 */

#ifndef SOURCES_FACEMULTIPLEXER_H_
#define SOURCES_FACEMULTIPLEXER_H_

#include "PE_Types.h"
#include "PE_Error.h"

#include "AS1.h"
#include "AS2.h"
#include "AS0.h"
#include "ASLP.h"
#include "LPUartSwitch.h"
#include "Uart1Switch.h"


void connectFaces(byte face[4]);
void setUart0Pins(byte faceNum);

#endif /* SOURCES_FACEMULTIPLEXER_H_ */
