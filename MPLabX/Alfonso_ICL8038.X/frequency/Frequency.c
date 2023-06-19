/*******************************************************************************

Author : Emiliano Mazza
Version : 1.0
Created on Date : 15/18/2020
Last update     : 03/06/2023

CopyRight 2006-2015 all rights are reserved

THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT,
IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

This Header contains all functions for used with ...
 
- Frequency counter via Timer0

*******************************************************************************/

#include <Frequency.h>


void init_Timer1 (void) {
    
    // Disable Timer1
    Timer1Disabled();
    // Disable Timer1 overflow
    Timer1DisableInterrupts();
    // Set start counting from 32768
    Timer1Set32KRegisters();
    
    // Configure T1CON register
    T1CONbits.RD16 = 0x0;       // Enables register read/write of Timer1 in two 8-bit operations
    T1CONbits.T1RUN = 0x0;      // Device clock is derived from another source
    T1CONbits.T1CKPS = 0x0;     // 1:1 Prescale value
    T1CONbits.T1OSCEN = 0x1;    // Timer1 oscillator is enabled
    T1CONbits.T1SYNC = 0x1;     // Do not synchronize external clock input
    T1CONbits.TMR1CS = 0x1;     // External clock from RC0/T1OSO/T13CKI pin (on the rising edge)
    
    // Clear Timer1 interrupt
    Timer1ClearInterrupt();
    // Enable Timer1 interrupt
    Timer1EnableInterruptsLowPriority();
    
    // Enable Timer1
    Timer1Enabled();
}

void init_Timer0 (void) {
    
    // Disable Timer0
    Timer0Disabled();
    // Disable Timer0 overflow
    Timer0DisableInterrupts();
    // Clear Timer0
    Timer0ResetRegisters();
    
    // Configure T0CON register
    T0CONbits.T08BIT = 0x1;     // Timer0 is configured as an 8-bit timer/counter
    T0CONbits.T0CS = 0x1;       // Transition on T0CKI pin
    T0CONbits.T0SE = 0x0;       // Increment on low-to-high transition on T0CKI pin
    T0CONbits.PSA = 0x1;        // Timer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
    T0CONbits.T0PS = 0x0;       // Not used. 1:1
    
    // Clear Timer0 interrupt
    Timer0ClearInterrupt();
    // Enable Timer0 interrupt
    Timer0EnableInterruptsLowPriority();
    
    // Enable Timer0
    Timer0Enabled();
}