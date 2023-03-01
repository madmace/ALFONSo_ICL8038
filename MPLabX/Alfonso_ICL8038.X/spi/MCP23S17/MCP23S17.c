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
16-Bit I/O Expander MCP23S17

- 16-Bit remote bidirectional I/O port, default to input
- High-speed SPI interface 10Mhz
- 3 pins to allow up to eight device using same chip-select
- SPI serial interface (mode 0,0 and 1,1)
- Byte mode disables automatic Address Pointer incrementing
- Used IOCON.BANK = 0. The address pointer to toggle between associated A/B register pairs

Attention !!
Not include CS operations. It will be managed out functions provided.
Affect Single and Daisy-Chain transactions.

*******************************************************************************/

#include "MCP23S17.h"
#include "SPILib.h"

// MCP23S17_Write_Byte_Register_SPI1 Implementation
int8_t MCP23S17_Write_Byte_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 3 bits address for write operation
    opcode = (device_address << 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
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
int8_t MCP23S17_Write_Byte_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 3 bits address for write operation
    opcode = (device_address << 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
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

// MCP23S17_Write_Word_Register_SPI1 Implementation
int8_t MCP23S17_Write_Word_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint16_t data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 3 bits address for write operation
    opcode = (device_address << 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
    // Send Device Opcode
    cRes = SPI1_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI1_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Send First High byte
            cRes = SPI1_write_byte((uint8_t)(data >> 8));
            // Control result
            if (cRes == 0) {
                // Send Second Low byte
                cRes = SPI1_write_byte((uint8_t)(data & 0x00FF));
            }
        }
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
int8_t MCP23S17_Write_Word_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint16_t data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 3 bits address for write operation
    opcode = (device_address << 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
    // Send Device Opcode
    cRes = SPI2_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI2_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Send First High byte
            cRes = SPI2_write_byte((uint8_t)(data >> 8));
            // Control result
            if (cRes == 0) {
                // Send Second Low byte
                cRes = SPI2_write_byte((uint8_t)(data & 0x00FF));
            }
        }
    }
    
    return cRes;
}
#endif


// MCP23S17_Read_Byte_Register_SPI1 Implementation
int8_t MCP23S17_Read_Byte_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t *data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 2 bits address + 1 for read operation
    opcode = ((device_address << 1) + 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
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
int8_t MCP23S17_Read_Byte_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t *data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    
    // Copy 2 bits address + 1 for read operation
    opcode = ((device_address << 1) + 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
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

// MCP23S17_Read_Word_Register_SPI1 Implementation
int8_t MCP23S17_Read_Word_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint16_t *data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    uint8_t highbyte = 0x00;
    uint8_t lowbyte = 0x00;
    
    // Copy 2 bits address + 1 for read operation
    opcode = ((device_address << 1) + 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
    // Send Device Opcode
    cRes = SPI1_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI1_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Receive First High byte
            highbyte = SPI1_read_byte();
            // Receive Second low byte
            lowbyte = SPI1_read_byte();
            // Store to word
            *data = (highbyte << 8) + lowbyte;
        }    
    }
    
    return cRes;
}

#ifdef SPI2_AVAILABLE
int8_t MCP23S17_Read_Word_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint16_t *data) {
    
    signed char cRes = -1;      // Default in error
    
    uint8_t opcode = 0x00;      // Device Opcode
    uint8_t highbyte = 0x00;
    uint8_t lowbyte = 0x00;
    
    // Copy 2 bits address + 1 for read operation
    opcode = ((device_address << 1) + 1) & 0x0F;
    // Add prefix
    opcode |= PREFIX_DEVICE_MCP23S17;
    
    // Send Device Opcode
    cRes = SPI2_write_byte(opcode);
    // Control result
    if (cRes == 0) {
        // Send Register
        cRes = SPI2_write_byte(register_address);
        // Control result
        if (cRes == 0) {
            // Receive First High byte
            highbyte = SPI2_read_byte();
            // Receive Second low byte
            lowbyte = SPI2_read_byte();
            // Store to word
            *data = (highbyte << 8) + lowbyte;
        }    
    }
    
    return cRes;
}
#endif

// MCP23S17_init_SPI1 Implementation
int8_t MCP23S17_init_SPI1 (uint8_t device_address, uint8_t mode) {
    
    int8_t iRes = -1;               // Default in error
    
    uint8_t confreg = 0x00;         // Configuration register
    
    // Set the fixed part
    confreg |= MCP23S17_IOCON_MASK;
    
    // Controls the BANK mode
    if (mode == MCP23S17_8BIT) {
        // 8-bit mode BANK = 1
        confreg |= MCP23S17_IOCON_BANK;
    }
    
    // Write register
    iRes = MCP23S17_Write_Byte_Register_SPI1(device_address, MCP23S17_INTCONA_16, confreg);
    
    return iRes;
}

#ifdef SPI2_AVAILABLE
int8_t MCP23S17_init_SPI2 (uint8_t device_address, uint8_t mode) {
    
    int8_t iRes = -1;               // Default in error
    
    uint8_t confreg = 0x00;         // Configuration register
    
    // Set the fixed part
    confreg |= MCP23S17_IOCON_MASK;
    
    // Controls the BANK mode
    if (mode == 1) {
        // 8-bit mode BANK = 1
        confreg |= MCP23S17_IOCON_BANK;
    }
    // Write register
    iRes = MCP23S17_Write_Byte_Register_SPI2(device_address, MCP23S17_INTCONA_16, confreg);
    
    return iRes;
}
#endif
