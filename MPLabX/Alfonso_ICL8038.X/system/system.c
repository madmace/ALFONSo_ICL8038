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

This module contains local definition for supports close functionalities 
of main application.

*******************************************************************************/

#include <system.h>
#include <math.h>

// SPI libraries
#include <SPILib.h>
#include <MCP42XXX.h>
#include <MCP425X.h>
#include <MCP23S08.h>
#include <MCP23S17.h>
#include <LCD44780_MCP23S08.h>

// I2C libraries
#include <I2CLib.h>
#include <PCF8574.h>
#include <pic18f4550.h>

// Frequency Counter libraries
#include <Frequency.h>

// CCP2 libraries
#include <CCP2.h>

// Utilities libraries
#include <utilities.h>

// System Informations (system model and microcode version) (Max 16 chars)
const char* caWelcomeMessage = "  A.L.F.O.N.S.  ";
const char* caVersionMessage = "Ver. 0.0.1 Proto";

// System Messages (Max 16 chars)
const char* caSystemReadyMessage = "System Ready.";
const char* caUSBConnectedMessage = "USB Connected.";
const char* caUSBUnconnectedMessage = "USB Unconnected.";

// Buffers for send and receive bytes
static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

// Current calculated frequency
static volatile uint16_t uiLastFreqCapture = 0x0;
// Number Timer0 overflows into Timer1
static volatile uint16_t uiTMR0OverflowCount = 0x0;

// States Table about VCO present
static volatile VCOState_t aVCOInfo[NUM_VCO_PRESENT];

// GPIO Register state of MCP23S17 16-bit I/O Expander
static volatile uint16_t uiMCP23S17Expander1 = MCP23S17_EXP_VCO_DEFAULT;        //Holds settings for VCO1 and VCO2
static volatile uint16_t uiMCP23S17Expander2 = MCP23S17_EXP_VCO_DEFAULT;        //Holds settings for VCO3 and VCO4

// Interrupt function implementation for USB in High priority
void INTERRUPT_HI SYS_InterruptHigh(void)
{
    #if defined(USB_INTERRUPT)
        // USB interrupt routine
        USBDeviceTasks();
    #endif
}

void INTERRUPT_LOW SYS_InterruptLow(void)
{
    #if defined(TMR0_INTERRUPT)
        // If the Timer0 interrupt flag is set
        if(INTCONbits.TMR0IF && INTCONbits.TMR0IE) {
            
            // Count overflow
            uiTMR0OverflowCount++;
            // Clear Timer0
            Timer0ResetRegisters();       
            // Clear interrupt
            Timer0ClearInterrupt();
        }
    #endif

    #if defined(TMR1_INTERRUPT)
        // If the Timer1 interrupt flag is set
        if(PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
            
            // Set start counting from 32768 fror Timer1
            Timer1Set32KRegisters();
            // Calculate Frequency
            uiLastFreqCapture = (uint16_t)uiTMR0OverflowCount * 256 + (uint16_t)TMR0;
            
            // Clear Timer0
            Timer0ResetRegisters();
            // Reset overflow counter for Timer0
            uiTMR0OverflowCount = 0x0;
            
            // Clear interrupt
            Timer1ClearInterrupt();
        }
    #endif
    
    //#if defined(CCP2_INTERRUPT)
        // CCP2 interrupt routine
        //ulLastCaptureCCP2 = CCP2CaptureTask(uiTMR3OverflowCount);
        
        
        
        
        //BlinkLEDGP3();
        
        
        // Reset Timer3 counter overflow
        //uiTMR3OverflowCount = 0x0;
        
        //Clear interrupt flag
        //CCP2ClearInterrupt();
        
    //#endif
}


// Clear CDC USB Out data buffer 
void ClearCDCUSBDataWriteBuffer(void) {
    memset(writeBuffer, 0, CDC_DATA_IN_EP_SIZE);
}

// Clear CDC USB In data buffer 
void ClearCDCUSBDataReadBuffer(void) {
    memset(readBuffer, 0, CDC_DATA_OUT_EP_SIZE);
}

// Clear all the VCO States
void ClearAllVCOStates(void) {
    
    uint8_t idx;
    
    for (idx = 0; idx < NUM_VCO_PRESENT; idx++) {
        aVCOInfo[idx].bVCOEnable = false;
        aVCOInfo[idx].byFreqSelector = 0x00;
        aVCOInfo[idx].byFrequency = 0x00;
        aVCOInfo[idx].byFreqFine = 0x00;
        aVCOInfo[idx].byDutyCycle = 0x00;
        aVCOInfo[idx].bSineWaveEnable = false;
        aVCOInfo[idx].bSquareWaveEnable = false;
        aVCOInfo[idx].bTriangleWaveEnable = false;
        aVCOInfo[idx].bInvalideAnalogFreq = false;
        aVCOInfo[idx].uiAnalogFreqCCP = 0x0000;
    }
}

// Deselect All VCO Frequencies Ranges
void deselectAllVCORanges (uint8_t uiVCO) {
    
    // Mask
    uint16_t uiMask = 0x0000;
    // Complementary Mask
    uint16_t uicMask = 0x0000;
    
    // Select VCO setting 
    switch(uiVCO) {
        
        case VCO1:
        case VCO3:
            // VCO 1 or VCO 3
            // Mask
            uiMask = HIGH_VCO_SEL_VLFO + HIGH_VCO_SEL_LFO + HIGH_VCO_SEL_VCO + HIGH_VCO_SEL_HVCO;
            
            break;
            
        case VCO2:
        case VCO4:
            // VCO 2 or VCO 4
            // Mask
            uiMask = LOW_VCO_SEL_VLFO + LOW_VCO_SEL_LFO + LOW_VCO_SEL_VCO + LOW_VCO_SEL_HVCO;
            
            break;
    }
    
    // Complementary Mask
    uicMask = ~uiMask;
    
    // Select Extender device
    MCP23S17_CS_LINE_PORT = 0x0;
    
    // Select for VCOs
    switch(uiVCO) {
        
        case VCO1:
        case VCO2:
            /// VCO 1 or VCO 2
            // Clears bits
            uiMCP23S17Expander1 &= uicMask;
            // Set all 16 port to low
            MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_GPIOA_16, uiMCP23S17Expander1);
            
            break;
            
        case VCO3:
        case VCO4:
            /// VCO 3 or VCO 4
            // Clears bits
            uiMCP23S17Expander2 &= uicMask;
            // Set all 16 port to low
            MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_2_ADDRESS, MCP23S17_GPIOA_16, uiMCP23S17Expander2);
            
            break;
    }
    
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;
}

// Select or Deselect a VCO frequency range
void selectVCORange(uint8_t uiVCO, uint8_t uiRange, bool bValue) {
    
    // Mask
    uint16_t uiMask = 0x0000;
    
    // Select VCO setting
    switch(uiVCO) {
        
        case VCO1:
        case VCO3:
            // VCO 1 or VCO 3
            switch(uiRange) {
                
                case HVCO_REQ_FREQ_SELECTOR:
                    // HVCO
                    uiMask = HIGH_VCO_SEL_HVCO;
                            
                    break;
                    
                case VCO_REQ_FREQ_SELECTOR:
                    // VCO
                    uiMask = HIGH_VCO_SEL_VCO;
                            
                    break;
                    
                case LFO_REQ_FREQ_SELECTOR:
                    // LFO
                    uiMask = HIGH_VCO_SEL_LFO;
                            
                    break;
                    
                case VLFO_REQ_FREQ_SELECTOR:
                    // VLFO
                    uiMask = HIGH_VCO_SEL_VLFO;
                            
                    break;
            }
            
            break;
            
        case VCO2:
        case VCO4:
            // VCO 2 or VCO 4
            
            switch(uiRange) {
                
                case HVCO_REQ_FREQ_SELECTOR:
                    // HVCO
                    uiMask = LOW_VCO_SEL_HVCO;
                            
                    break;
                    
                case VCO_REQ_FREQ_SELECTOR:
                    // VCO
                    uiMask = LOW_VCO_SEL_VCO;
                            
                    break;
                    
                case LFO_REQ_FREQ_SELECTOR:
                    // LFO
                    uiMask = LOW_VCO_SEL_LFO;
                            
                    break;
                    
                case VLFO_REQ_FREQ_SELECTOR:
                    // VLFO
                    uiMask = LOW_VCO_SEL_VLFO;
                            
                    break;
            }
            
            break;
    }
    
    // Sets the single bit determined by the input mask
    setSingleBitToMCP23S17Expander(uiVCO, uiMask, bValue);
    
    /*
    // Select VCO range for CCP2
    switch(uiRange) {
        
        case HVCO_REQ_FREQ_SELECTOR:
            // HVCO
            // Configure CCP2 module in capture mode for HVCO range
            CCP2_HVCO_init();
                            
            break;
                    
        case VCO_REQ_FREQ_SELECTOR:
            // VCO
            // Configure CCP2 module in capture mode for VCO range
            CCP2_VCO_init();

            break;
                    
        case LFO_REQ_FREQ_SELECTOR:
            // LFO
            // Configure CCP2 module in capture mode for LFO range
            CCP2_LFO_init();

            break;

        case VLFO_REQ_FREQ_SELECTOR:
            // VLFO
            // Configure CCP2 module in capture mode for VLFO range
            CCP2_VLFO_init();

            break;
    }
    */
}

// Enable or Disable a VCO Sine Harmonics
void selectVCOSineHarmonic(uint8_t uiVCO, bool bValue) {
    
    // Mask
    uint16_t uiMask = 0x0000;
    
    // Select VCO Harmonics setting
    switch(uiVCO) {
        
        case VCO1:
        case VCO3:
            // Sine
            uiMask = HIGH_VCO_SEL_SIN_EN;

            break;
            
        case VCO2:
        case VCO4:
            // Sine
            uiMask = LOW_VCO_SEL_SIN_EN;

            break;
    }
    
    // Sets the single bit determined by the input mask
    setSingleBitToMCP23S17Expander(uiVCO, uiMask, bValue);
}

// Enable or Disable a VCO Square Harmonics
void selectVCOSquareHarmonic(uint8_t uiVCO, bool bValue) {
    
    // Mask
    uint16_t uiMask = 0x0000;
    
    // Select VCO Harmonics setting
    switch(uiVCO) {
        
        case VCO1:
        case VCO3:
            // Square
            uiMask = HIGH_VCO_SEL_SQR_EN;

            break;
            
        case VCO2:
        case VCO4:
            // Square
            uiMask = LOW_VCO_SEL_SQR_EN;

            break;
    }
    
    // Sets the single bit determined by the input mask
    setSingleBitToMCP23S17Expander(uiVCO, uiMask, bValue);
}

// Enable or Disable a VCO Triangle Harmonics
void selectVCOTriangleHarmonic(uint8_t uiVCO, bool bValue) {
    
    // Mask
    uint16_t uiMask = 0x0000;
    
    // Select VCO Harmonics setting
    switch(uiVCO) {
            
        case VCO1:
        case VCO3:
            // Triangle
            uiMask = HIGH_VCO_SEL_TRG_EN;

            break;
            
        case VCO2:
        case VCO4:
            // Triangle
            uiMask = LOW_VCO_SEL_TRG_EN;

            break;
    }
    
    // Sets the single bit determined by the input mask
    setSingleBitToMCP23S17Expander(uiVCO, uiMask, bValue);
}

// Set coarse Frequency for a VCO
void setVCOFrequencyCoarse(uint8_t uiVCO, uint8_t uiValue) {
    
    // Select VCO Frequency settings
    switch(uiVCO) {
        
        case VCO1:
            
            // Select Pot VCO 1
            MCP42XXX_VCO1_CS_LINE_PORT = 0x0;
            // Set Byte to Pot for coarse tune
            MCP42XXX_Pot0_Write_Data_SPI1(uiValue);        
            // Deselect Pot VCO 1
            MCP42XXX_VCO1_CS_LINE_PORT = 0x1;
            
            break;
            
        case VCO2:
            
            /*
            // Select Pot VCO 2
            MCP42XXX_VCO2_CS_LINE_PORT = 0x0;
            // Set Byte to Pot for coarse tune
            MCP42XXX_Pot0_Write_Data_SPI1(uiValue);        
            // Deselect Pot VCO 2
            MCP42XXX_VCO2_CS_LINE_PORT = 0x1;
            */
            
            break;
            
        case VCO3:
        case VCO4:
            
            break;
    }
}

// Set fine Frequency for a VCO
void setVCOFrequencyFine(uint8_t uiVCO, uint8_t uiValue) {
    
    // Select VCO Frequency settings
    switch(uiVCO) {
        
        case VCO1:
            
            // Select Pot VCO 1
            MCP42XXX_VCO1_CS_LINE_PORT = 0x0;
            // Set Byte to Pot for fine tune
            MCP42XXX_Pot1_Write_Data_SPI1(uiValue);        
            // Deselect Pot VCO 1
            MCP42XXX_VCO1_CS_LINE_PORT = 0x1;
            
            break;
            
        case VCO2:
            
            /*
            // Select Pot VCO 2
            MCP42XXX_VCO2_CS_LINE_PORT = 0x0;
            // Set Byte to Pot for fine tune
            MCP42XXX_Pot1_Write_Data_SPI1(uiValue);        
            // Deselect Pot VCO 1
            MCP42XXX_VCO2_CS_LINE_PORT = 0x1;
            */
            
            break;
            
        case VCO3:
        case VCO4:
            
            break;
            
    }
}

// Set duty cycle Frequency for a VCO
void setVCODutyCycle(uint8_t uiVCO, uint8_t uiValue) {
    
    // Select VCO Frequency settings
    switch(uiVCO) {
        
        case VCO1:
            
            // Select Duty Pot VCO 1
            MCP425X_VCO12_CS_LINE_PORT = 0x0;
            // Set Byte to Pot for duty cycle
            //MCP425X_Pot0_Write_Data_SPI1(uiValue);
            MCP42XXX_Pot0_Write_Data_SPI1(uiValue);
            // Deselect Pot VCO 1
            MCP425X_VCO12_CS_LINE_PORT = 0x1;
            
            break;
            
        case VCO2:
            
            /*
            // Select Duty Pot VCO 1
            MCP425X_VCO12_CS_LINE_PORT = 0x0;
            // Set Byte to Pot for duty cycle
            MCP425X_Pot1_Write_Data_SPI1(uiValue);        
            // Deselect Pot VCO 1
            MCP425X_VCO12_CS_LINE_PORT = 0x1;
            */
            
            break;
            
        case VCO3:
        case VCO4:
            
            break;
    }
}


// Enable or Disable a VCO
void enableVCO(uint8_t uiVCO, bool bValue) {
    
    // Mask
    uint16_t uiMask = 0x0000;
    
    // Enable VCO
    // VCO 1 or VCO 3
    switch(uiVCO) {
        
        case VCO1:
        case VCO3:
            uiMask = HIGH_VCO_SEL_ENABLE;

            break;
            
        case VCO2:
        case VCO4:
            uiMask = LOW_VCO_SEL_ENABLE;

            break;
    }
    
    // Sets the single bit determined by the input mask
    setSingleBitToMCP23S17Expander(uiVCO, uiMask, bValue);
}

// Sets the single bit determined by the input mask
void setSingleBitToMCP23S17Expander(uint8_t uiVCO, uint16_t uiMask, bool bValue) {
    
    // Select Extender device
    MCP23S17_CS_LINE_PORT = 0x0;
    
    // Select VCO setting 
    switch(uiVCO) {
        
        case VCO1:
        case VCO2:
            /// VCO 1 or VCO 2
            
            // Set single port
            set_int16_by_bit_weight(&uiMCP23S17Expander1, uiMask, bValue);
            // Set all 16 port
            MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_GPIOA_16, uiMCP23S17Expander1);
            
            break;
            
        case VCO3:
        case VCO4:
            /// VCO 3 or VCO 4
            
            // Set single port
            set_int16_by_bit_weight(&uiMCP23S17Expander2, uiMask, bValue);
            // Set all 16 port
            //MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_2_ADDRESS, MCP23S17_GPIOA_16, uiMCP23S17Expander2);
            
            break;
    }
    
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;
}

// Main system state machine function
void ConfigSystemState(SYSTEM_STATE state)
{
    // Last State occurred
    static uint8_t uiLastSysState = 0;
    
    // Controls if same of last state
    if (state != uiLastSysState) {        
    
        // Controls state machine
        switch(state)
        {
            case SYSTEM_STATE_START_INIT:
                // Setup of initial GPIO configuration
                StartUpIOPortsConfig();
                
                // USART Debugging console printf() if enabled
                #ifdef ENABLE_USART_PRINTF
                    // Enable USART on printf()
                    serial_init_printf();
                #endif

                // Setup of MSSP as SPI Master
                StartUpSPIConfig();
                // Setup of the SPI MCP23S08 that driver an LCD 44780 Hitachi compatible
                StartUpSPI16x2LCD();
                // Setup of the SPI MCP23S08 used as GPIO Extender
                StartUpSPIGPIOExtender();
                // Setup of Frequency Counter
                StartUpFreqCounterConfig();
                
                // Clear all the VCO States
                ClearAllVCOStates();

                break;

            case SYSTEM_STATE_COMPLETED_INIT:
                // Put info message on LCD
                SimpleMessageSPI16x2LCD(caSystemReadyMessage);
                
                //printf("Init completed.\n");

                break;

            case SYSTEM_STATE_USB_CONFIGURED:
                // Put info message on LCD
                SimpleMessageSPI16x2LCD(caUSBConnectedMessage);

                break;

            case SYSTEM_STATE_USB_SUSPEND:
                break;

            case SYSTEM_STATE_USB_RESUME:
                break;
                
            case SYSTEM_STATE_USB_UNCONNECTED:
                // Put info message on LCD
                SimpleMessageSPI16x2LCD(caUSBUnconnectedMessage);
                
                break;
        }
        
        // Update last state
        uiLastSysState = state;
    }
}

// Apply the initial ports configuration
void StartUpIOPortsConfig(void) {
    
    // Disable A/D converter module
    ADCON0 = 0x00;
    // Set All possible ports/line AN0 to AN12 to digital
    ADCON1 = 0xFF;
    
	// Set USB LED activity to output and put low
 	LED_STATUS_USB_TRIS = 0x0;
    LED_STATUS_USB_PORT = 0x0;
    
    // Set General Purpose LEDs to output and put low
    LED_GP1_TRIS = 0x0;
    LED_GP1_PORT = 0x0;
    LED_GP2_TRIS = 0x0;
    LED_GP2_PORT = 0x0;
    
    // CS for MCP42XXX Digital Potentiometer VCO 1
    MCP42XXX_VCO1_CS_LINE_TRIS = 0x0;       // Output
    MCP42XXX_VCO1_CS_LINE_PORT = 0x1;       // CS Disabled
    
    // CS for MCP42XXX Digital Potentiometer VCO 2
    MCP42XXX_VCO2_CS_LINE_TRIS = 0x0;       // Output
    MCP42XXX_VCO2_CS_LINE_PORT = 0x1;       // CS Disabled
    
    // CS for MCP425X Digital Potentiometer VCO 1 & 2
    MCP425X_VCO12_CS_LINE_TRIS = 0x0;       // Output
    MCP425X_VCO12_CS_LINE_PORT = 0x1;       // CS Disabled
    
    // CS for MCP23S17s GPIO Expander
    MCP23S17_CS_LINE_TRIS = 0x0;            // Output
    MCP23S17_CS_LINE_PORT = 0x1;            // CS Disabled
    
    // Alive LEDs !
    BlinkLEDUSB();
    BlinkLEDGP1();
    BlinkLEDGP2();
}

// Setup of SPI configuration of MSSP
void StartUpSPIConfig(void) {
    
    // Configure SPI1 in middle fast mode
    SPI1_baudrate(SPI_CLK_OSC_16);
    // Configure to 1 1 mode
    SPI1_mode(SPI_MODE_3);
    // Configure MSSP as master
    SPI1_open(SPI_MASTER_DEVICE);
}

// Initial Setup of all resources for configure Frequency Counter
void StartUpFreqCounterConfig(void) {
    
    // Configure 16bit Timer1 as RTC
    init_Timer1();
    // Configure 8bit Timer0 as external clock
    init_Timer0();
}

// Setup of the SPI MCP23S08 that driver an
// LCD 44780 Hitachi compatible
void StartUpSPI16x2LCD(void) {
    
    // Initialization of MCP28S03 at hardware address 0x01
    // used with the library for driver an LCD 44780 Hitachi
    // compatible in 4 bit mode
    LCD44780_MCP23S08_lcd_init_SPI1(LCD44780_MCP23S08_ADDRESS);
    // Set cursor at first line
    LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
    // Print the welcome message
    LCD44780_MCP23S08_send_message_SPI1(caWelcomeMessage);
    // Set cursor at second line
    LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_SECOND_LINE);
    // Print the microcode version
    LCD44780_MCP23S08_send_message_SPI1(caVersionMessage);
    // 3 Seconds for gig :)
    __delay_ms(3000);
    // Clear LCD
    LCD44780_MCP23S08_lcd_clear_SPI1();
}

// Setup of the SPI MCP23S08 that is used as
// GPIO Extender
void StartUpSPIGPIOExtender(void) {
    //
    // Initialization of First MCP28S17 I/O Extender at hardware address 0x00
    //
    
    // Select Extender device
    MCP23S17_CS_LINE_PORT = 0x0;
    // Initialization Extender device
    MCP23S17_init_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_16BIT);
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;
        
    __delay_us(50);
        
    // Select Extender device
    MCP23S17_CS_LINE_PORT = 0x0;
    // Set sll 16 port as outputs
    MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_IODIRA_16, 0x0000);
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;

    __delay_us(50);

    // Select Extender device
    MCP23S17_CS_LINE_PORT = 0x0;
    // Set default ports for VCO 1 and VCO2
    MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_GPIOA_16, MCP23S17_EXP_VCO_DEFAULT);
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;
    
    // Not presents now...
    
    /*
    // Select Extender device
    MCP23S17_CS_LINE_PORT = 0x0;
    // Set default ports for VCO 3 and VCO4
    MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_2_ADDRESS, MCP23S17_GPIOA_16, MCP23S17_EXP_VCO_DEFAULT);
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;
    
    __delay_us(50);
    */
}

// Update the system by current USB status
void UpdateUSBStatus(void)
{
    static uint16_t ledCount = 0;

    // Controls if suspended
    if(USBIsDeviceSuspended() == true)
    {
        LED_STATUS_USB_PORT = 0x0;
        return;
    }

    // Which is USB state ?
    switch(USBGetDeviceState())
    {
        case CONFIGURED_STATE:
            /* We are configured.  Blink fast.
             * On for 75ms, off for 75ms, then reset/repeat. */
            if(ledCount == 1)
            {
                LED_STATUS_USB_PORT = 0x1;
            }
            else if(ledCount == 75)
            {
                LED_STATUS_USB_PORT = 0x0;
            }
            else if(ledCount > 150)
            {
                ledCount = 0;
            }
            break;

        default:
            /* We aren't configured yet, but we aren't suspended so let's blink with
             * a slow pulse. On for 50ms, then off for 950ms, then reset/repeat. */
            if(ledCount == 1)
            {
                LED_STATUS_USB_PORT = 0x1;
            }
            else if(ledCount == 50)
            {
                LED_STATUS_USB_PORT = 0x0;
            }
            else if(ledCount > 950)
            {
                ledCount = 0;
            }
            break;
    }

    // Increment the millisecond counter.
    ledCount++;
}

// Put a simple message on first line of LCD 44780 Hitachi
// by SPI MCP23S08
void SimpleMessageSPI16x2LCD(const char *message) {
    // Clear LCD
    LCD44780_MCP23S08_lcd_clear_SPI1();
    // Set cursor at first line
    LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
    // Print the welcome message
    LCD44780_MCP23S08_send_message_SPI1(message);
}

// Put a command and relative value on first line of LCD 44780 Hitachi
// by SPI MCP23S08
#if defined(CMD_LCD_DEBUG_MODE)
    void DebugCommandSPI16x2LCD(const char *cmd, bool bIsLenght, bool bIsValue, uint8_t byLenght, uint8_t byValue) {
        // Clear LCD
        LCD44780_MCP23S08_lcd_clear_SPI1();
        // Set cursor at first line
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
        // Disply command
        LCD44780_MCP23S08_send_message_SPI1("-> ");
        LCD44780_MCP23S08_send_message_SPI1(cmd);
        
        // Set cursor at second line
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_SECOND_LINE);
        
        // Controls if lenght present
        if (bIsLenght) {
            LCD44780_MCP23S08_send_message_SPI1("L:");
            LCD44780_MCP23S08_write_integer_SPI1((int16_t)byLenght, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
        }
        
        // Controls if value present
        if (bIsValue) {
            LCD44780_MCP23S08_send_message_SPI1(" V:");
            LCD44780_MCP23S08_write_integer_SPI1((int16_t)byValue, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
        }
    }
#endif

// Takes a current value of capture of CCP2 updated by the ISR
// and controls if variance are in tollerance gap.
bool updateCCPCapture(volatile uint16_t *uiFreqCapture) {
    
    //int16_t iCaptureDelta = 0;
    bool bIsChanged = false;
    
    // Controls if last CCP capture has changed from previous
    if ((*uiFreqCapture) != uiLastFreqCapture) {
        // Calcs difference
        //iCaptureDelta = (int16_t)(*uiCapture) - (int16_t)uiLastCaptureCCP2;
        // Controls if is threshold gap
        //if (abs(iCaptureDelta) > CCP2_CAPTURE_THRESHOLD_GAP) {

            // Save new value
            (*uiFreqCapture) = uiLastFreqCapture;
            // Mark changed
            bIsChanged = true;
        //}
    }
    
    return bIsChanged;
}

// Prepare the 16bit Frequency value to be send to client
// by the response protocol
uint8_t packResponseFrequency16(uint8_t *buffer, uint16_t uiValue, uint8_t byVCOID) {
    
    // Clear write buffer
    ClearCDCUSBDataWriteBuffer();
    
    uint16_t uiIDCommand = 0x00;
    
    // Set Response Frequency
    uiIDCommand = VCO_1_RSP_FREQUENCY;
    // First Low byte
    buffer[0] = (uint8_t)(uiIDCommand & 0x00FF);
    // High Low byte
    buffer[1] = (uint8_t)(uiIDCommand >> 8);
    // First Low byte value
    buffer[2] = (uint8_t)(uiValue & 0x00FF);
    // High Low byte value
    buffer[3] = (uint8_t)(uiValue >> 8);
        
    // Debug block
    /*
    #if defined(CMD_DEBUG_MODE)
        LCD44780_MCP23S08_lcd_clear_SPI1();
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
        LCD44780_MCP23S08_send_message_SPI1("Freq : ");
        LCD44780_MCP23S08_write_integer_SPI1((int16_t)uiValue, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
    #endif
     */
    
    // Four bytes copied.
    return 4;
}

// Prepare the 32bit Frequency value to be send to client
// by the response protocol
uint8_t packResponseFrequency32(uint8_t *buffer, uint32_t ulValue, uint8_t byVCOID) {
    
    // Clear write buffer
    ClearCDCUSBDataWriteBuffer();
    
    uint16_t uiIDCommand = 0x00;
    uint16_t uiLowValue = (uint16_t)(ulValue & 0x0000FFFF);
    uint16_t uiHighValue = (uint16_t)(ulValue >> 16);
    
    // Set Response Frequency
    uiIDCommand = VCO_1_RSP_FREQUENCY;
    // Command Low byte
    buffer[0] = (uint8_t)(uiIDCommand & 0x00FF);
    // Command High byte
    buffer[1] = (uint8_t)(uiIDCommand >> 8);
    // Low word Low byte value
    buffer[2] = (uint8_t)(uiLowValue & 0x00FF);
    // Low word High byte value
    buffer[3] = (uint8_t)(uiLowValue >> 8);
    // High word Low byte value
    buffer[4] = (uint8_t)(uiHighValue & 0x00FF);
    // High word High byte value
    buffer[5] = (uint8_t)(uiHighValue >> 8);
        
    // Debug block
    /*
    #if defined(CMD_LCD_DEBUG_MODE)
        LCD44780_MCP23S08_lcd_clear_SPI1();
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
        LCD44780_MCP23S08_send_message_SPI1("Freq : ");
        LCD44780_MCP23S08_write_integer_SPI1((int16_t)uiValue, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
    #endif
     */
    
    // Six bytes copied.
    return 6;
}

// Runs system level tasks that keep the system running
void MainSystemTasks(void) {
    
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if(USBGetDeviceState() < CONFIGURED_STATE)
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if(USBIsDeviceSuspended() == true)
    {
        // Update state
        ConfigSystemState(SYSTEM_STATE_USB_UNCONNECTED);
        
        return;
    }
        
    /* Check to see if there is a transmission in progress, if there isn't, then
     * we can see about performing an echo response to data received.
     */
    if(USBUSARTIsTxTrfReady() == true)
    {
        uint16_t uiIDCommand = 0x00;                // Request Command received
        uint8_t byBufferIndex = 0;                  // Pointer Index to received buffer
        uint8_t byValue = 0;                        // First byte Value received
        uint8_t iNumBytesRead = 0;                  // Number of bytes read
        uint8_t iNumBytesToWrite = 0;               // Number of bytes written
        uint8_t byVCOID = 0;                        // Working VCO ID
        uint8_t byVCOIndex = 0;                     // VCO Index
        uint8_t byCounter = 0;                      // Simple counter
        uint8_t byAux = 0;                          // Temporary byte variable
        
        // Reads bytes available from USB
        iNumBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
        // Controls if we receive at least one or more bytes.
        if (iNumBytesRead > 0) {
            
            // Blink LED
            BlinkLEDGP1();
            
            // Reading 2 byte command               
            uiIDCommand = (uint16_t)(readBuffer[CMD_PART_LOW_BYTE] + (readBuffer[CMD_PART_HIGH_BYTE] << 8));
            // Reading 1 byte value
            byValue = readBuffer[START_REQ_PAYLOAD];
            
            // Decode command
            switch(uiIDCommand) {

                // ************************************************
                // Synchronization command
                
                // Request all ALFONSo State
                case SYNC_REQ_ALL:
                    
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_ALL_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNC_REQ_ALL", true, false, iNumBytesRead, 0);
                        #endif
                        
                        // Set index at start of payload buffer
                        byBufferIndex = START_REQ_PAYLOAD;
                        // Should be equal to all VCOs available
                        //for(byVCOIndex = 0; byVCOIndex < NUM_VCO_PRESENT; byVCOIndex++) {
                        for(byVCOIndex = 0; byVCOIndex < 1; byVCOIndex++) {
                            
                            // Get VCO ID
                            aVCOInfo[byVCOIndex].byVCOID = readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Enable 
                            aVCOInfo[byVCOIndex].bVCOEnable = (bool)readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Range frequency selector
                            aVCOInfo[byVCOIndex].byFreqSelector = readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Frequency Coarse
                            aVCOInfo[byVCOIndex].byFrequency = readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Frequency Fine
                            aVCOInfo[byVCOIndex].byFreqFine = readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Duty Cycle
                            aVCOInfo[byVCOIndex].byDutyCycle = readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Harmonic Sine
                            aVCOInfo[byVCOIndex].bSineWaveEnable = (bool)readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Harmonic Square
                            aVCOInfo[byVCOIndex].bSquareWaveEnable = (bool)readBuffer[byBufferIndex];
                            byBufferIndex++;
                            // VCO Harmonic Triangle
                            aVCOInfo[byVCOIndex].bTriangleWaveEnable = (bool)readBuffer[byBufferIndex];
                            byBufferIndex++;
                            
                            // Synchronizing VCO
                            
                            // Set VCO Harmonics
                            selectVCOSineHarmonic(byVCOIndex, aVCOInfo[byVCOIndex].bSineWaveEnable);
                            selectVCOSquareHarmonic(byVCOIndex, aVCOInfo[byVCOIndex].bSquareWaveEnable);
                            selectVCOTriangleHarmonic(byVCOIndex, aVCOInfo[byVCOIndex].bTriangleWaveEnable);
                            // Set Frequency coarse for VCO
                            setVCOFrequencyCoarse(byVCOIndex, aVCOInfo[byVCOIndex].byFrequency);
                            // Set Frequency fine for VCO
                            setVCOFrequencyFine(byVCOIndex, aVCOInfo[byVCOIndex].byFreqFine);
                            // Set Duty Cycle for VCO
                            setVCODutyCycle(byVCOIndex, aVCOInfo[byVCOIndex].byDutyCycle);
                            // Disable all Frequency Selector for VCO                      
                            deselectAllVCORanges(byVCOIndex);
                            // Select Range for VCO
                            selectVCORange(byVCOIndex, aVCOInfo[byVCOIndex].byFreqSelector, true);                    
                            // Enable or Disable the VCO
                            enableVCO(byVCOIndex, aVCOInfo[byVCOIndex].bVCOEnable);
                            // Take new measure of frequency from CCP if VCO is enable
                            aVCOInfo[byVCOIndex].bInvalideAnalogFreq = aVCOInfo[byVCOIndex].bVCOEnable;
                            
                        }                   
                    }
                    
                    break;

                case SYNC_REQ_VCO_1 :
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO1", true, false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                        
                    }
                    
                    break;
                    
                case SYNC_REQ_VCO_2:
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO2", true, false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                    }
                    
                    break;
                    
                case SYNC_REQ_VCO_3:
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO3", true, false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                    }
                    
                    break;
                    
                case SYNC_REQ_VCO_4:
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO4", true, false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable command
                    
                case VCO_1_REQ_ENABLE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_ENA", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Enable 
                        aVCOInfo[VCO1].bVCOEnable = (bool)byValue;
                            
                        // Enable or Disable the VCO
                        enableVCO(VCO1, byValue);
                        
                        // Force to send new measure of frequency
                        aVCOInfo[VCO1].bInvalideAnalogFreq = true;
                        
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Frequency Range command
                    
                case VCO_1_REQ_FREQ_SELECTOR:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_FREQ_SELECTOR_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_FQSEL", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Frequency Range selector
                        aVCOInfo[VCO1].byFreqSelector = byValue;

                        // Disable all Frequency Selector for VCO 1                        
                        deselectAllVCORanges(VCO1);
                        // Select Range  for VCO 1 
                        selectVCORange(VCO1, byValue, true);
                        
                        // Force to send new measure of frequency
                        aVCOInfo[VCO1].bInvalideAnalogFreq = true;
                        
                    }
                    
                    break;
                    
                case VCO_2_REQ_FREQ_SELECTOR:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_FREQ_SELECTOR_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO2REQ_FQSEL", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Frequency Range selector
                        aVCOInfo[VCO2].byFreqSelector = byValue;

                        // Disable all Frequency Selector for VCO 2                        
                        deselectAllVCORanges(VCO2);
                        // Select Range  for VCO 1 
                        selectVCORange(VCO2, byValue, true);
                        
                        // Force to send new measure of frequency
                        aVCOInfo[VCO2].bInvalideAnalogFreq = true;
                        
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Frequency Coarse command
                
                case VCO_1_REQ_FREQCOARSE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_FREQCOARSE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_FRQCR", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Frequency Coarse
                        aVCOInfo[VCO1].byFrequency = byValue;

                        // Set coarse frequency for VCO 1
                        setVCOFrequencyCoarse(VCO1, byValue);
                        
                        // Force to send new measure of frequency
                        aVCOInfo[VCO1].bInvalideAnalogFreq = true;
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Frequency Fine command
                
                case VCO_1_REQ_FREQFINE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_FREQFINE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_FRQFN", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Frequency Fine
                        aVCOInfo[VCO1].byFreqFine = byValue;

                        // Set fine frequency for VCO 1
                        setVCOFrequencyFine(VCO1, byValue);
                        
                        // Force to send new measure of frequency
                        aVCOInfo[VCO1].bInvalideAnalogFreq = true;
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Duty cycle command
                
                case VCO_1_REQ_DUTY_CYCLE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_DUTY_CYCLE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_DTY_C", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Duty Cycle 
                        aVCOInfo[VCO1].byDutyCycle = byValue;

                        // Set Duty Cycle for VCO 1
                        setVCODutyCycle(VCO1, byValue);
                        
                        // Force to send new measure of frequency
                        aVCOInfo[VCO1].bInvalideAnalogFreq = true;
                        
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable Sine harmonica command    
                
                case VCO_1_REQ_ENABLE_SINE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_SINE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1ENA_SINE", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Sine Harmonic
                        aVCOInfo[VCO1].bSineWaveEnable = (bool)byValue;

                        // Enable or Disable a VCO Harmonic
                        selectVCOSineHarmonic(VCO1, byValue);
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable Square harmonica command    
                
                case VCO_1_REQ_ENABLE_SQUARE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_SQUARE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1ENA_SQUAR", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Square Harmonic
                        aVCOInfo[VCO1].bSquareWaveEnable = (bool)byValue;
                        
                        // Enable or Disable a VCO Harmonic
                        selectVCOSquareHarmonic(VCO1, byValue);
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable Triangle harmonica command    
                
                case VCO_1_REQ_ENABLE_TRIANGLE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_TRIANGLE_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1ENA_TRIAN", true, true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Triangle Harmonic
                        aVCOInfo[VCO1].bTriangleWaveEnable = (bool)byValue;
                        
                        // Enable or Disable a VCO Harmonic
                        selectVCOTriangleHarmonic(VCO1, byValue);
                    }
                    
                    break;
                    
                // ************************************************
                // Command for get current frequency on VCO 1    
                
                case VCO_1_REQ_FREQUENCY:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_FREQUENCY_LEN) {
                        #if defined(CMD_LCD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1GET_FREQ", true, true, iNumBytesRead, byValue);
                        #endif

                        // Force to send new measure of frequency
                        aVCOInfo[VCO1].bInvalideAnalogFreq = true;
                    }
                    
                    break;
                    
            }
            
            // Should be equal to all VCOs available
            for(byVCOIndex = 0; byVCOIndex < NUM_VCO_PRESENT; byVCOIndex++) {
                // Controls if VCO is enabled
                if (aVCOInfo[byVCOIndex].bVCOEnable) {
                    // Controls if force new measure of frequency from CCP
                    if (aVCOInfo[byVCOIndex].bInvalideAnalogFreq) {
                        // Takes the current Frequency captured for VCO
                        if (updateCCPCapture(&aVCOInfo[byVCOIndex].uiAnalogFreqCCP)) {

                            // Blink LED
                            BlinkLEDGP2();
                            // Packs the value
                            iNumBytesToWrite = packResponseFrequency16(writeBuffer, aVCOInfo[byVCOIndex].uiAnalogFreqCCP, byVCOIndex);
                            // Send bytes to USB
                            putUSBUSART(writeBuffer, iNumBytesToWrite);
                        }
                        // Reset force flag
                        aVCOInfo[byVCOIndex].bInvalideAnalogFreq = false;
                    }
                }
            }
        }
    }

    /* This handles device-to-host transaction(s).
     * Failure to call CDCTxService() periodically will prevent data from
     * being sent to the USB host.
     */
    CDCTxService();
}
