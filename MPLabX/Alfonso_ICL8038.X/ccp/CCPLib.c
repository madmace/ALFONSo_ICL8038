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

This module contains functionalities for use capture/compare in standard mode.

CCP2 is fixed to RC1.
#pragma config CCP2MX =	1   //OFF	CCP2 input/output is multiplexed with RC1

For capture :
Functions their fix the T3CCP2:T3CCP1: Timer3 and Timer1 to CCPx Enable bits as
Timer3 is the capture/compare clock source for CCP2
Timer1 is the capture/compare clock source for CCP1

*******************************************************************************/

#include "CCPLIb.h"

// CCP1_init_capture Implementation
void CCP1_init_capture (uint8_t sampling_type, uint8_t timer_prescale) {
    
    // Set up the CCP1 module for capture mode
	CCP1CON = 0x00 | sampling_type;
    // Clear the capture registers
	CCPR1H = 0; 
	CCPR1L = 0;
    
    // Set CCP1 as input
    CCP1_LINE_TRIS = 0x1;
        
    // Configure Timer1
    Timer1_config(timer_prescale);
    
    // Clear interrupts
    CCP1ClearInterrupt();
    // Enable interrupts
    CCP1EnableInterrupts();
}

// CCP2_init_capture Implementation
#ifdef CCP2_AVAILABLE
    void CCP2_init_capture (uint8_t sampling_type, uint8_t timer_prescale) {
        
        // Set up the CCP2 module for capture mode
        CCP2CON = 0x00 | sampling_type;
        
        // Clear the capture registers
        CCPR2H = 0; 
        CCPR2L = 0;
        
        // Set CCP1 as input
        CCP2_LINE_TRIS = 0x1;
        
        // Configure Timer3
        Timer3_config(timer_prescale);
        
        // Clear interrupts
        CCP2ClearInterrupt();
        // Enable interrupts
        CCP2EnableInterrupts();        
    }
#endif

// Timer1_config Implementation
void Timer1_config (uint8_t prescaler_value) {
    
    // Disable Timer1 overflow
    Timer1DisableInterrupts();
    // Enables register read/write of Timer1 in 16-bit operations
    T1CONbits.RD16 = 0x1;
    
    // Enable CCPX in Timer3
    Timer3_CCPX_enable();
    
    // Set prescaler ratio
    switch(prescaler_value) {
        
        case CCPx_TIMER_PRESCALE_1:
            // 1:1 Prescaler value
            T1CONbits.T1CKPS1 = 0x0;
            T1CONbits.T1CKPS0 = 0x0;
            break;
            
        case CCPx_TIMER_PRESCALE_2:
            // 1:2 Prescaler value
            T1CONbits.T1CKPS1 = 0x0;
            T1CONbits.T1CKPS0 = 0x1;
            break;
            
        case CCPx_TIMER_PRESCALE_4:
            // 1:4 Prescaler value
            T1CONbits.T1CKPS1 = 0x1;
            T1CONbits.T1CKPS0 = 0x0;
            break;
        
        case CCPx_TIMER_PRESCALE_8:
            // 1:8 Prescaler value
            T1CONbits.T1CKPS1 = 0x1;
            T1CONbits.T1CKPS0 = 0x1;
            break;
    }
    
    // Oscillator is shut off
    T1CONbits.T1OSCEN = 0x0;
    // Internal clock (FOSC/4)
    T1CONbits.TMR1CS = 0x0;
    // Enables Timer1
    T1CONbits.TMR1ON = 0x1;
    // Clear the timer registers
    TMR1H = 0x00;
    TMR1L = 0x00;
}

// Timer3_config Implementation
void Timer3_config (uint8_t prescaler_value) {
    
    // Disable Timer3 overflow
    Timer3DisableInterrupts();
    // Enables register read/write of Timer3 in 16-bit operations
    T3CONbits.RD16 = 0x1;
    
    // Enable CCPX in Timer3
    Timer3_CCPX_enable();
    
    // Set prescaler ratio
    switch(prescaler_value) {
        
        case CCPx_TIMER_PRESCALE_1:
            // 1:1 Prescaler value
            T3CONbits.T3CKPS1 = 0x0;
            T3CONbits.T3CKPS0 = 0x0;
            break;
            
        case CCPx_TIMER_PRESCALE_2:
            // 1:2 Prescaler value
            T3CONbits.T3CKPS1 = 0x0;
            T3CONbits.T3CKPS0 = 0x1;
            break;
            
        case CCPx_TIMER_PRESCALE_4:
            // 1:4 Prescaler value
            T3CONbits.T3CKPS1 = 0x1;
            T3CONbits.T3CKPS0 = 0x0;
            break;
        
        case CCPx_TIMER_PRESCALE_8:
            // 1:8 Prescaler value
            T3CONbits.T3CKPS1 = 0x1;
            T3CONbits.T3CKPS0 = 0x1;
            break;
    }
    
    // Internal clock (FOSC/4)
    T3CONbits.TMR3CS = 0x0;
    // Enables Timer3
    T3CONbits.TMR3ON = 0x1;
    // Clear the timer registers
    TMR3H = 0x00;
    TMR3L = 0x00;
}

// Timer3_CCPX_enable Implementation
void Timer3_CCPX_enable() {
    
    // Timer3 is the capture/compare clock source for CCP2;
    // Timer1 is the capture/compare clock source for CCP1
    T3CONbits.T3CCP2 = 0x0;
    T3CONbits.T3CCP1 = 0x1;
}
