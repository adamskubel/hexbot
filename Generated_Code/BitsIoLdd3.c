/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : BitsIoLdd3.c
**     Project     : HexLEDTest
**     Processor   : MK22FN512VLH12
**     Component   : BitsIO_LDD
**     Version     : Component 01.029, Driver 01.05, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-23, 01:03, # CodeGen: 42
**     Abstract    :
**         The HAL BitsIO component provides a low level API for unified
**         access to general purpose digital input/output 32 pins across
**         various device designs.
**
**         RTOS drivers using HAL BitsIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : BitsIoLdd3
**          Port                                           : PTB
**          Pins                                           : 2
**            Pin0                                         : 
**              Pin                                        : PTB18/FTM2_CH0/I2S0_TX_BCLK/FBa_AD15/FTM2_QD_PHA
**            Pin1                                         : 
**              Pin                                        : PTB19/FTM2_CH1/I2S0_TX_FS/FBa_OE_b/FTM2_QD_PHB
**          Direction                                      : Input/Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 0
**            Auto initialization                          : yes
**          Safe mode                                      : yes
**     Contents    :
**         Init   - LDD_TDeviceData* BitsIoLdd3_Init(LDD_TUserData *UserDataPtr);
**         GetDir - bool BitsIoLdd3_GetDir(LDD_TDeviceData *DeviceDataPtr);
**         SetDir - void BitsIoLdd3_SetDir(LDD_TDeviceData *DeviceDataPtr, bool Dir);
**         GetVal - uint32_t BitsIoLdd3_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         PutVal - void BitsIoLdd3_PutVal(LDD_TDeviceData *DeviceDataPtr, uint32_t Val);
**         GetBit - LDD_TError BitsIoLdd3_GetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit,...
**         PutBit - LDD_TError BitsIoLdd3_PutBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit,...
**         SetBit - LDD_TError BitsIoLdd3_SetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);
**         ClrBit - LDD_TError BitsIoLdd3_ClrBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);
**         NegBit - LDD_TError BitsIoLdd3_NegBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);
**
**     (c) 2012 by Freescale
** ###################################################################*/
/*!
** @file BitsIoLdd3.c
** @version 01.05
** @brief
**         The HAL BitsIO component provides a low level API for unified
**         access to general purpose digital input/output 32 pins across
**         various device designs.
**
**         RTOS drivers using HAL BitsIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup BitsIoLdd3_module BitsIoLdd3 module documentation
**  @{
*/         

/* MODULE BitsIoLdd3. */

/* {Default RTOS Adapter} No RTOS includes */
#include "BitsIoLdd3.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserDataPtr;          /* Pointer to user data */
} BitsIoLdd3_TDeviceData;              /* Device data structure type */

typedef BitsIoLdd3_TDeviceData *BitsIoLdd3_TDeviceDataPtr ; /* Pointer to the device data structure. */

static const uint32_t BitsIoLdd3_PIN_MASK_MAP[2U] = {
   0x00040000U, 0x00080000U
};                                     /* Map of masks for each pin */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static BitsIoLdd3_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;


/*
** ===================================================================
**     Method      :  BitsIoLdd3_Init (component BitsIO_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* BitsIoLdd3_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  BitsIoLdd3_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Enable device clock gate */
  /* SIM_SCGC5: PORTB=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
  /* Configure pin directions */
  /* GPIOB_PDDR: PDD|=0x000C0000 */
  GPIOB_PDDR |= GPIO_PDDR_PDD(0x000C0000);
  /* Set initialization value */
  /* GPIOB_PDOR: PDO&=~0x000C0000 */
  GPIOB_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x000C0000));
  /* Initialization of pin routing */
  /* PORTB_PCR18: ISF=0,MUX=1 */
  PORTB_PCR18 = (uint32_t)((PORTB_PCR18 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x06)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x01)
                ));
  /* PORTB_PCR19: ISF=0,MUX=1 */
  PORTB_PCR19 = (uint32_t)((PORTB_PCR19 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x06)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x01)
                ));
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_BitsIoLdd3_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_GetDir (component BitsIO_LDD)
*/
/*!
**     @brief
**         Returns the selected direction.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Possible values:
**                           [false] - Input
**                           [true] - Output
*/
/* ===================================================================*/
bool BitsIoLdd3_GetDir(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Return the direction of the bits in the mask */
  if ((GPIO_PDD_GetPortDirection(BitsIoLdd3_MODULE_BASE_ADDRESS) & BitsIoLdd3_PIN_ALLOC_0_MASK) != 0U) {
    return (bool)TRUE;
  } else {
    return (bool)FALSE;
  }
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_SetDir (component BitsIO_LDD)
*/
/*!
**     @brief
**         Sets a direction for the pins (available only if Direction =
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Dir             - Direction to set. Possible values:
**                           [false] - Input
**                           [true] - Output
*/
/* ===================================================================*/
void BitsIoLdd3_SetDir(LDD_TDeviceData *DeviceDataPtr, bool Dir)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (Dir) {
    /* Output */
    GPIO_PDD_SetPortOutputDirectionMask(BitsIoLdd3_MODULE_BASE_ADDRESS, BitsIoLdd3_PORT_MASK);
  } else {
    /* Input */
    GPIO_PDD_SetPortInputDirectionMask(BitsIoLdd3_MODULE_BASE_ADDRESS, BitsIoLdd3_PORT_MASK);
  }
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_GetVal (component BitsIO_LDD)
*/
/*!
**     @brief
**         Returns the value of the Input/Output component. If the
**         direction is [input] then reads the input value of the pins
**         and returns it. If the direction is [output] then returns
**         the last written value (see [Safe mode] property for
**         limitations).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Input value
*/
/* ===================================================================*/
uint32_t BitsIoLdd3_GetVal(LDD_TDeviceData *DeviceDataPtr)
{
  uint32_t PortData;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if ((GPIO_PDD_GetPortDirection(BitsIoLdd3_MODULE_BASE_ADDRESS) & BitsIoLdd3_PORT_MASK) != 0U) {
    /* Port is configured as output */
    PortData = GPIO_PDD_GetPortDataOutput(BitsIoLdd3_MODULE_BASE_ADDRESS) & BitsIoLdd3_PORT_MASK;
  } else {
    /* Port is configured as input */
    PortData = GPIO_PDD_GetPortDataInput(BitsIoLdd3_MODULE_BASE_ADDRESS) & BitsIoLdd3_PORT_MASK;
  }
  return PortData >> BitsIoLdd3_PIN_ALLOC_0_INDEX; /* Return port data shifted with the offset of the first allocated pin*/
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_PutVal (component BitsIO_LDD)
*/
/*!
**     @brief
**         Specified value is passed to the Input/Output component. If
**         the direction is [input] saves the value to a memory or a
**         register, this value will be written to the pins after
**         switching to the output mode - using [SetDir(TRUE)] (see
**         [Safe mode] property for limitations). If the direction is
**         [output] it writes the value to the pins. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Val             - Output value
*/
/* ===================================================================*/
void BitsIoLdd3_PutVal(LDD_TDeviceData *DeviceDataPtr, uint32_t Val)
{
  /* Store the raw value of the port, set according to the offset of the first allocated pin */
  uint32_t RawVal;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Calculate the raw data to be set (i.e. shifted to left according to the first allocated pin) */
  RawVal = (Val & BitsIoLdd3_PORT_VALID_VALUE_MASK) << BitsIoLdd3_PIN_ALLOC_0_INDEX; /* Mask and shift output value */
  /* Set port data by toggling the different bits only */
  GPIO_PDD_TogglePortDataOutputMask(BitsIoLdd3_MODULE_BASE_ADDRESS,
      (GPIO_PDD_GetPortDataOutput(BitsIoLdd3_MODULE_BASE_ADDRESS) ^ RawVal) & BitsIoLdd3_PORT_MASK);
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_GetBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Returns the value of the specified bit/pin of the
**         Input/Output component. If the direction is [input] then it
**         reads the input value of the pin and returns it. If the
**         direction is [output] then it returns the last written value
**         (see [Safe mode] property for limitations).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Bit             - Bit/pin number to read
**     @param
**         BitVal          - The returned value: 
**                           [false] - logical "0" (Low level)
**                           [true] - logical "1" (High level)
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
**                           ERR_PARAM_VALUE - Invalid output parameter
*/
/* ===================================================================*/
LDD_TError BitsIoLdd3_GetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit, bool *BitVal)
{
  uint32_t Mask = 0;
  uint32_t PortVal;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Bit number value - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Bit > 1U) {
    return ERR_PARAM_INDEX;
  }
  /* Bit value returned - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (BitVal == NULL) {
    return ERR_PARAM_VALUE;
  }
  Mask = BitsIoLdd3_PIN_MASK_MAP[Bit];
  if ((GPIO_PDD_GetPortDirection(BitsIoLdd3_MODULE_BASE_ADDRESS) & Mask) != 0U) {
    /* Port is configured as output */
    PortVal = GPIO_PDD_GetPortDataOutput(BitsIoLdd3_MODULE_BASE_ADDRESS);
  } else {
    /* Port is configured as input */
    PortVal = GPIO_PDD_GetPortDataInput(BitsIoLdd3_MODULE_BASE_ADDRESS);
  }
  if ((PortVal & Mask) != 0U) {
    *BitVal = (bool)TRUE;
  } else {
    *BitVal = (bool)FALSE;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_PutBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Specified value is passed to the specified bit/pin of the
**         Input/Output component. If the direction is [input] it saves
**         the value to a memory or register, this value will be
**         written to the pin after switching to the output mode -
**         using [SetDir(TRUE)] (see [Safe mode] property for
**         limitations). If the direction is [output] it writes the
**         value to the pin. (Method is available only if the Direction
**         = _[output]_ or _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number
**     @param
**         Val             - A new bit value. Possible values:
**                           [false] - logical "0" (Low level)
**                           [true] - logical "1" (High level)
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd3_PutBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit, bool Val)
{
  uint32_t Mask = 0;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Bit number value - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Bit > 1U) {
    return ERR_PARAM_INDEX;
  }
  Mask = BitsIoLdd3_PIN_MASK_MAP[Bit];
  if (Val) {
    GPIO_PDD_SetPortDataOutputMask(BitsIoLdd3_MODULE_BASE_ADDRESS, Mask);
  } else { /* !Val */
    GPIO_PDD_ClearPortDataOutputMask(BitsIoLdd3_MODULE_BASE_ADDRESS, Mask);
  } /* !Val */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_SetBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Sets (to one) the specified bit of the Input/Output
**         component. It is the same as [PutBit(Bit, TRUE)]. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number to set
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd3_SetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit)
{
  uint32_t Mask = 0;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Bit number value - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Bit > 1U) {
    return ERR_PARAM_INDEX;
  }
  Mask = BitsIoLdd3_PIN_MASK_MAP[Bit];
  GPIO_PDD_SetPortDataOutputMask(BitsIoLdd3_MODULE_BASE_ADDRESS, Mask);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_ClrBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Clears (sets to zero) the specified bit of the Input/Output
**         component. It is the same as [PutBit(Bit, FALSE)]. (Method
**         is available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number to clear
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd3_ClrBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit)
{
  uint32_t Mask = 0;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Bit number value - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Bit > 1U) {
    return ERR_PARAM_INDEX;
  }
  Mask = BitsIoLdd3_PIN_MASK_MAP[Bit];
  GPIO_PDD_ClearPortDataOutputMask(BitsIoLdd3_MODULE_BASE_ADDRESS, Mask);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  BitsIoLdd3_NegBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Negates (inverts) the specified bit of the Input/Output
**         component. It is the same as [PutBit(Bit,!GetBit(Bit))].
**         (Method is available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number to invert
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd3_NegBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit)
{
  uint32_t Mask = 0;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Bit number value - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Bit > 1U) {
    return ERR_PARAM_INDEX;
  }
  Mask = BitsIoLdd3_PIN_MASK_MAP[Bit];
  GPIO_PDD_TogglePortDataOutputMask(BitsIoLdd3_MODULE_BASE_ADDRESS, Mask);
  return ERR_OK;
}

/* END BitsIoLdd3. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
