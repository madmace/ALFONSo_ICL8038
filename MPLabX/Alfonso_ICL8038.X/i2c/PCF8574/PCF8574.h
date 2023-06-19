/*******************************************************************************

Author : Emiliano Mazza
Version : 1.0
Created on Date : 15/18/2020
Last update     : 31/01/2023

CopyRight 2006-2015 all rights are reserved

THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT,
IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

This Header contains I2C Library functions for
Remote 8bit I/O Expander I2C with interrupt series
PCF8574/PCF8574A

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef PCF8574_H
#define	PCF8574_H

#include <xc.h>
#include "globals.h"
#include "I2CLib.h"

// Device Settings Addresses
#define USED_DEVICE_PCF8574 0x40
#define USED_DEVICE_PCF8574A 0x70

#ifndef PCF8574_INTERNAL_ADDRESS
    #define PCF8574_INTERNAL_ADDRESS USED_DEVICE_PCF8574
#endif

/**
 * @brief This function writes to the data Port of the I2C I/O expander.
 *
 * @param device_address Is the address of the PCF8574 (Internal Address + Pin address)
 *
 * @param data Byte to write [min: 0, max: 255]
 *
 * @return status
 * 0: The byte has been properly written
 * -1: Communication Error
 *
 * @note
 * PCF8574  Address : 0100xxx0
 * PCF8574A Address : 0111xxx0
 * xxx = A2 A1 A0 (External Address Pins)
 * 
 */
int8_t PCF8574_I2C1_write_data (uint8_t device_address, uint8_t data);
#ifdef I2C2_AVAILABLE
    int8_t PCF8574_I2C2_write_data (uint8_t device_address, uint8_t data);
#endif

/**
 * @brief This function reads to the data Port of the I2C I/O expander.
 *
 * @param device_address Is the address of the PCF8574 (Internal Address + Pin address)
 *
 * @param data Address where the data is written into.
 *
 * @return status
 * 0: The byte has been properly written
 * -1: Communication Error
 *
 * @note
 * PCF8574  Address : 0100xxx0
 * PCF8574A Address : 0111xxx0
 * xxx = A2 A1 A0 (External Address Pins)
 * 
 */
int8_t PCF8574_I2C1_read_data(uint8_t device_address, uint8_t *data);
#ifdef I2C2_AVAILABLE
    int8_t PCF8574_I2C2_read_data(uint8_t device_address, uint8_t *data);
#endif

#endif	/* PCF8574_H */
