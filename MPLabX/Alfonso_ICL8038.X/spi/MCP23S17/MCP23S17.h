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
// Byte mode disables automatic Address Pointer incrementing
// Used IOCON.BANK = 0
// The address pointer to toggle between associated A/B register pairs
#define MCP23S17_IODIRA 0x00                // Port A Direction : 1 Input, 0 Output
#define MCP23S17_IODIRB 0x01                // Port B Direction : 1 Input, 0 Output
#define MCP23S17_IPOLA 0x02                 // Port A Polarity : 1 opposite, 0 direct
#define MCP23S17_IPOLB 0x03                 // Port B Polarity : 1 opposite, 0 direct
#define MCP23S17_GPINTENA 0x04              // Port A Interrupt on change : 1 enable, 0 disable
#define MCP23S17_GPINTENB 0x05              // Port B Interrupt on change : 1 enable, 0 disable
#define MCP23S17_DEFVALA 0x06               // Port A Default compare bits for interrupt change
#define MCP23S17_DEFVALB 0x07               // Port B Default compare bits for interrupt change
#define MCP23S17_INTCONA 0x08               // Port A Interrupt on change Control register 
#define MCP23S17_INTCONB 0x09               // Port B Interrupt on change Control register 
#define MCP23S17_IOCON 0x0A                 // Port A/B I/O Expander Configuration Register
                                            // bit 7 BANK: Controls how the registers are addressed : 1 = Separated, 0 = Same bank.
                                            // bit 6 MIRROR: INT Pins Mirror bit : 1 = The INT pins are internally connected, 0 = The INT pins are not connected.
                                            // bit 5 SEQOP: Sequential Operation mode bit : 1 = Sequential operation disabled, 0 = Sequential operation enabled.
                                            // bit 4 DISSLW: Slew Rate control bit for SDA output : 1 = Slew rate disabled, 0 = Slew rate enabled
                                            // bit 3 HAEN: Hardware Address Enable bit (MCP23S17 only) : 1 = Enables the MCP23S17 address pins, 0 = Disables the MCP23S17 address pins.
                                            // bit 2 ODR: Configures the INT pin as an open-drain output: 1 = Open-drain output (overrides the INTPOL bit.), 0 = Active driver output (INTPOL bit sets the polarity.)
                                            // bit 1 INTPOL: This bit sets the polarity of the INT output pin : 1 = Active-high, 0 = Active-low
                                            // bit 0 Unimplemented: Read as ?0?
#define MCP23S17_GPPUA 0x0C                 // Port A pull-up resistors Configuration Register : 1 = Pull-up enabled, 0 = Pull-up disabled
#define MCP23S17_GPPUB 0x0D                 // Port B pull-up resistors Configuration Register : 1 = Pull-up enabled, 0 = Pull-up disabled
#define MCP23S17_INTFA 0x0E                 // Port A Interrupt Flag Register
#define MCP23S17_INTFB 0x0F                 // Port B Interrupt Flag Register
#define MCP23S17_INTCAPA 0x10               // Port A Interrupt Captured value Register
#define MCP23S17_INTCAPB 0x11               // Port B Interrupt Captured value Register
#define MCP23S17_GPIOA 0x12                 // Port A General purpose I/O register
#define MCP23S17_GPIOB 0x13                 // Port B General purpose I/O register
#define MCP23S17_OLATA 0x14                 // Port A Output Latch register
#define MCP23S17_OLATB 0x15                 // Port B Output Latch register

/**
 * @brief This function writes to the register Port of the SPI I/O expander.
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
int8_t MCP23S17_Write_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_Write_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t data);
#endif

/**
 * @brief This function read from the register Port of the SPI I/O expander.
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
int8_t MCP23S17_Read_Register_SPI1 (uint8_t device_address, uint8_t register_address, uint8_t *data);
#ifdef SPI2_AVAILABLE
    int8_t MCP23S17_Read_Register_SPI2 (uint8_t device_address, uint8_t register_address, uint8_t *data);
#endif

#endif	/* MCP23S17_H */

