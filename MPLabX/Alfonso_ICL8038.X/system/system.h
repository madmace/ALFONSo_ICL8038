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
#define CMD_LCD_DEBUG_MODE

// LEDs definition for USB operations

// LED USB Connection activity
#define LED_STATUS_USB_TRIS TRISDbits.RD0
#define LED_STATUS_USB_PORT LATDbits.LATD0

// LEDs General Purpose activity
#define LED_GP1_TRIS TRISAbits.RA0
#define LED_GP1_PORT LATAbits.LATA0
#define LED_GP2_TRIS TRISDbits.RD2
#define LED_GP2_PORT LATDbits.LATD2

// LEDs USB functions
#define BlinkLEDUSB() { LED_STATUS_USB_PORT = 0x1; __delay_ms(100); LED_STATUS_USB_PORT = 0x0; }

// LEDs General Purpose functions
#define BlinkLEDGP1() { LED_GP1_PORT = 0x1; __delay_ms(100); LED_GP1_PORT = 0x0; }
#define BlinkLEDGP2() { LED_GP2_PORT = 0x1; __delay_ms(100); LED_GP2_PORT = 0x0; }

// CS Lines (not included in SPI Library)

// CS Line for MCP23S08 driving Hitachi 44780 LDC
#define LCD44780_MCP23S08_CS_LINE_TRIS TRISAbits.RA1
#define LCD44780_MCP23S08_CS_LINE_PORT LATAbits.LATA1

// CS for MCP23S17s GPIO Expander
#define MCP23S17_CS_LINE_TRIS TRISAbits.RA2
#define MCP23S17_CS_LINE_PORT LATAbits.LATA2

// CS for MCP42XXX Digital Potentiometer VCO 1
#define MCP42XXX_VCO1_CS_LINE_TRIS TRISAbits.RA3
#define MCP42XXX_VCO1_CS_LINE_PORT LATAbits.LATA3

// CS for MCP42XXX Digital Potentiometer VCO 2
#define MCP42XXX_VCO2_CS_LINE_TRIS TRISAbits.RA5
#define MCP42XXX_VCO2_CS_LINE_PORT LATAbits.LATA5

// CS for MCP425X Digital Potentiometer VCO 1 & 2
#define MCP425X_VCO12_CS_LINE_TRIS TRISEbits.RE0
#define MCP425X_VCO12_CS_LINE_PORT LATEbits.LATE0

// Address for MCP23S08 driving Hitachi 44780 LDC
#define LCD44780_MCP23S08_ADDRESS 0x00

// Address for first MCP23S17 GPIO Expander
#define MCP23S17_EXP_1_ADDRESS 0x00
// Address for second MCP23S17 GPIO Expander
#define MCP23S17_EXP_2_ADDRESS 0x01

// MCP23S17 GPIO Expander VCO control ports
// A single MCP23S17 commands two VCO (High and Low)
#define HIGH_VCO_SEL_VLFO 0x8000                // VLFO Selector for High VCO (GPB7 on MCP23S17)
#define HIGH_VCO_SEL_LFO 0x4000                 // LFO Selector for High VCO (GPB6 on MCP23S17)
#define HIGH_VCO_SEL_VCO 0x2000                 // VCO Selector for High VCO (GPB5 on MCP23S17)
#define HIGH_VCO_SEL_HVCO 0x1000                // HVCO Selector for High VCO (GPB4 on MCP23S17)
#define LOW_VCO_SEL_VLFO 0x800                  // VLFO Selector for Low VCO (GPB3 on MCP23S17)
#define LOW_VCO_SEL_LFO 0x400                   // LFO Selector for Low VCO (GPB2 on MCP23S17)
#define LOW_VCO_SEL_VCO 0x200                   // VCO Selector for Low VCO (GPB1 on MCP23S17)
#define LOW_VCO_SEL_HVCO 0x100                  // HVCO Selector for Low VCO (GPB0 on MCP23S17)
#define HIGH_VCO_SEL_SQR_EN 0x80                // Square Enable for High VCO (GPA7 on MCP23S17)
#define HIGH_VCO_SEL_SIN_EN 0x40                // Sine Enable for High VCO (GPA6 on MCP23S17)
#define HIGH_VCO_SEL_TRG_EN 0x20                // Triangle Enable for High VCO (GPA5 on MCP23S17)
#define HIGH_VCO_SEL_ENABLE 0x10                // Enable for High VCO (GPA4 on MCP23S17)
#define LOW_VCO_SEL_SQR_EN 0x08                 // Square Enable for Low VCO (GPA3 on MCP23S17)
#define LOW_VCO_SEL_SIN_EN 0x04                 // Sine Enable for Low VCO (GPA2 on MCP23S17)
#define LOW_VCO_SEL_TRG_EN 0x02                 // Triangle Enable for Low VCO (GPA1 on MCP23S17)
#define LOW_VCO_SEL_ENABLE 0x01                 // Enable for Low VCO (GPA0 on MCP23S17)

// Default at BOR for MCP23S17 GPIO Expander VCO control ports
// HIGH_VCO_SEL_VLFO 0x0                        // VLFO Selector for High VCO (GPB7 on MCP23S17)
// HIGH_VCO_SEL_LFO 0x0                         // LFO Selector for High VCO (GPB6 on MCP23S17)
// HIGH_VCO_SEL_VCO 0x1                         // VCO Selector for High VCO (GPB5 on MCP23S17)
// HIGH_VCO_SEL_HVCO 0x0                        // HVCO Selector for High VCO (GPB4 on MCP23S17)
// LOW_VCO_SEL_VLFO 0x0                         // VLFO Selector for Low VCO (GPB3 on MCP23S17)
// LOW_VCO_SEL_LFO 0x0                          // LFO Selector for Low VCO (GPB2 on MCP23S17)
// LOW_VCO_SEL_VCO 0x1                          // VCO Selector for Low VCO (GPB1 on MCP23S17)
// LOW_VCO_SEL_HVCO 0x0                         // HVCO Selector for Low VCO (GPB0 on MCP23S17)
// HIGH_VCO_SEL_SQR_EN 0x0                      // Square Enable for High VCO (GPA7 on MCP23S17)
// HIGH_VCO_SEL_SIN_EN 0x0                      // Sine Enable for High VCO (GPA6 on MCP23S17)
// HIGH_VCO_SEL_TRG_EN 0x0                      // Triangle Enable for High VCO (GPA5 on MCP23S17)
// HIGH_VCO_SEL_ENABLE 0x0                      // Enable for High VCO (GPA4 on MCP23S17)
// LOW_VCO_SEL_SQR_EN 0x0                       // Square Enable for Low VCO (GPA3 on MCP23S17)
// LOW_VCO_SEL_SIN_EN 0x0                       // Sine Enable for Low VCO (GPA2 on MCP23S17)
// LOW_VCO_SEL_TRG_EN 0x0                       // Triangle Enable for Low VCO (GPA1 on MCP23S17)
// LOW_VCO_SEL_ENABLE 0x0                       // Enable for Low VCO (GPA0 on MCP23S17)
#define MCP23S17_EXP_VCO_DEFAULT 0x2200

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
        uint8_t byVCOID;                    // VCO ID
        bool    bVCOEnable;                 // VCO Enabled
        uint8_t byFreqSelector;             // VCO Range frequency selector
        uint8_t byFrequency;                // VCO Steps frequency coarse
        uint8_t byFreqFine;                 // VCO Steps frequency fine
        uint8_t byDutyCycle;                // VCO Steps Duty Cycle
        bool    bSineWaveEnable;            // VCO Sine wave Enable
        bool    bSquareWaveEnable;          // VCO Square wave Enable
        bool    bTriangleWaveEnable;        // VCO Triangle wave Enable
        
        uint16_t uiAnalogVCOFreq;           // VCO Real frequency
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

// Sets the single bit determined by the input mask
/**
 * @brief Internal service function.
 * Sets the single bit determined by the input mask
 *
 * @param uiVCO VCO ID where set or reset bit
 * @param uiMask Mask for selecting single bit
 * @param bValue Bit value to set
 *
 * @return void
 * 
 */
void setSingleBitToMCP23S17Expander(uint8_t uiVCO, uint16_t uiMask, bool bValue);

/**
 * @brief Clear all the VCO States
 *
 * @param void
 *
 * @return void
 * 
 */
void ClearAllVCOStates (void);

/**
 * @brief Enable or Disable a VCO
 *
 * @param uiVCO VCO ID of VCO to enable or disable
 * @param bValue If true enable the VCO, false disable it
 *
 * @return void
 * 
 */
void enableVCO(uint8_t uiVCO, bool bValue);

/**
 * @brief Deselect All VCO Frequencies Ranges
 *
 * @param uiVCO VCO ID where deselect all ranges
 *
 * @return void
 * 
 */
void deselectAllVCORanges (uint8_t uiVCO);

/**
 * @brief Select or Deselect a VCO frequency range
 *
 * @param uiVCO VCO ID where select or deselect specific range
 * @param uiRange Range to select or deselect
 *        Takes this constants :
 *        HVCO_REQ_FREQ_SELECTOR is High VCO
 *        VCO_REQ_FREQ_SELECTOR is Low VCO
 *        LFO_REQ_FREQ_SELECTOR is high LFO
 *        VLFO_REQ_FREQ_SELECTOR is low LFO
 * @param bValue If true select the range, false deselect it
 *
 * @return void
 * 
 */
void selectVCORange(uint8_t uiVCO, uint8_t uiRange, bool bValue);

/**
 * @brief Enable or Disable a VCO Sine Harmonic
 *
 * @param uiVCO VCO ID where enable or disable harmonic
 * @param bValue If true enable the harmonic, false disable it
 *
 * @return void
 * 
 */
void selectVCOSineHarmonic(uint8_t uiVCO, bool bValue);

/**
 * @brief Enable or Disable a VCO Square Harmonic
 *
 * @param uiVCO VCO ID where enable or disable harmonic
 * @param bValue If true enable the harmonic, false disable it
 *
 * @return void
 * 
 */
void selectVCOSquareHarmonic(uint8_t uiVCO, bool bValue);

/**
 * @brief Enable or Disable a VCO Triangle Harmonic
 *
 * @param uiVCO VCO ID where enable or disable harmonic
 * @param bValue If true enable the harmonic, false disable it
 *
 * @return void
 * 
 */
void selectVCOTriangleHarmonic(uint8_t uiVCO, bool bValue);

/**
 * @brief Set coarse Frequency for a VCO
 *
 * @param uiVCO VCO ID where set frequency
 * @param uiValue Frequency value to set to coarse pot
 *
 * @return void
 * 
 */
void setVCOFrequencyCoarse(uint8_t uiVCO, uint8_t uiValue);

/**
 * @brief Set fine Frequency for a VCO
 *
 * @param uiVCO VCO ID where set frequency
 * @param uiValue Frequency value to set to fine pot
 *
 * @return void
 * 
 */
void setVCOFrequencyFine(uint8_t uiVCO, uint8_t uiValue);

/**
 * @brief Set duty cycle Frequency for a VCO
 *
 * @param uiVCO VCO ID where set duty cycle
 * @param uiValue duty cycle value to set
 *
 * @return void
 * 
 */
void setVCODutyCycle(uint8_t uiVCO, uint8_t uiValue);

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
 * @brief Setup of all resources for configure Frequency Counter
 *        To do at startup.
 *
 * @param void
 *
 * @return void
 * 
 */
void StartUpFreqCounterConfig(void);

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
 * @param bIsLenght If true the next lenght will be displayed
 * @param bIsValue  If true the next value will be displayed
 * @param byLenght  Lenght in bytes of value
 * @param byValue   Relative value if present
 *
 * @return void
 * 
 * This function is only for debugging of received commads.
 */
#if defined(CMD_LCD_DEBUG_MODE)
    void DebugCommandSPI16x2LCD(const char *cmd, bool bIsLenght, bool bIsValue, uint8_t byLenght, uint8_t byValue);
#endif
    
    /**
 * @brief Put a 16bit int values on first and second line of LCD 44780 Hitachi
 *        by SPI MCP23S08
 *
 * @param iValue1   16bit int value to put on display at first row
 * @param iValue2   16bit int value to put on display at second row
 *
 * @return void
 * 
 * This function is only for debugging of received commads.
 */
#if defined(CMD_LCD_DEBUG_MODE)
    void DebugIntSPI16x2LCD(int16_t iValue1, int16_t iValue2);
#endif

/**
 * @brief Takes a current value of VCO Frequency updated by the ISR
 *        and controls if variance are in tollerance gap.
 *
 * @param byVCOID           VCO ID of Frequency value
 *
 * @return bool             Return True if the capture is taken and wrote
 *                          to input variable
 * 
 */
bool updateVCOFrequency(uint8_t byVCOID);

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
uint8_t packResponseFrequency16(uint8_t *buffer, uint16_t uiValue, uint8_t byVCOID);

/**
 * @brief Prepare the 32bit Frequency value to be send to client
 *        by the response protocol
 *
 * @param buffer          Pointer by Reference buffer to write
 * 
 * @param ulValue         Frequency value to pack
 * 
 * @param byVCOID         VCO ID of Frequency value
 *
 * @return bool           Return True if the capture is taken and wrote
 *                        to input variable
 * 
 */
uint8_t packResponseFrequency32(uint8_t *buffer, uint32_t ulValue, uint8_t byVCOID);

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


#if defined(CMD_LCD_DEBUG_MODE)
    
#endif

#endif	/* SYSTEM_H */
