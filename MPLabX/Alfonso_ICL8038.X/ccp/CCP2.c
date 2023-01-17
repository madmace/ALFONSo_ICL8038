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

#include <CCP2.h>

// CCP2CaptureTask Implementation
uint16_t CCP2CaptureTask (void) {
    
    // Time Capture from Timer
    uint16_t capture_time = 0;
    
    // If the CCP2 interrupt flag is set
    if(PIR2bits.CCP2IF && PIE2bits.CCP2IE) {
        
        // Capture the timer value
        capture_time = ((uint16_t)CCPR2H << 8) | CCPR2L; 
        
        // Reset CCP2 Registers
        CCPR2H = 0;
        CCPR2L = 0;
        
        // Clear the timer registers
        TMR3H = 0x00;
        TMR3L = 0x00;
        
        //Clear interrupt flag
        CCP2ClearUSBInterrupt();
        
    }
    
    return capture_time;
}

// CCP2_init Implementation
void CCP2_init (void) {
    
    // Configure CCP2 in capture mode for every 16th rising edge
    CCP2_init_capture(CCPx_CAPTURE_16_RISE);
    
}

// getFrequencyFromTimer Implementation
double getFrequencyFromTimer(uint16_t capture_time, uint8_t capture_mode) {
    
    double TOsc = 4 / SYSTEM_CLOCK;         // TCycle period
    double TSignal = 0;                     // TSignal period
    
    // Select capture mode
    switch (capture_mode) {
        
        case CCPx_CAPTURE_1_FALL:
        case CCPx_CAPTURE_1_RISE:
            TSignal = capture_time * TOsc;
            break;
        case CCPx_CAPTURE_4_RISE:
            TSignal = (capture_time / 4) * TOsc;
            break;
        case CCPx_CAPTURE_16_RISE:
            TSignal = (capture_time / 16) * TOsc;
            break;
    }
    
    return (1 / TSignal) * 1000;
    
}
