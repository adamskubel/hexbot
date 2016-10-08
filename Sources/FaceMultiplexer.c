/* * FaceMultiplexer.c
 *
 *  Created on: Sep 21, 2016
 *      Author: Adam
 */

#include "FaceMultiplexer.h"
#include "Cpu.h"


#define NONE 0x00
#define UART0 0x01
#define UART1 0x02
#define UART2 0x03
#define LPUART 0x04
#define UART1_TO_FACE1 0x00
#define UART1_TO_FACE0 0x03
//
//byte * faceConfig[6];
//
//faceConfig[0] = (byte*){UART0,UART1};
//faceConfig[1] = (byte*){UART1,NONE};
//faceConfig[2] = (byte*){UART0,NONE};
//faceConfig[3] = (byte*){UART0,LPUART};
//faceConfig[4] = (byte*){LPUART,NONE};
//faceConfig[5] = (byte*){UART2,NONE};
//
//struct Mapping
//{
//	byte face;
//	byte uartId;
//};


int select(byte index, byte * faces, byte result[4]);
void assignUart(byte uartId,byte faceNum);

//void connectFaces(byte connectedFaces[4])
//{
//	byte uartList[4];
//
//	select(0,connectedFaces,uartList);
//
//	for (int i=0;i<4;i++)
//	{
//		if (uartList[i] > 0)
//			assignUart(uartList[i],connectedFaces[i]);
//		else
//			break;
//	}
//
//}

//int select(byte index, byte * faces, byte result[4])
//{
//	int optUart=-1, optScore=0;
//	for (int i=0;i<2;i++)
//	{
//		byte uartId = faceConfig[faces[index]][i];
//		bool found = 0;
//		for (int r=0;r<4;r++)
//		{
//			if (result[r] == uartId){
//				found = 1;
//				break;
//			}
//		}
//
//		if (found)
//			continue;
//
//		byte nextResult[4];
//		for (int r=0;r<index;r++)
//		{
//			nextResult[r] = result[r];
//		}
//		nextResult[index] = uartId;
//
//		int score = select(index+1,faces,nextResult);
//
//		if (score > optScore)
//		{
//			optScore = score;
//			optUart = uartId;
//		}
//	}
//	result[index] = optUart;
//
//	if (optUart > 0)
//		return optScore;
//	else
//		return 0;
//}

void setUart0Pins(byte faceNum)
{
	byte pta1,pta2,ptb16,ptb17,ptd6,ptd7;

	switch (faceNum){
	case 0:
		ptd6 = ptd7 = 0x03;
		pta1 = pta2 = 0x01;
		ptb16 = ptb17 = 0x01;
		break;
	case 2:
		ptd6 = ptd7 = 0x01;
		pta1 = pta2 = 0x02;
		ptb16 = ptb17 = 0x01;
		break;
	case 3:
		ptd6 = ptd7 = 0x01;
		pta1 = pta2 = 0x01;
		ptb16 = ptb17 = 0x03;
		break;
	default:
		return;
	}



	//Set pins 22-23 (PTA1-2) to ALT1
	  /* PORTB_PCR16: ISF=0,MUX=3 */
	  PORTA_PCR1 = (uint32_t)((PORTA_PCR1 & (uint32_t)~(uint32_t)(
					 PORT_PCR_ISF_MASK |
					 PORT_PCR_MUX(0x07-pta1)
					)) | (uint32_t)(
					 PORT_PCR_MUX(pta1)
					));
	  /* PORTB_PCR17: ISF=0,MUX=3 */
	  PORTA_PCR2 = (uint32_t)((PORTA_PCR2 & (uint32_t)~(uint32_t)(
					 PORT_PCR_ISF_MASK |
					 PORT_PCR_MUX(0x07-pta2)
					)) | (uint32_t)(
					 PORT_PCR_MUX(pta2)
					));



	//Set pins 39-40 (PTB16-17) to ALT1
	  /* PORTB_PCR16: ISF=0,MUX=3 */
	  PORTB_PCR16 = (uint32_t)((PORTB_PCR16 & (uint32_t)~(uint32_t)(
					 PORT_PCR_ISF_MASK |
					 PORT_PCR_MUX(0x07-ptb16)
					)) | (uint32_t)(
					 PORT_PCR_MUX(ptb16)
					));
	  /* PORTB_PCR17: ISF=0,MUX=3 */
	  PORTB_PCR17 = (uint32_t)((PORTB_PCR17 & (uint32_t)~(uint32_t)(
					 PORT_PCR_ISF_MASK |
					 PORT_PCR_MUX(0x07-ptb17)
					)) | (uint32_t)(
					 PORT_PCR_MUX(ptb17)
					));

	//set Pin63/PTD6 to ALT3
	//set Pin64/PTD7 to ALT3

	PORTD_PCR6 = (uint32_t)((PORTD_PCR6 & (uint32_t)~(uint32_t)(
					PORT_PCR_ISF_MASK |
					PORT_PCR_MUX(0x07-ptd6)
				   )) | (uint32_t)(
					PORT_PCR_MUX(ptd6)
				   ));

	PORTD_PCR7 = (uint32_t)((PORTD_PCR7 & (uint32_t)~(uint32_t)(
					PORT_PCR_ISF_MASK |
					PORT_PCR_MUX(0x07-ptd7)
				   )) | (uint32_t)(
					PORT_PCR_MUX(ptd7)
				   ));


}



void assignUart(byte uartId, byte faceNum)
{
	switch (uartId)	{
	case UART0:
		switch (faceNum){
		case 0:
			Uart1Switch_PutVal(UART1_TO_FACE1);
			setUart0Pins(0);
			break;
		case 2:

			break;
		case 3:
			break;
		}
		break;
	case UART1:
		switch (faceNum){
		case 0:
			//set Pin63/PTD6 to ALT1 and float
			//set Pin64/PTD7 to ALT1 and float
			Uart1Switch_PutVal(UART1_TO_FACE0);
			break;
		case 1:
			Uart1Switch_PutVal(UART1_TO_FACE1);
			break;
		}
		break;
	case UART2:
		break;
	case LPUART:
		switch (faceNum){
		case 3:
			LPUartSwitch_PutVal(0x03);
			break;
		case 4:
			LPUartSwitch_PutVal(0x00);
			break;
		}
		break;

	}
}











































