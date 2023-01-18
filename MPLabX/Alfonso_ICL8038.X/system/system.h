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

This Header contains local definition for supports close functionalities 
of main application.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdbool.h>

#include "globals.h"
#include "protocol.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

// Define Interrupt type
#if(__XC8_VERSION < 2000)
    #define INTERRUPT interrupt
#else
    #define INTERRUPT_HI __interrupt(high_priority)
    #define INTERRUPT_LOW __interrupt(low_priority)
#endif

// LEDs definition for USB operations

// LED USB Connection activity
#define LED_STATUS_USB_TRIS TRISDbits.RD0
#define LED_STATUS_USB_PORT LATDbits.LATD0

// LEDs General Purpose activity
#define LED_GP1_TRIS TRISDbits.RD1
#define LED_GP1_PORT LATDbits.LATD1
#define LED_GP2_TRIS TRISDbits.RD2
#define LED_GP2_PORT LATDbits.LATD2

// LEDs General Purpose functions
#define BlinkLEDGP1() { LED_GP1_PORT = 0x1; __delay_ms(100); LED_GP1_PORT = 0x0; }
#define BlinkLEDGP2() { LED_GP2_PORT = 0x1; __delay_ms(100); LED_GP2_PORT = 0x0; }

// CS Line (not included in SPI Library)
#define SPI1_CS1_LINE_TRIS TRISAbits.RA5
#define SPI1_CS1_LINE_PORT LATAbits.LATA5
#define SPI1_CS2_LINE_TRIS TRISAbits.RA0
#define SPI1_CS2_LINE_PORT LATAbits.LATA0
#define SPI1_CS3_LINE_TRIS TRISAbits.RA1
#define SPI1_CS3_LINE_PORT LATAbits.LATA1

// CS Line for Hitachi 44780 LDC
#define LCD44780_MCP23S08_CS_LINE_TRIS TRISAbits.RA1
#define LCD44780_MCP23S08_CS_LINE_PORT LATAbits.LATA1

// PCF8574 definitions
#define PCF8574_INTERNAL_ADDRESS USED_DEVICE_PCF8574

// System States defined for application state machine
typedef enum
{
    SYSTEM_STATE_START_INIT = 100,
    SYSTEM_STATE_COMPLETED_INIT,
    SYSTEM_STATE_USB_CONFIGURED,
    SYSTEM_STATE_USB_SUSPEND,
    SYSTEM_STATE_USB_RESUME,
    SYSTEM_STATE_USB_UNCONNECTED
} SYSTEM_STATE;

// Used in CCP2 Capture. If new frequency capture is
// this tollerance, no data will send to client
#define CCP2_CAPTURE_THRESHOLD_GAP 500

/***************************************
 * Local Utility functions
 ***************************************/

/**
 * Clear CDC USB Out data buffer 
 *
 * @param void
 *
 * @return void
 * 
 */
void ClearCDCUSBDataWriteBuffer (void);

/**
 * Clear CDC USB In data buffer 
 *
 * @param void
 *
 * @return void
 * 
 */
void ClearCDCUSBDataReadBuffer (void);

/***************************************
 * System functions
 ***************************************/

/**
 * Main system state machine function
 * This function is a facade function that care for
 * initial configure and next configuration of all micro GPIO about 
 * the state machine.
 *
 * @param state An value of SYSTEM_STATE enumerator. 
 *
 * @return void
 * 
 */
void ConfigSystemState(SYSTEM_STATE state);

/**
 * Set all GPIO port for initial start up.
 * Should be call at initial life of program or if we want
 * return to initial state again.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpIOPortsConfig(void);

/**
 * Setup of SPI configuration of MSSP
 * To do at startup.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpSPIConfig(void);

/**
 * Setup of CCP module for configure CCP2
 * as capture.
 * To do at startup.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpCCP2Config(void);

/**
 * Setup of the SPI MCP23S08 that driver an
 * LCD 44780 Hitachi compatible in 4 bit mode
 * To do at startup.
 * 
 * Perform initial presentation with
 * System Model
 * Actual Firmware Version
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpSPI16x2LCD(void);

/**
 * Setup of the SPI MCP23S08 8 GPIO Extender
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpSPIGPIOExtender(void);

/**
 * Update the system by current USB status.
 * Should be call in callback pump USB events function.
 *
 * @param void
 *
 * @return void
 * 
 */
void UpdateUSBStatus(void);

/**
 * Put a simple message on first line of LCD 44780 Hitachi
 * by SPI MCP23S08
 *
 * @param message Mesage to put on display
 *
 * @return void
 * 
 */
void SimpleMessageSPI16x2LCD(const char *message);

/**
 * Runs system level tasks that keep the system running
 *
 * PreCondition: System has been initialized with 
 * ConfigSystemState(SYSTEM_STATE_START_INIT)
 * and completed with
 * ConfigSystemState(SYSTEM_STATE_COMPLETED_INIT)
 *
 * @param void
 *
 * @return void
 *
 */
void MainSystemTasks(void);

#endif	/* SYSTEM_H */