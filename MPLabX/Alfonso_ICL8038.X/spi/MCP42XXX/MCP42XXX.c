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

This source contains SPI Library functions implementations for
Dual Digital Potentiometer series
MCP42XXX

*******************************************************************************/

#include "MCP42XXX.h"
#include "SPILib.h"

// MCP42XXX_Pot0_Write_Data_SPI1 Implementation
int8_t MCP42XXX_Pot0_Write_Data_SPI1 (uint8_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    // Send command
    cRes = SPI1_write_byte(MCP42XXX_WRITE_DATA_POT0_CMD);
    // Control result
    if (cRes == 0) {
        // Send Pot value
        cRes = SPI1_write_byte(newTapValue);
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
// MCP42XXX_Pot0_Write_Data_SPI2 Implementation
int8_t MCP42XXX_Pot0_Write_Data_SPI2 (uint8_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    // Send command
    cRes = SPI2_write_byte(MCP42XXX_WRITE_DATA_POT0_CMD);
    // Control result
    if (cRes == 0) {
        // Send Pot value
        cRes = SPI2_write_byte(newTapValue);
    }
    
    return cRes;
}
#endif

// MCP42XXX_Pot0_Shutdown_SPI1 Implementation
int8_t MCP42XXX_Pot0_Shutdown_SPI1 (void) {
    // Send command
    return SPI1_write_byte(MCP42XXX_SHUTDOWN_POT0_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP42XXX_Pot0_Shutdown_SPI2 Implementation
int8_t MCP42XXX_Pot0_Shutdown_SPI2 (void) {
    // Send command
    return SPI2_write_byte(MCP42XXX_SHUTDOWN_POT0_CMD);
}
#endif

// MCP42XXX_Pot1_Write_Data_SPI1 Implementation
int8_t MCP42XXX_Pot1_Write_Data_SPI1 (uint8_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    // Send command
    cRes = SPI1_write_byte(MCP42XXX_WRITE_DATA_POT1_CMD);
    // Control result
    if (cRes == 0) {
        // Send Pot value
        cRes = SPI1_write_byte(newTapValue);
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
// MCP42XXX_Pot1_Write_Data_SPI2 Implementation
int8_t MCP42XXX_Pot1_Write_Data_SPI2 (uint8_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    // Send command
    cRes = SPI2_write_byte(MCP42XXX_WRITE_DATA_POT1_CMD);
    // Control result
    if (cRes == 0) {
        // Send Pot value
        cRes = SPI2_write_byte(newTapValue);
    }
    
    return cRes;
}
#endif

// MCP42XXX_Pot1_Shutdown_SPI1 Implementation
int8_t MCP42XXX_Pot1_Shutdown_SPI1 (void) {
    // Send command
    return SPI1_write_byte(MCP42XXX_SHUTDOWN_POT1_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP42XXX_Pot1_Shutdown_SPI2 Implementation
int8_t MCP42XXX_Pot1_Shutdown_SPI2 (void) {
    // Send command
    return SPI2_write_byte(MCP42XXX_SHUTDOWN_POT1_CMD);
}
#endif

// MCP42XXX_Pot_All_Data_SPI1 Implementation
int8_t MCP42XXX_Pot_All_Data_SPI1 (uint8_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    // Send command
    cRes = SPI1_write_byte(MCP42XXX_WRITE_DATA_POT_ALL_CMD);
    // Control result
    if (cRes == 0) {
        // Send Pot value
        cRes = SPI1_write_byte(newTapValue);
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
// MCP42XXX_Pot_All_Data_SPI2 Implementation
int8_t MCP42XXX_Pot_All_Data_SPI2 (uint8_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    // Send command
    cRes = SPI2_write_byte(MCP42XXX_WRITE_DATA_POT_ALL_CMD);
    // Control result
    if (cRes == 0) {
        // Send Pot value
        cRes = SPI2_write_byte(newTapValue);
    }
    
    return cRes;
}
#endif

// MCP42XXX_Pot_All_Shutdown_SPI1 Implementation
int8_t MCP42XXX_Pot_All_Shutdown_SPI1 (void) {
    // Send command
    return SPI1_write_byte(MCP42XXX_SHUTDOWN_POT_ALL_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP42XXX_Pot_All_Shutdown_SPI2 Implementation
int8_t MCP42XXX_Pot_All_Shutdown_SPI2 (void) {
    // Send command
    return SPI2_write_byte(MCP42XXX_SHUTDOWN_POT_ALL_CMD);
}
#endif
