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
Dual Digital Potentiometer series
MCP425X

- 257 taps for each potentiometer
- Potentiometer values for 5KOhm, 10 KOhm, 50 KOhm and 100 KOhm
- Single and dual versions
- SPI serial interface (mode 0,0 and 1,1)

Attention !!
Not include CS operations. It will be managed out functions provided.
Affect Single and Daisy-Chain transactions.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef MCP425X_H
#define	MCP425X_H

#include <xc.h>
#include "globals.h"
#include "SPILib.h"

// MCP425X Commands
#define MCP425X_WRITE_DATA_POT0_CMD 0x00
#define MCP425X_WRITE_DATA_POT1_CMD 0x10
#define MCP425X_READ_DATA_POT0_CMD 0x0C
#define MCP425X_READ_DATA_POT1_CMD 0x1C
#define MCP425X_INCREMENT_WIPER_POT0_CMD 0x04
#define MCP425X_DECREMENT_WIPER_POT0_CMD 0x08
#define MCP425X_INCREMENT_WIPER_POT1_CMD 0x14
#define MCP425X_DECREMENT_WIPER_POT1_CMD 0x18

/**
 * @brief This function writes a new wiper position on Pot 0
 *
 * @param newTapValue Tap to set [0..256]
 *
 * @return error
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
int8_t MCP425X_Pot0_Write_Data_SPI1 (uint16_t newTapValue);
#ifdef SPI2_AVAILABLE
    int8_t MCP425X_Pot0_Write_Data_SPI2 (uint16_t newTapValue);
#endif

/**
 * @brief This function read the current taps value from the Pot 0
 *
 * @param void
 *
 * @return byte Value read from the Pot 0
 * 
 * @warning The function is a blocking one. It waits for 16 bits to be sent out.
 * 
 */
uint16_t MCP425X_Pot0_Read_Data_SPI1 (void);
#ifdef SPI2_AVAILABLE
    uint16_t MCP425X_Pot0_Read_Data_SPI2 (void);
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
int8_t MCP425X_Pot0_Increment_Wiper_SPI1 (void);
#ifdef SPI2_AVAILABLE
    nt8_t MCP425X_Pot0_Increment_Wiper_SPI2 (void);
#endif

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
int8_t MCP425X_Pot0_Decrement_Wiper_SPI1 (void);
#ifdef SPI2_AVAILABLE
    int8_t MCP425X_Pot0_Decrement_Wiper_SPI2 (void);
#endif

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
int8_t MCP425X_Pot1_Write_Data_SPI1 (uint16_t newTapValue);
#ifdef SPI2_AVAILABLE
    int8_t MCP425X_Pot1_Write_Data_SPI2 (uint16_t newTapValue);
#endif

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
uint16_t MCP425X_Pot1_Read_Data_SPI1 (void);
#ifdef SPI2_AVAILABLE
    uint16_t MCP425X_Pot1_Read_Data_SPI2 (void);
#endif

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
int8_t MCP425X_Pot1_Increment_Wiper_SPI1 (void);
#ifdef SPI2_AVAILABLE
    int8_t MCP425X_Pot1_Increment_Wiper_SPI2 (void);
#endif

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
int8_t MCP425X_Pot1_Decrement_Wiper_SPI1 (void);
#ifdef SPI2_AVAILABLE
    int8_t MCP425X_Pot1_Decrement_Wiper_SPI2 (void);
#endif

#endif	/* MCP425X_H */
