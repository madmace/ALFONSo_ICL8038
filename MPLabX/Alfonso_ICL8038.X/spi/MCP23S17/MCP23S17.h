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

This Header contains SPI Library functions for
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

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef MCP23S17_H
#define	MCP23S17_H

#include <xc.h>
#include "globals.h"
#include "SPILib.h"

// Device Settings Addresses
#define PREFIX_DEVICE_MCP23S17 0x40

// MCP23S08 Register addresses

// Used IOCON.BANK = 0
// The address pointer to toggle between associated A/B register pairs
#define MCP23S17_IODIRA_16 0x00                 // Port A Direction : 1 Input, 0 Output
#define MCP23S17_IODIRB_16 0x01                 // Port B Direction : 1 Input, 0 Output
#define MCP23S17_IPOLA_16 0x02                  // Port A Polarity : 1 opposite, 0 direct
#define MCP23S17_IPOLB_16 0x03                  // Port B Polarity : 1 opposite, 0 direct
#define MCP23S17_GPINTENA_16 0x04               // Port A Interrupt on change : 1 enable, 0 disable
#define MCP23S17_GPINTENB_16 0x05               // Port B Interrupt on change : 1 enable, 0 disable
#define MCP23S17_DEFVALA_16 0x06                // Port A Default compare bits for interrupt change
#define MCP23S17_DEFVALB_16 0x07                // Port B Default compare bits for interrupt change
#define MCP23S17_INTCONA_16 0x08                // Port A Interrupt on change Control register 
#define MCP23S17_INTCONB_16 0x09                // Port B Interrupt on change Control register 
#define MCP23S17_IOCON_16 0x0A                  // Port A/B I/O Expander Configuration Register                  
#define MCP23S17_GPPUA_16 0x0C                  // Port A pull-up resistors Configuration Register : 1 = Pull-up enabled, 0 = Pull-up disabled
#define MCP23S17_GPPUB_16 0x0D                  // Port B pull-up resistors Configuration Register : 1 = Pull-up enabled, 0 = Pull-up disabled
#define MCP23S17_INTFA_16 0x0E                  // Port A Interrupt Flag Register
#define MCP23S17_INTFB_16 0x0F                  // Port B Interrupt Flag Register
#define MCP23S17_INTCAPA_16 0x10                // Port A Interrupt Captured value Register
#define MCP23S17_INTCAPB_16 0x11                // Port B Interrupt Captured value Register
#define MCP23S17_GPIOA_16 0x12                  // Port A General purpose I/O register
#define MCP23S17_GPIOB_16 0x13                  // Port B General purpose I/O register
#define MCP23S17_OLATA_16 0x14                  // Port A Output Latch register
#define MCP23S17_OLATB_16 0x15                  // Port B Output Latch register

// Used IOCON.BANK = 1
// The registers associated with each port are separated into different banks.
#define MCP23S17_IODIRA_8 0x00                  // Port A Direction : 1 Input, 0 Output
#define MCP23S17_IPOLA_8 0x01                   // Port A Polarity : 1 opposite, 0 direct
#define MCP23S17_GPINTENA_8 0x02                // Port A Interrupt on change : 1 enable, 0 disable
#define MCP23S17_DEFVALA_8 0x03                 // Port A Default compare bits for interrupt change
#define MCP23S17_INTCONA_8 0x04                 // Port A Interrupt on change Control register
#define MCP23S17_IOCON_8 0x05                   // Port A I/O Expander Configuration Register 
#define MCP23S17_GPPUA_8 0x06                   // Port A pull-up resistors Configuration Register : 1 = Pull-up enabled, 0 = Pull-up disabled
#define MCP23S17_INTFA_8 0x07                   // Port A Interrupt Flag Register
#define MCP23S17_INTCAPA_8 0x08                 // Port A Interrupt Captured value Register
#define MCP23S17_GPIOA_8 0x09                   // Port A General purpose I/O register
#define MCP23S17_OLATA_8 0x0A                   // Port A Output Latch register
#define MCP23S17_IODIRB 0x10                    // Port B Direction : 1 Input, 0 Output
#define MCP23S17_IPOLB 0x11                     // Port B Polarity : 1 opposite, 0 direct
#define MCP23S17_GPINTENB 0x12                  // Port B Interrupt on change : 1 enable, 0 disable
#define MCP23S17_DEFVALB 0x13                   // Port B Default compare bits for interrupt change
#define MCP23S17_INTCONB 0x14                   // Port B Interrupt on change Control register
#define MCP23S17_IOCON 0x15                     // Port B I/O Expander Configuration Register 
#define MCP23S17_GPPUB 0x16                     // Port B pull-up resistors Configuration Register : 1 = Pull-up enabled, 0 = Pull-up disabled
#define MCP23S17_INTFB 0x17                     // Port B Interrupt Flag Register
#define MCP23S17_INTCAPB 0x18                   // Port B Interrupt Captured value Register
#define MCP23S17_GPIOB 0x19                     // Port B General purpose I/O register
#define MCP23S17_OLATB 0x1A                     // Port B Output Latch register

// IOCON IO Control Register bit masks
#define MCP23S17_IOCON_BANK 0x80                // bit 7 BANK: Controls how the registers are addressed : 1 = Separated, 0 = Same bank.
#define MCP23S17_IOCON_MIRROR 0x40              // bit 6 MIRROR: INT Pins Mirror bit : 1 = The INT pins are internally connected, 0 = The INT pins are not connected.
#define MCP23S17_IOCON_SEQOP 0x20               // bit 5 SEQOP: Sequential Operation mode bit : 1 = Sequential operation disabled, 0 = Sequential operation enabled.
#define MCP23S17_IOCON_DISSLW 0x10              // bit 4 DISSLW: Slew Rate control bit for SDA output : 1 = Slew rate disabled, 0 = Slew rate enabled
#define MCP23S17_IOCON_HAEN 0x08                // bit 3 HAEN: Hardware Address Enable bit (MCP23S17 only) : 1 = Enables the MCP23S17 address pins, 0 = Disables the MCP23S17 address pins.
#define MCP23S17_IOCON_ODR 0x04                 // bit 2 ODR: Configures the INT pin as an open-drain output: 1 = Open-drain output (overrides the INTPOL bit.), 0 = Active driver output (INTPOL bit sets the polarity.)
#define MCP23S17_IOCON_INTPOL 0x02              // bit 1 INTPOL: This bit sets the polarity of the INT output pin : 1 = Active-high, 0 = Active-low
#define MCP23S17_IOCON_NI 0x01                  // bit 0 Unimplemented: Read as 0

// ICON Fixed Library bit mask
// The fixed operational are:
// IOCON.BANK is NOT set.       Controls how the registers are addressed : 1 = Separated, 0 = Same bank.
// IOCON.MIRROR is set to 0.    The INT pins are not connected.
// IOCON.SEQOP is set to 0.     Sequential operation enabled.
// IOCON.DISSLW is set to 0.    Slew rate enabled.
// IOCON.HAEN is set to 1.      Enables the MCP23S17 address pins.
// IOCON.ODR is set to 0.       Active driver output (INTPOL bit sets the polarity.)
// IOCON.INTPOL is set to 0.    Active-low
// Unimplemented: Read as 0
// x0001000                     Bits fixed mask
#define MCP23S17_IOCON_MASK 0x08

// ICON address mode
#define MCP23S17_8BIT 0x01
#define MCP23S17_16BIT 0x00

/**
 * @brief 
 * This function writes to the register Port of the SPI I/O expander.
 * This works in 8-bit mode
 *
 * @param device_address Is the address of the MCP23S17 (3 bit Pin address)
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
int8_t MCP23S17_Write_Byte_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_Write_Byte_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t data);
#endif
    
/**
 * @brief 
 * This function writes to the register Port of the SPI I/O expander.
 * This works in 16-bit mode
 *
 * @param device_address Is the address of the MCP23S17 (3 bit Pin address)
 * 
 * @param register_address Address of register where write
 * 
 * @param data Byte to write in the register [min: 0, max: 65535]
 *
 * @return error 
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
int8_t MCP23S17_Write_Word_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint16_t data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_Write_Word_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint16_t data);
#endif

/**
 * @brief 
 * This function read from the register Port of the SPI I/O expander.
 * This works in 8-bit mode
 *
 * @param device_address Is the address of the MCP23S17 (3 bit Pin address)
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
int8_t MCP23S17_Read_Byte_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t *data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_Read_Byte_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t *data);
#endif

/**
 * @brief 
 * This function read from the register Port of the SPI I/O expander.
 * This works in 16-bit mode
 *
 * @param device_address Is the address of the MCP23S17 (3 bit Pin address)
 * 
 * @param register_address Address of register where read
 *
 * @param data Address where the data is written into.
 * 
 * @return status
 * 0: The byte has been properly written
 * -1: Communication Error
 * 
 * @warning The function is a blocking one. It waits for 16 bits to be sent out.
 * 
 */
int8_t MCP23S17_Read_Word_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint16_t *data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_Read_Word_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint16_t *data);
#endif

/**
 * @brief 
 * This function inizialize the SPI I/O expander.
 * Sets the IOCON register
 * The fixed operational are:
 * 
 * IOCON.MIRROR is set to 0.    The INT pins are not connected.
 * IOCON.SEQOP is set to 0.     Sequential operation enabled.
 * IOCON.DISSLW is set to 0.    Slew rate enabled.
 * IOCON.HAEN is set to 1.      Enables the MCP23S17 address pins.
 * IOCON.ODR is set to 0.       Active driver output (INTPOL bit sets the polarity.)
 * IOCON.INTPOL is set to 0.    Active-low
 *
 * @param device_address Is the address of the MCP23S17 (3 bit Pin address)
 * 
 * @param mode
 * Set the mode 8-bit (BANK = 1) or 16-bit (BANK = 0)
 * 0 8-bit mode
 * 1 16-bit mode
 *
 * @return error 
 * Communication error 
 * 0: The byte has been properly written
 * -1: Communication error
 * 
 */
int8_t MCP23S17_init_SPI1 (uint8_t device_address, uint8_t mode);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_init_SPI2 (uint8_t device_address, uint8_t mode);
#endif

#endif	/* MCP23S17_H */
