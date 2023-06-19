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

This module contains the implementation all functions for used with CCP2 module
 
- Frequency counter via CCP2 

*******************************************************************************/

#include <CCP2.h>

// CCP2CaptureTask Implementation
uint16_t CCP2CaptureTask (void) {
    
    // Time Capture from CPP2
    uint16_t uiCaptureTime = 0;
    
    // If the CCP2 interrupt flag is set
    if(PIR2bits.CCP2IF && PIE2bits.CCP2IE) {
        
        // Capture the timer value
        uiCaptureTime = ((uint16_t)CCPR2H << 8) | CCPR2L; 
        
        // Reset CCP2 Registers
        CCP2ResetRegisters();
        
        // Clear the timer registers
        Timer3ResetRegisters();
        
        //Clear interrupt flag
        CCP2ClearInterrupt();
    }
    
    return uiCaptureTime;
}

// CCP2_init Implementation
void CCP2_init (void) {
    
    // Configure CCP2 in capture mode and 1:1 prescaler for timer
    CCP2_init_capture(CCPx_TIMER_PRESCALE_1);
}

// getFrequencyFromTimer Implementation
volatile double getFrequencyFromTimer(uint16_t capture_time, uint8_t capture_mode, uint8_t timer_prescale) {
    
    //double dTOsc = 4 / (SYSTEM_CLOCK / 1000000);        // TCycle period
    double dTOsc = 0.0833;
    double dTSignal = 0;                                // TSignal period
    uint8_t byTimerRatio = 0;                           // Timer Prescaler ratio
    uint8_t byCaptureSamples = 0;                       // Capture Samples
    double dDivider = 0;                                // TOsc divider by 
                                                        // Timer Prescaler ratio and Capture Samples
    double dTimerCount = 0;                             // Count TOsc for Timer
    
    // Select capture mode
    switch (capture_mode) {
        
        case CCPx_CAPTURE_1_FALL:
        case CCPx_CAPTURE_1_RISE:
            byCaptureSamples = 1;
            break;
        case CCPx_CAPTURE_4_RISE:
            byCaptureSamples = 4;
            break;
        case CCPx_CAPTURE_16_RISE:
            byCaptureSamples = 16;
            break;
    }
    
    // Select Timer ratio
    switch (timer_prescale) {
        
        case CCPx_TIMER_PRESCALE_1:
            byTimerRatio = 1;
            break;
        case CCPx_TIMER_PRESCALE_2:
            byTimerRatio = 2;
            break;
        case CCPx_TIMER_PRESCALE_4:
            byTimerRatio = 4;
            break;
        case CCPx_TIMER_PRESCALE_8:
            byTimerRatio = 8;
            break;
    }
    
    // Calcs divider
    dDivider = byTimerRatio / byCaptureSamples;
    // Calcs TOsc in Timer count
    dTimerCount = (double)capture_time * dDivider;
    // Calcs period
    dTSignal = dTimerCount * dTOsc;
    // Return frequncy
    return 1000 / dTSignal;
    
}
