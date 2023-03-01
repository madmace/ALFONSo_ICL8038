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

This source contains SPI Library functions implementations for
8-Bit I/O Expander MCP23S08

- 8-Bit remote bidirectional I/O port, default to input
- High-speed SPI interface 10Mhz
- 2 pins to allow up to four device using same chip-select
- SPI serial interface (mode 0,0 and 1,1)

Attention !!
Not include CS operations. It will be managed out functions provided.
Affect Single and Daisy-Chain transactions.

*******************************************************************************/

#include "MCP23S08.h"
#include "SPILib.h"

// MCP23S08_Write_Register_SPI1 Implementation
int8_t MCP23S08_Write_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 2 bits address + 0 for write operation
    opcode = (device_address << 1) & 0x07;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S08;
    
    // Send Device Opcode
    cRes = SPI1_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI1_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Send Configuration
            cRes = SPI1_write_byte(data);
        }
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
// MCP23S08_Write_Register_SPI2 Implementation
int8_t MCP23S08_Write_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 2 bits address + 0 for write operation
    opcode = (device_address << 1) & 0x07;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S08;
    
    // Send Device Opcode
    cRes = SPI2_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI2_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Send Configuration
            cRes = SPI2_write_byte(data);
        }
    }
    
    return cRes;
}
#endif

// MCP23S08_Read_Register_SPI1 Implementation
int8_t MCP23S08_Read_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t *data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 2 bits address + 1 for read operation
    opcode = ((device_address << 1) + 1) & 0x07;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S08;
    
    // Send Device Opcode
    cRes = SPI1_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI1_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Receive byte
            *data = SPI1_read_byte();
        }    
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
int8_t MCP23S08_Read_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t *data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 2 bits address + 1 for read operation
    opcode = ((device_address << 1) + 1) & 0x07;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S08;
    
    // Send Device Opcode
    cRes = SPI2_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI2_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Receive byte
            *data = SPI2_read_byte();
        }    
    }
    
    return cRes;
}
#endif
