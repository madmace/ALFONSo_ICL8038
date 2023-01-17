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

This Header contains SPI Library functions.

Attention !!
Not include CS operations. It will be managed out functions provided.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef SPILIB_H
#define	SPILIB_H

#include <xc.h>
#include "globals.h"

//SPI Lib MSSP configuration
#define SPI_SLAVE_SS_ENABLED 0x04   //0b0100xxxx
#define SPI_SLAVE_SS_DISABLED 0x05  //0b0101xxxx
#define SPI_TIMER_OUT_CLK 0x03      //0bxxxx0011
#define SPI_CLK_OSC_64 0x02         //0bxxxx0010
#define SPI_CLK_OSC_16 0x01         //0bxxxx0001
#define SPI_CLK_OSC_4 0x00          //0bxxxx0000

// SPI Lib constants
#define SPI_MASTER_DEVICE 0x01
#define SPI_SLAVE_DEVICE 0x02

#define SPI_MODE_0 0x00
#define SPI_MODE_1 0x01
#define SPI_MODE_2 0x02
#define SPI_MODE_3 0x03

/**
 * This function opens the SPI module for communication.
 * In particular it sets the device type either to Master or Slave.
 *
 * @param device_type Device Type [SPI_MASTER_DEVICE, SPI_SLAVE_DEVICE]
 *
 * @return void
 *
 * @warning This function should be called only after having set the module with the right 
 * baudrate and mode.
 * 
 */
void SPI1_open (uint8_t device_type);
#ifdef SPI2_AVAILABLE
    void SPI2_open (uint8_t device_type);
#endif

    
/**
 * This function closes the SPI module.
 *
 * @param void
 *
 * @return void
 * 
 */
void SPI1_close (void);
#ifdef SPI2_AVAILABLE
    void SPI2_close (void);
#endif

    
/**
 * This function sets the communication baudrate.
 * It should be called before SPI_open function.
 *
 * @param baudrate Baudrate [SPI_CLK_OSC_64, SPI_CLK_OSC_16, SPI_CLK_OSC_4, SPI_TIMER_OUT_CLK]
 *
 * @return void
 *
 * @warning This function should be called before SPI_open and for Master device Only. 
 * 
 */
void SPI1_baudrate (uint8_t baudrate);
#ifdef SPI2_AVAILABLE
    void SPI2_baudrate (uint8_t baudrate);
#endif


/**
 * This function sets the communication mode.
 * It should be called before SPI_open function.
 *
 * @param communication_mode Operational mode [SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3]
 *
 * @return void
 *
 * @warning This function should be called before SPI_open for both MAster and Slave devices. 
 * 
 */
void SPI1_mode (uint8_t communication_mode);
#ifdef SPI2_AVAILABLE
    void SPI2_mode (uint8_t communication_mode);
#endif

    
/**
 * This function writes a single byte on the bus.
 *
 * @param byte_to_send Byte to send [0..255]
 *
 * @return error Communication error 
 *               0: The byte has been properly written
 *               -1: Communication error
 * 
 */
int8_t SPI1_write_byte (uint8_t byte_to_send);
#ifdef SPI2_AVAILABLE
    int8_t SPI2_write_byte (uint8_t byte_to_send);
#endif

     
/**
 * This function reads a single byte from the bus
 *
 * @param void
 *
 * @return byte Value read from the input buffer. 
 * 
 * @warning The function is a blocking one. It waits for 8 bits to be sent out.
 * 
 */
uint8_t SPI1_read_byte (void);
#ifdef SPI2_AVAILABLE
    uint8_t SPI2_read_byte (void);
#endif


/**
 * This macro checks if the data is ready. It can be used for TX mode only.
 *
 * @param void
 *
 * @return Bit BF 0: Receive buffer is not full
 *                1: Receive buffer is full
 */
#define SPI1_check_data_ready() (SSPSTATbits.BF)
#ifdef SPI2_AVAILABLE
    #define SPI2_check_data_ready() (SSP2STATbits.BF)
#endif

/**
 * This macro checks if any communication .
 *
 * @param void
 *
 * @return Bit WCOL 0: No communication collision. 
 *                  1: Communication collision dedected.
 */
#define SPI1_check_bus_collision() (SSPCON1bits.WCOL)
#ifdef SPI2_AVAILABLE
    #define SPI2_check_bus_collision() (SSP2CON1bits.WCOL)
#endif

/**
 * This macro checks if any buffer overflow occured.
 *
 * @param void
 *
 * @return Bit WCOL 0: No overflow. 
 *                  1: Buffer Overflow dedected.
 */ 
#define SPI1_check_buffer_overflow() (SSPCON1bits.SSPOV)
#ifdef SPI2_AVAILABLE
    #define SPI2_check_buffer_overflow() (SSP2CON1bits.SSPOV)
#endif
    
/**
 * This macro checks TX transition is over. It check the interrupt flag as reference.
 *
 * @param void
 *
 * @return Bit Interrupt Flag   0: Communication in progress
 *                              1: Communication completed
 */
#define SPI1_is_TX_over() (PIR1bits.SSPIF)
#ifdef SPI2_AVAILABLE
    #define SPI2_is_TX_over() (PIR3bits.SSP2IF)
#endif

#endif	/* SPILIB_H */

