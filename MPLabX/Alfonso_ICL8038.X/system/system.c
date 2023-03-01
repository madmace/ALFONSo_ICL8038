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
static volatile uint16_t uiLastCaptureCCP2 = 0x0000;

// States Table about VCO present
static volatile VCOState_t aVCOInfo[NUM_VCO_PRESENT];

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

// Clear all the VCO States
void ClearAllVCOStates(void) {
    
    uint8_t idx;
    
    for (idx = 0; idx < NUM_VCO_PRESENT; idx++) {
        aVCOInfo[idx].bVCOEnable = false;
        aVCOInfo[idx].byFreqSelector = 0x00;
        aVCOInfo[idx].byFrequency = 0x00;
        aVCOInfo[idx].byDutyCycle = 0x00;
        aVCOInfo[idx].bSineWaveEnable = false;
        aVCOInfo[idx].bSquareWaveEnable = false;
        aVCOInfo[idx].bTriangleWaveEnable = false;
        aVCOInfo[idx].uiAnalogFreqCCP = 0x0000;
    }
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
                
                // Clear all the VCO States
                ClearAllVCOStates();

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
    
    // CS for MCP42XXX Digital Potentiometer
    MCP42XXX_CS_LINE_TRIS = 0x0;        // Output
    MCP42XXX_CS_LINE_PORT = 0x1;        // CS Disabled
    
    // CS for MCP425X Digital Potentiometer
    MCP425X_CS_LINE_TRIS = 0x0;         // Output
    MCP425X_CS_LINE_PORT = 0x1;         // CS Disabled
    
    // CS for MCP23S17s GPIO Expander
    MCP23S17_CS_LINE_TRIS = 0x0;        // Output
    MCP23S17_CS_LINE_PORT = 0x1;        // CS Disabled
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
    // Set all 16 port to low
    MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_GPIOA_16, 0x0000);
    // Deselect Extender device
    MCP23S17_CS_LINE_PORT = 0x1;
    
    __delay_us(50);
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
#if defined(CMD_DEBUG_MODE)
    void DebugCommandSPI16x2LCD(const char *cmd, bool bIsValue, uint8_t byLenght, uint8_t byValue) {
        // Clear LCD
        LCD44780_MCP23S08_lcd_clear_SPI1();
        // Set cursor at first line
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_FIRST_LINE);
        // Disply command
        LCD44780_MCP23S08_send_message_SPI1("-> ");
        LCD44780_MCP23S08_send_message_SPI1(cmd);
        
        // Set cursor at second line
        LCD44780_MCP23S08_goto_line_SPI1(LCD44780_MCP23S08_SECOND_LINE);
        LCD44780_MCP23S08_send_message_SPI1("L:");
        LCD44780_MCP23S08_write_integer_SPI1((int16_t)byLenght, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
        
        // Controls if value present
        if (bIsValue) {
            LCD44780_MCP23S08_send_message_SPI1(" V:");
            LCD44780_MCP23S08_write_integer_SPI1((int16_t)byValue, 1, LCD44780_MCP23S08_ZERO_CLEANING_OFF);
        }
    }
#endif

// Takes a current value of capture of CCP2 updated by the ISR
// and controls if variance are in tollerance gap.
bool updateCCPCapture(volatile uint16_t *uiCapture) {
    
    int16_t iCaptureDelta = 0;
    bool bIsChanged = false;
    
    // Controls if last CCP capture has changed from previous
    if ((*uiCapture) != uiLastCaptureCCP2) {
        // Calcs difference
        //iCaptureDelta = (int16_t)(*uiCapture) - (int16_t)uiLastCaptureCCP2;
        // Controls if is threshold gap
        //if (abs(iCaptureDelta) > CCP2_CAPTURE_THRESHOLD_GAP) {

            // Save new value
            (*uiCapture) = uiLastCaptureCCP2;
            // Mark changed
            bIsChanged = true;
        //}
    }
    
    return bIsChanged;
}

// Prepare the 16bit Frequency value to be send to client
// by the response protocol
uint8_t packResponseFrequency(uint8_t *buffer, uint16_t uiValue, uint8_t byVCOID) {
    
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
        uint8_t byVCOID = 0;                        // Working VCO ID 
        uint8_t byIndex = 0;                        // Pointer Index to received buffer
        uint8_t byValue = 0;                        // First byte Value received
        uint8_t iNumBytesRead = 0;                  // Number of bytes read
        uint8_t iNumBytesToWrite = 0;               // Number of bytes written
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
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNC_REQ_ALL", false, iNumBytesRead, 0);
                        #endif
                        
                        // Set index at start of payload buffer
                        byIndex = START_REQ_PAYLOAD;
                        // Should be equal to all VCOs available
                        for(byCounter = 0; byCounter < NUM_VCO_PRESENT; byCounter++) {
                            
                            // Get VCO ID
                            byVCOID = readBuffer[byIndex];
                            byIndex++;
                            
                            // VCO Enable 
                            aVCOInfo[byVCOID].bVCOEnable = (bool)readBuffer[byIndex];
                            byIndex++;
                            // VCO Range frequency selector
                            aVCOInfo[byVCOID].byFreqSelector = readBuffer[byIndex];
                            byIndex++;
                            // VCO Frequency
                            aVCOInfo[byVCOID].byFrequency = readBuffer[byIndex];
                            byIndex++;
                            // VCO Duty Cycle
                            aVCOInfo[byVCOID].byDutyCycle = readBuffer[byIndex];
                            byIndex++;
                            // VCO Harmonic Sine
                            aVCOInfo[byVCOID].bSineWaveEnable = (bool)readBuffer[byIndex];
                            byIndex++;
                            // VCO Harmonic Square
                            aVCOInfo[byVCOID].bSquareWaveEnable = (bool)readBuffer[byIndex];
                            byIndex++;
                            // VCO Harmonic Triangle
                            aVCOInfo[byVCOID].bTriangleWaveEnable = (bool)readBuffer[byIndex];
                            byIndex++;                            
                        }
                        
                        // To do ....
                        // ADJUST 
                        // !!!
                        // !!!
                        
                        // Takes the current Frequency captured for VCO1
                        if (updateCCPCapture(&aVCOInfo[VCO1].uiAnalogFreqCCP)) {
                        
                            // Blink LED
                            BlinkLEDGP2();
                            // Packs the value
                            iNumBytesToWrite = packResponseFrequency(writeBuffer, aVCOInfo[VCO1].uiAnalogFreqCCP, VCO1);
                            // Send bytes to USB
                            putUSBUSART(writeBuffer, iNumBytesToWrite);
                        }                    
                    }
                    
                    break;

                case SYNC_REQ_VCO_1 :
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO1", false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                        
                    }
                    
                    break;
                    
                case SYNC_REQ_VCO_2:
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO2", false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                    }
                    
                    break;
                    
                case SYNC_REQ_VCO_3:
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO3", false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                    }
                    
                    break;
                    
                case SYNC_REQ_VCO_4:
                    // Control if right size
                    if (iNumBytesRead == SYNC_REQ_VCO_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("SYNCREQ_VCO4", false, iNumBytesRead, 0);
                        #endif

                        // To do ....
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable command
                    
                case VCO_1_REQ_ENABLE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_ENA", true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Enable 
                        aVCOInfo[VCO1].bVCOEnable = (bool)byValue;
                            
                        // To do ....
                        
                        // TEST !!!!
                        //byAux = (uint8_t)(byValue << 4);
                        byAux = (uint8_t)(byValue & 0x01);
                        // Select Extender device
                        MCP23S17_CS_LINE_PORT = 0x0;
                        // Set all 16 port to low
                        MCP23S17_Write_Word_Register_SPI1(MCP23S17_EXP_1_ADDRESS, MCP23S17_GPIOA_16, (uint16_t)byAux);
                        // Deselect Extender device
                        MCP23S17_CS_LINE_PORT = 0x1;
                        
                        // ****
                        
                        // Takes the current Frequency captured for VCO1
                        if (updateCCPCapture(&aVCOInfo[VCO1].uiAnalogFreqCCP)) {

                            // Blink LED
                            BlinkLEDGP2();
                            // Packs the value
                            iNumBytesToWrite = packResponseFrequency(writeBuffer, aVCOInfo[VCO1].uiAnalogFreqCCP, VCO1);
                            // Send bytes to USB
                            putUSBUSART(writeBuffer, iNumBytesToWrite);
                        }
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Frequency command
                
                case VCO_1_REQ_FREQUENCY:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_FREQUENCY_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_FREQ", true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Frequency 
                        aVCOInfo[VCO1].byFrequency = byValue;

                        // To do ....
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Duty cycle command
                
                case VCO_1_REQ_DUTY_CYCLE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_DUTY_CYCLE_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1REQ_DTY_CY", true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Duty Cycle 
                        aVCOInfo[VCO1].byDutyCycle = byValue;

                        // To do ....
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable Sine harmonica command    
                
                case VCO_1_REQ_ENABLE_SINE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_SINE_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1ENA_SINE", true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Sine Harmonic
                        aVCOInfo[VCO1].bSineWaveEnable = (bool)byValue;

                        // To do ....
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable Square harmonica command    
                
                case VCO_1_REQ_ENABLE_SQUARE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_SQUARE_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1ENA_SQUAR", true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Square Harmonic
                        aVCOInfo[VCO1].bSquareWaveEnable = (bool)byValue;
                        
                        // To do ....
                    }
                    
                    break;
                    
                // ************************************************
                // VCO Enable Triangle harmonica command    
                
                case VCO_1_REQ_ENABLE_TRIANGLE:
                    // Control if right size
                    if (iNumBytesRead == VCO_REQ_ENABLE_TRIANGLE_LEN) {
                        #if defined(CMD_DEBUG_MODE)
                            DebugCommandSPI16x2LCD("VCO1ENA_TRIAN", true, iNumBytesRead, byValue);
                        #endif

                        // Update VCO Triangle Harmonic
                        aVCOInfo[VCO1].bTriangleWaveEnable = (bool)byValue;
                        
                        // To do ....
                    }
                    
                    break;
                    
            }
        }
    }

    /* This handles device-to-host transaction(s).
     * Failure to call CDCTxService() periodically will prevent data from
     * being sent to the USB host.
     */
    CDCTxService();
}
