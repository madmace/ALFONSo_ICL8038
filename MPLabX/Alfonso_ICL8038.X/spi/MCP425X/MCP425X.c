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
MCP425X

*******************************************************************************/

#include "MCP425X.h"
#include "SPILib.h"

// MCP425X_Pot0_Write_Data_SPI1 Implementation
int8_t MCP425X_Pot0_Write_Data_SPI1 (uint16_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t MSB_CMD = 0x00;
    uint8_t LSB_CMD = 0x00;
    
    // Copy Low Byte
    LSB_CMD = newTapValue & 0x00FF;
    // Copy Last 2 bits in High Byte
    MSB_CMD = (newTapValue & 0x0300) / 0x100;
    // Set Command
    MSB_CMD |= MCP425X_WRITE_DATA_POT0_CMD;
    
    // Send High Byte Command
    cRes = SPI1_write_byte(MSB_CMD);
    // Control result
    if (cRes == 0) {
        // Send Low Byte Command
        cRes = SPI1_write_byte(LSB_CMD);
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot0_Write_Data_SPI2 Implementation
int8_t MCP425X_Pot0_Write_Data_SPI2 (uint16_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t MSB_CMD = 0x00;
    uint8_t LSB_CMD = 0x00;
    
    // Copy Low Byte
    LSB_CMD = newTapValue & 0x00FF;
    // Copy Last 2 bits in High Byte
    MSB_CMD = (newTapValue & 0x0300) / 0x100;
    // Set Command
    MSB_CMD |= MCP425X_WRITE_DATA_POT0_CMD;
    
    // Send High Byte Command
    cRes = SPI2_write_byte(MSB_CMD);
    // Control result
    if (cRes == 0) {
        // Send Low Byte Command
        cRes = SPI2_write_byte(LSB_CMD);
    }
    
    return cRes;
}
#endif

// MCP425X_Pot0_Read_Data_SPI1 Implementation
uint16_t MCP425X_Pot0_Read_Data_SPI1 (void) {
    return 0;
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot0_Read_Data_SPI2 Implementation
uint16_t MCP425X_Pot0_Read_Data_SPI2 (void) {
    return 0;
}
#endif

// MCP425X_Pot0_Increment_Wiper_SPI1 Implementation
int8_t MCP425X_Pot0_Increment_Wiper_SPI1 (void) {    
    // Send Byte Command
    return SPI1_write_byte(MCP425X_INCREMENT_WIPER_POT0_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot0_Increment_Wiper_SPI2 Implementation
int8_t MCP425X_Pot0_Increment_Wiper_SPI2 (void) {    
    // Send Byte Command
    return SPI2_write_byte(MCP425X_INCREMENT_WIPER_POT0_CMD);
}
#endif

// MCP425X_Pot0_Decrement_Wiper_SPI1 Implementation
int8_t MCP425X_Pot0_Decrement_Wiper_SPI1 (void) {    
    // Send Byte Command
    return SPI1_write_byte(MCP425X_DECREMENT_WIPER_POT0_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot0_Decrement_Wiper_SPI2 Implementation
int8_t MCP425X_Pot0_Decrement_Wiper_SPI2 (void) {    
    // Send Byte Command
    return SPI2_write_byte(MCP425X_DECREMENT_WIPER_POT0_CMD);
}
#endif

// MCP425X_Pot1_Write_Data_SPI1 Implementation
int8_t MCP425X_Pot1_Write_Data_SPI1 (uint16_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t MSB_CMD = 0x00;
    uint8_t LSB_CMD = 0x00;
    
    // Copy Low Byte
    LSB_CMD = newTapValue & 0x00FF;
    // Copy Last 2 bits in High Byte
    MSB_CMD = (newTapValue & 0x0300) / 0x100;
    // Set Command
    MSB_CMD |= MCP425X_WRITE_DATA_POT1_CMD;
    
    // Send High Byte Command
    cRes = SPI1_write_byte(MSB_CMD);
    // Control result
    if (cRes == 0) {
        // Send Low Byte Command
        cRes = SPI1_write_byte(LSB_CMD);
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot1_Write_Data_SPI2 Implementation
int8_t MCP425X_Pot1_Write_Data_SPI2 (uint16_t newTapValue) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t MSB_CMD = 0x00;
    uint8_t LSB_CMD = 0x00;
    
    // Copy Low Byte
    LSB_CMD = newTapValue & 0x00FF;
    // Copy Last 2 bits in High Byte
    MSB_CMD = (newTapValue & 0x0300) / 0x100;
    // Set Command
    MSB_CMD |= MCP425X_WRITE_DATA_POT1_CMD;
    
    // Send High Byte Command
    cRes = SPI2_write_byte(MSB_CMD);
    // Control result
    if (cRes == 0) {
        // Send Low Byte Command
        cRes = SPI2_write_byte(LSB_CMD);
    }
    
    return cRes;
}
#endif

// MCP425X_Pot1_Read_Data_SPI1 Implementation
uint16_t MCP425X_Pot1_Read_Data_SPI1 (void) {
    return 0;
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot1_Read_Data_SPI2 Implementation
uint16_t MCP425X_Pot1_Read_Data_SPI2 (void) {
    return 0;
}
#endif

// MCP425X_Pot1_Increment_Wiper_SPI1 Implementation
int8_t MCP425X_Pot1_Increment_Wiper_SPI1 (void) {    
    // Send Byte Command
    return SPI1_write_byte(MCP425X_INCREMENT_WIPER_POT1_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot1_Increment_Wiper_SPI2 Implementation
int8_t MCP425X_Pot1_Increment_Wiper_SPI2 (void) {    
    // Send Byte Command
    return SPI2_write_byte(MCP425X_INCREMENT_WIPER_POT1_CMD);
}
#endif

// MCP425X_Pot1_Decrement_Wiper_SPI1 Implementation
int8_t MCP425X_Pot1_Decrement_Wiper_SPI1 (void) {    
    // Send Byte Command
    return SPI1_write_byte(MCP425X_DECREMENT_WIPER_POT1_CMD);
}

#ifdef SPI2_AVAILABLE
// MCP425X_Pot1_Decrement_Wiper_SPI2 Implementation
int8_t MCP425X_Pot1_Decrement_Wiper_SPI2 (void) {    
    // Send Byte Command
    return SPI2_write_byte(MCP425X_DECREMENT_WIPER_POT1_CMD);
}
#endif
