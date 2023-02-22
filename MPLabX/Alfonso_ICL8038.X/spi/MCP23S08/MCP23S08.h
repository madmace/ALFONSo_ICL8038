/*******************************************************************************

Author : Emiliano Mazza
Version : 1.0
Created on Date : 01/03/2016
Last update     : 18/03/2016

CopyRight 2006-2015 all rights are reserved

THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT,
IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

This Header contains SPI Library functions for
8-Bit I/O Expander MCP23S08

- 8-Bit remote bidirectional I/O port, default to input
- High-speed SPI interface 10Mhz
- 2 pins to allow up to four device using same chip-select
- SPI serial interface (mode 0,0 and 1,1)

Attention !!
Not include CS operations. It will be managed out functions provided.
Affect Single and Daisy-Chain transactions.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef MCP23S08_H
#define	MCP23S08_H

#include <xc.h>
#include "globals.h"
#include "SPILib.h"


// Device Settings Addresses
#define PREFIX_DEVICE_MCP23S08 0x40

// MCP23S08 Register addresses
#define MCP23S08_IODIR 0x00             // Direction : 1 Input, 0 Output
#define MCP23S08_IPOL 0x01              // Polarity : 1 opposite, 0 direct
#define MCP23S08_GPINTEN 0x02           // Interrupt on change : 1 enable, 0 disable
#define MCP23S08_DEFVAL 0x03            // Default compare bits for interrupt change
#define MCP23S08_INTCON 0x04            // Interrupt control : 1 compare with DELFAL, 0 with previous value
#define MCP23S08_IOCON 0x05             // bit 7-6 Unimplemented
                                        // bit 5 SEQOP Sequential Operation mode : 1 disabled, 0 enabled
                                        // bit 4 DISSLW Disable Slew rate : 1 disabled, 0 enabled
                                        // bit 3 HAEN Hardware Address Enable : 1 enable, 0 disable
                                        // bit 2 ODR open-drain INT pin : 1 open-drain (overrides INTPOL bit), 0 active driver
                                        // bit 1 INTPOL polarity INT pin : 1 active-high, 0 active-low
#define MCP23S08_GPPU 0x06              // Input pull-up resistor : 1 enabled (when set as input), 0 disabled
#define MCP23S08_INTF 0x07              // Interrupt Flag (read-only): 1 pin caused interrupt, 0 interrupt not pending 
#define MCP23S08_INTCAP 0x08            // Capture GPIO port value at interrupt (read-only)
#define MCP23S08_GPIO 0x09              // Reflets value on port
#define MCP23S08_OLAT 0x0A              // Access to the poutput latches

/**
 * @brief This function writes to the register Port of the SPI I/O expander.
 *
 * @param device_address Is the address of the MCP23S08 (2 bit Pin address)
 * 
 * @param register_address Address of register where write
 * 
 * @param data Byte to write in the register [min: 0, max: 255]
 *
 * @return error 
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
int8_t MCP23S08_Write_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S08_Write_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t data);
#endif

/**
 * @brief This function read from the register Port of the SPI I/O expander.
 *
 * @param device_address Is the address of the MCP23S08 (2 bit Pin address)
 * 
 * @param register_address Address of register where read
 *
 * @param data Address where the data is written into.
 * 
 * @return status
 * 0: The byte has been properly written
 * -1: Communication Error
 * 
 * @warning The function is a blocking one. It waits for 8 bits to be sent out.
 * 
 */
int8_t MCP23S08_Read_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t *data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S08_Read_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t *data);
#endif

/**
 * @brief This function increment by one tap the Pot 0
 *
 * @param void
 *
 * @return error
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
//int8_t MCP425X_Pot0_Increment_Wiper_SPI1 (void);
//#ifdef SPI2_AVAILABLE
//    int8_t MCP425X_Pot0_Increment_Wiper_SPI2 (void);
//#endif

/**
 * @brief This function decrement by one tap the Pot 0
 *
 * @param void
 *
 * @return error 
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
//int8_t MCP425X_Pot0_Decrement_Wiper_SPI1 (void);
//#ifdef SPI2_AVAILABLE
//    int8_t MCP425X_Pot0_Decrement_Wiper_SPI2 (void);
//#endif

/**
 * @brief This function writes a new wiper position on Pot 1
 *
 * @param newTapValue Tap to set [0..256]
 *
 * @return error
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
//int8_t MCP425X_Pot1_Write_Data_SPI1 (uint16_t newTapValue);
//#ifdef SPI2_AVAILABLE
//    int8_t MCP425X_Pot1_Write_Data_SPI2 (uint16_t newTapValue);
//#endif

/**
 * @brief This function read the current taps value from the Pot 1
 *
 * @param void
 *
 * @return byte Value read from the Pot 1
 * 
 * @warning The function is a blocking one. It waits for 16 bits to be sent out.
 * 
 */
//uint16_t MCP425X_Pot1_Read_Data_SPI1 (void);
//#ifdef SPI2_AVAILABLE
//    uint16_t MCP425X_Pot1_Read_Data_SPI2 (void);
//#endif

/**
 * @brief This function increment by one tap the Pot 1
 *
 * @param void
 *
 * @return error
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
//int8_t MCP425X_Pot1_Increment_Wiper_SPI1 (void);
//#ifdef SPI2_AVAILABLE
//    int8_t MCP425X_Pot1_Increment_Wiper_SPI2 (void);
//#endif

/**
 * @brief This function decrement by one tap the Pot 1
 *
 * @param void
 *
 * @return error
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
///int8_t MCP425X_Pot1_Decrement_Wiper_SPI1 (void);
//#ifdef SPI2_AVAILABLE
//    int8_t MCP425X_Pot1_Decrement_Wiper_SPI2 (void);
//#endif

#endif	/* MCP23S08_H */
