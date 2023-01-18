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

This module contains local definition for supports close functionalities 
of main application.

*******************************************************************************/

#include <system.h>

// SPI libraries
#include <SPILib.h>
#include <MCP42XXX.h>
#include <MCP425X.h>
#include <MCP23S08.h>
#include <LCD44780_MCP23S08.h>

// I2C libraries
#include <I2CLib.h>
#include <PCF8574.h>
#include <pic18f4550.h>

// CCP2 libraries
#include <CCP2.h>

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

// Current capture value from CCP2.
// Needs for calculate frequency
static uint16_t uiCaptureCCP2 = 0x00;
static uint16_t uiLastCaptureCCP2 = 0x00;

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
    #if defined(CCP2_INTERRUPT)
        // CCP2 interrupt routine
        uiLastCaptureCCP2 = CCP2CaptureTask();
    #endif
}

// Clear CDC USB Out data buffer 
void ClearCDCUSBDataWriteBuffer(void) {
    memset(writeBuffer, 0, CDC_DATA_IN_EP_SIZE);
}

// Clear CDC USB In data buffer 
void ClearCDCUSBDataReadBuffer(void) {
    memset(readBuffer, 0, CDC_DATA_OUT_EP_SIZE);
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
                // Setup of MSSP as SPI Master
                StartUpSPIConfig();
                // Setup of the SPI MCP23S08 that driver an LCD 44780 Hitachi compatible
                StartUpSPI16x2LCD();
                // Setup of the SPI MCP23S08 used as GPIO Extender
                StartUpSPIGPIOExtender();
                // Setup of CCP configuration of CCP2
                StartUpCCP2Config();

                break;

            case SYSTEM_STATE_COMPLETED_INIT:
                // Put info message on LCD
                SimpleMessageSPI16x2LCD(caSystemReadyMessage);

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
    
    // Disable ADC
    ADCON0bits.ADON = 0x0;
    // Set All possible ports/line AN0 to AN12 to digital
    ADCON1bits.PCFG = 0xF;
    
	// Set USB LED activity to output and put low
 	LED_STATUS_USB_TRIS = 0x0;
    LED_STATUS_USB_PORT = 0x0;
    
    // Set General Purpose LEDs to output and put low
    LED_GP1_TRIS = 0x0;
    LED_GP1_PORT = 0x0;
    LED_GP2_TRIS = 0x0;
    LED_GP2_PORT = 0x0;
    
    // Set CS1,CS2 and CS3 for SPI as output
    SPI1_CS1_LINE_TRIS = 0x0;
    SPI1_CS2_LINE_TRIS = 0x0;
    SPI1_CS3_LINE_TRIS = 0x0;
    // Set Set CS1,CS2 and CS3 disable
    SPI1_CS1_LINE_PORT = 0x1;
    SPI1_CS2_LINE_PORT = 0x1;
    SPI1_CS3_LINE_PORT = 0x1;
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

// Setup of CCP configuration of CCP2
void StartUpCCP2Config(void) {
    
    // Configure CCP2 module in capture mode
    CCP2_init();
}

// Setup of the SPI MCP23S08 that driver an
// LCD 44780 Hitachi compatible
void StartUpSPI16x2LCD(void) {
    
    // Initialization of MCP28S03 at hardware address 0x01
    // used with the library for driver an LCD 44780 Hitachi
    // compatible in 4 bit mode
    LCD44780_MCP23S08_lcd_init_SPI1(0x01);
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
    
    
    // Initialization of MCP28S03 at hardware address 0x00
    SPI1_CS3_LINE_PORT = 0x0;
    MCP23S08_Write_Register_SPI1(0x00, MCP23S08_IOCON, 0x0A);
    // Deselect Extender device
    SPI1_CS3_LINE_PORT = 0x1;
        
    __delay_us(50);
        
    // Select Extender device
    SPI1_CS3_LINE_PORT = 0x0;
    MCP23S08_Write_Register_SPI1(0x00, MCP23S08_IODIR, 0x00);
    // Deselect Extender device
    SPI1_CS3_LINE_PORT = 0x1;

    __delay_us(50);

    // Select Extender device
    SPI1_CS3_LINE_PORT = 0x0;
    MCP23S08_Write_Register_SPI1(0x00, MCP23S08_OLAT, 0x00);
    // Deselect Extender device
    SPI1_CS3_LINE_PORT = 0x1;
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
        uint16_t uiIDCommand = 0x00;
        uint8_t byValue = 0;
        uint8_t iNumBytesRead = 0;
        uint8_t iNumBytesToWrite = 0;
        
        int16_t iCaptureDelta = 0;
        
        iNumBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
        
        // Controls if we receive at least one or more bytes.
        if (iNumBytesRead > 0) {
            
            BlinkLEDGP1();
            
            //for (i = 0; i < iNumBytesRead; i++) {
                
                uiIDCommand = (uint16_t)(readBuffer[0] + (readBuffer[1] << 8));
                byValue = readBuffer[2];

                LCD44780_MCP23S08_lcd_clear_SPI1();
                LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
                LCD44780_MCP23S08_send_message_SPI1("ID : ");
                LCD44780_MCP23S08_write_integer_SPI1((int16_t)uiIDCommand, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
                LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_SECOND_LINE);
                LCD44780_MCP23S08_send_message_SPI1("Value : ");
                LCD44780_MCP23S08_write_integer_SPI1((int16_t)byValue, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
            //}
        
        }
        
        // Controls if last CCP capture has changed from previous
        if (uiCaptureCCP2 != uiLastCaptureCCP2) {
            
            iCaptureDelta = (int16_t)uiCaptureCCP2 - (int16_t)uiLastCaptureCCP2;
            
            // Controls if is threshold gap
            if (abs(iCaptureDelta) > CCP2_CAPTURE_THRESHOLD_GAP) {
                    
                // Save new value
                uiCaptureCCP2 = uiLastCaptureCCP2;
            
                BlinkLEDGP2();
            
            
            
                LCD44780_MCP23S08_lcd_clear_SPI1();
                LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
                LCD44780_MCP23S08_send_message_SPI1("Freq : ");
                LCD44780_MCP23S08_write_integer_SPI1((int16_t)uiCaptureCCP2, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
            
            
                // Clear write buffer
                ClearCDCUSBDataWriteBuffer();
                
                uiIDCommand = VCO_1_RSP_FREQUENCY;
                
                writeBuffer[0] = (uint8_t)(uiIDCommand & 0x00FF);
                writeBuffer[1] = (uint8_t)(uiIDCommand >> 8);
                
                writeBuffer[2] = (uint8_t)(uiCaptureCCP2 & 0x00FF);
                writeBuffer[3] = (uint8_t)(uiCaptureCCP2 >> 8);
                
                iNumBytesToWrite = 4;
                
                putUSBUSART(writeBuffer, iNumBytesToWrite);
            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /******************************************************
    // ONLY FOR TEST !!!
    
    volatile uint8_t uiIndex1SPI = 0;
    volatile uint8_t uiIndex2SPI = 0;
    volatile uint8_t uiIndex3SPI = 0;
    
    volatile uint8_t iuValuePot1 = 0;
    volatile uint16_t iuValuePot2 = 0;
    
    volatile uint8_t uiBitsMask;
    
    
    
    
    
        LATDbits.LATD1 = 0x1;
        
        // Wait for one second
        __delay_ms(1000);
        
        // ************ MCP42XXX
        
        // Select Pot device
        SPI1_CS1_LINE_PORT = 0x0;
        
        if (uiIndex1SPI >= 4) {
            iuValuePot1 = 255;
            MCP42XXX_Pot0_Write_Data_SPI1(iuValuePot1);
            uiIndex1SPI = 0;
        } else {
            iuValuePot1 = 64 * uiIndex1SPI;
            MCP42XXX_Pot0_Write_Data_SPI1(iuValuePot1);
            uiIndex1SPI ++;
        }
        
        // Deselect Pot device
        SPI1_CS1_LINE_PORT = 0x1;
        
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
        LCD44780_MCP23S08_send_message_SPI1("VPot 1 : ");
        LCD44780_MCP23S08_write_integer_SPI1(iuValuePot1, 0, LCD44780_MCP23S08_ZERO_CLEANING_ON);
        
        // ************ MCP425X
        
        // Select Pot device
        SPI1_CS2_LINE_PORT = 0x0;
        
        if (uiIndex2SPI > 4) {
            uiIndex2SPI = 0;
        } else {
            iuValuePot2 = 64 * uiIndex2SPI;
            MCP425X_Pot1_Write_Data_SPI1(iuValuePot2);
            uiIndex2SPI ++;
        }
                
        // Deselect Pot device
        SPI1_CS2_LINE_PORT = 0x1;
        
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_SECOND_LINE);
        LCD44780_MCP23S08_send_message_SPI1("VPot 2 : ");
        LCD44780_MCP23S08_write_integer_SPI1((int16_t)iuValuePot2, 0, LCD44780_MCP23S08_ZERO_CLEANING_ON);
        
        // ************ MCP23S08
        
        uiBitsMask = 0x10;
        
        for (uiIndex3SPI = 0; uiIndex3SPI < 5; uiIndex3SPI++) {
            // Wait for half second
            __delay_ms(500);
            
            // Select Pot device
            SPI1_CS3_LINE_PORT = 0x0;
            MCP23S08_Write_Register_SPI1(0x00, MCP23S08_OLAT, uiBitsMask & 0xF0);
            // Deselect Pot device
            SPI1_CS3_LINE_PORT = 0x1;
        
            // Left shift
            uiBitsMask = (uint8_t)(uiBitsMask << 1);
        }
                
        // ********** End SPI Session **********
        
        LATDbits.LATD1 = 0x0;
        
        // Wait for 2 second
        __delay_ms(2000);
        // Invert RD0 level
        LATDbits.LATD0 = ~LATDbits.LATD0;
        
        *********************************************/
        
        
}
