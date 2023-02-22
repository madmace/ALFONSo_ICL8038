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

// If uncomment define under the debug commands mode
#define CMD_DEBUG_MODE

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

// CS Lines (not included in SPI Library)

// CS for MCP42XXX Digital Potentiometer
#define MCP42XXX_CS_LINE_TRIS TRISAbits.RA5
#define MCP42XXX_CS_LINE_PORT LATAbits.LATA5

// CS for MCP425X Digital Potentiometer
#define MCP425X_CS_LINE_TRIS TRISAbits.RA0
#define MCP425X_CS_LINE_PORT LATAbits.LATA0

// CS for MCP23S08s GPIO Expander
#define MCP23S08_CS_LINE_TRIS TRISAbits.RA2
#define MCP23S08_CS_LINE_PORT LATAbits.LATA2

// CS Line for MCP23S08 driving Hitachi 44780 LDC
#define LCD44780_MCP23S08_CS_LINE_TRIS TRISAbits.RA1
#define LCD44780_MCP23S08_CS_LINE_PORT LATAbits.LATA1

// Address for MCP23S08 driving Hitachi 44780 LDC
#define LCD44780_MCP23S08_ADDRESS 0x00

// Address for first MCP23S08 GPIO Expander
#define MCP23S08_EXP_1_ADDRESS 0x00
// Address for seconf MCP23S08 GPIO Expander
#define MCP23S08_EXP_2_ADDRESS 0x01

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
#define CCP2_CAPTURE_THRESHOLD_GAP 10

// Structure for state of all VCO
typedef struct {
        bool    bVCOEnable;                 // VCO Enabled
        uint8_t byFreqSelector;             // VCO Range frequency selector
        uint8_t byFrequency;                // VCO Steps frequency
        uint8_t byDutyCycle;                // VCO Steps Duty Cycle
        bool    bSineWaveEnable;            // VCO Sine wave Enable
        bool    bSquareWaveEnable;          // VCO Square wave Enable
        bool    bTriangleWaveEnable;        // VCO Triangle wave Enable
        uint16_t uiAnalogFreqCCP;           // VCO Real frequency from CCP
} VCOState_t;

// Frequency Ranges Value
#define HVCO 1                              // High Frequencies range
#define VCO 2                               // Normal audible Frequencies range
#define LFO 3                               // Low audible Frequencies range
#define VLFO 4                              // Lowest Frequencies range

// Number of all VCO present
#define NUM_VCO_PRESENT 4

// VCO ID
#define VCO1 0
#define VCO2 1
#define VCO3 2
#define VCO4 3

/***************************************
 * Local Utility functions
 ***************************************/

/**
 * @brief Clear CDC USB Out data buffer 
 *
 * @param void
 *
 * @return void
 * 
 */
void ClearCDCUSBDataWriteBuffer (void);

/**
 * @brief Clear CDC USB In data buffer 
 *
 * @param void
 *
 * @return void
 * 
 */
void ClearCDCUSBDataReadBuffer (void);

/**
 * @brief Clear all the VCO States
 *
 * @param void
 *
 * @return void
 * 
 */
void ClearAllVCOStates (void);

/***************************************
 * System functions
 ***************************************/

/**
 * @brief Main system state machine function
 *        This function is a facade function that care for
 *        initial configure and next configuration of all micro GPIO about 
 *        the state machine.
 *
 * @param state An value of SYSTEM_STATE enumerator. 
 *
 * @return void
 * 
 */
void ConfigSystemState(SYSTEM_STATE state);

/**
 * @brief Set all GPIO port for initial start up.
 *        Should be call at initial life of program or if we want
 *        return to initial state again.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpIOPortsConfig(void);

/**
 * @brief Setup of SPI configuration of MSSP
 *        To do at startup.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpSPIConfig(void);

/**
 * @brief Setup of CCP module for configure CCP2
 *        as capture.
 *        To do at startup.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpCCP2Config(void);

/**
 * @brief Setup of the SPI MCP23S08 that driver an
 *        LCD 44780 Hitachi compatible in 4 bit mode
 *        To do at startup.
 * 
 *        Perform initial presentation with
 *        System Model
 *        Actual Firmware Version
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpSPI16x2LCD(void);

/**
 * @brief Setup of the SPI MCP23S08 8 GPIO Extender
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpSPIGPIOExtender(void);

/**
 * @brief Update the system by current USB status.
 *        Should be call in callback pump USB events function.
 *
 * @param void
 *
 * @return void
 * 
 */
void UpdateUSBStatus(void);

/**
 * @brief Put a simple message on first line of LCD 44780 Hitachi
 *        by SPI MCP23S08
 *
 * @param message Message to put on display
 *
 * @return void
 * 
 */
void SimpleMessageSPI16x2LCD(const char *message);

/**
 * @brief Put a command and relative value on first line of LCD 44780 Hitachi
 *        by SPI MCP23S08
 *
 * @param cmd       Command name to put on display
 * @param bIsValue  If true the next value will be displayed
 * @param byLenght  Lenght in bytes of value
 * @param byValue   Relative value if present
 *
 * @return void
 * 
 * This function is only for debugging of recevied commads.
 */
#if defined(CMD_DEBUG_MODE)
    void DebugCommandSPI16x2LCD(const char *cmd, bool bIsValue, uint8_t byLenght, uint8_t byValue);
#endif

/**
 * @brief Takes a current value of capture of CCP2 updated by the ISR
 *        and controls if variance are in tollerance gap.
 *
 * @param uiCapture       Pointer by Reference to 16bits output variable
 *
 * @return bool           Return True if the capture is taken and wrote
 *                        to input variable
 * 
 */
bool updateCCPCapture(volatile uint16_t *uiCapture);

/**
 * @brief Prepare the 16bit Frequency value to be send to client
 *        by the response protocol
 *
 * @param buffer          Pointer by Reference buffer to write
 * 
 * @param uiValue         Frequency value to pack
 * 
 * @param byVCOID         VCO ID of Frequency value
 *
 * @return bool           Return True if the capture is taken and wrote
 *                        to input variable
 * 
 */
uint8_t packResponseFrequency(uint8_t *buffer, uint16_t uiValue, uint8_t byVCOID);

/**
 * @brief Runs system level tasks that keep the system running
 *
 *        PreCondition: System has been initialized with 
 *        ConfigSystemState(SYSTEM_STATE_START_INIT)
 *        and completed with
 *        ConfigSystemState(SYSTEM_STATE_COMPLETED_INIT)
 *
 * @param void
 *
 * @return void
 *
 */
void MainSystemTasks(void);


#if defined(CMD_DEBUG_MODE)
    
#endif

#endif	/* SYSTEM_H */
