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
MCP42XXX

- 256 taps for each potentiometer
- Potentiometer values for 10 KOhm, 50 KOhm and 100 KOhm
- Single and dual versions
- SPI serial interface (mode 0,0 and 1,1)

Attention !!
Not include CS operations. It will be managed out functions provided.
Affect Single and Daisy-Chain transactions.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef MCP42XXX_H
#define	MCP42XXX_H

#include <xc.h>
#include "globals.h"
#include "SPILib.h"

// MCP42XXX Commands
#define MCP42XXX_WRITE_DATA_POT0_CMD 0x11
#define MCP42XXX_WRITE_DATA_POT1_CMD 0x12
#define MCP42XXX_WRITE_DATA_POT_ALL_CMD 0x13
#define MCP42XXX_SHUTDOWN_POT0_CMD 0x21
#define MCP42XXX_SHUTDOWN_POT1_CMD 0x22
#define MCP42XXX_SHUTDOWN_POT_ALL_CMD 0x23

/**
 * This function writes a new wiper position on Pot 0
 *
 * @param newTapValue Tap to set [0..255]
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t MCP42XXX_Pot0_Write_Data_SPI1 (uint8_t newTapValue);
#ifdef SPI2_AVAILABLE
    int8_t MCP42XXX_Pot0_Write_Data_SPI2 (uint8_t newTapValue);
#endif

/**
 * This function shutoff and set to high impedance the Pot 0
 *
 * @param void
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t MCP42XXX_Pot0_Shutdown_SPI1 (void);
#ifdef SPI2_AVAILABLE
    int8_t MCP42XXX_Pot0_Shutdown_SPI2 (void);
#endif

/**
 * This function writes a new wiper position on Pot 1
 *
 * @param newTapValue Tap to set [0..255]
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t MCP42XXX_Pot1_Write_Data_SPI1 (uint8_t newTapValue);
#ifdef SPI2_AVAILABLE
    int8_t MCP42XXX_Pot1_Write_Data_SPI2 (uint8_t newTapValue);
#endif

/**
 * This function shutoff and set to high impedance the Pot 1
 *
 * @param void
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t MCP42XXX_Pot1_Shutdown_SPI1 (void);
#ifdef SPI2_AVAILABLE
    int8_t MCP42XXX_Pot1_Shutdown_SPI2 (void);
#endif

/**
 * This function writes a new wiper position on all Pots
 *
 * @param newTapValue Tap to set [0..255]
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t MCP42XXX_Pot_All_Write_Data_SPI1 (uint8_t newTapValue);
#ifdef SPI2_AVAILABLE
    int8_t MCP42XXX_Pot_All_Write_Data_SPI2 (uint8_t newTapValue);
#endif   

/**
 * This function shutoff and set to high impedance all Pots
 *
 * @param void
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t MCP42XXX_Pot_All_Shutdown_SPI1 (void);
#ifdef SPI2_AVAILABLE
    int8_t MCP42XXX_Pot_All_Shutdown_SPI2 (void);
#endif    

#endif	/* MCP42XXX_H */
