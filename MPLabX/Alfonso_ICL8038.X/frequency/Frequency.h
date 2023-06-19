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

#ifndef FREQUENCY_H
#define	FREQUENCY_H

#include <xc.h>
#include "globals.h"

// PIRx Timer Interrupt functions
#if defined(TMR0_AVAILABLE)
    #define Timer0EnableInterruptsLowPriority() {RCONbits.IPEN = 1; INTCON2bits.TMR0IP = 0; INTCONbits.TMR0IE =  1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define Timer0DisableInterrupts() {INTCONbits.TMR0IE =  0;}
    #define Timer0ClearInterrupt() {INTCONbits.TMR0IF = 0;}
    #define Timer0ResetRegisters() {TMR0 = 0x00;}
    #define Timer0Enabled() {T0CONbits.TMR0ON = 0x1;}
    #define Timer0Disabled() {T0CONbits.TMR0ON = 0x0;}
#endif
#if defined(TMR1_AVAILABLE)
    #define Timer1EnableInterruptsLowPriority() {RCONbits.IPEN = 1; IPR1bits.TMR1IP = 0; PIE1bits.TMR1IE =  1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define Timer1DisableInterrupts() {PIE1bits.TMR1IE =  0;}
    #define Timer1ClearInterrupt() {PIR1bits.TMR1IF = 0;}
    #define Timer1ResetRegisters() {TMR1H = 0x00; TMR1L = 0x00;}
//    #define Timer1Set32KRegisters() {TMR1H = 0x80; TMR1L = 0x00;}
    #define Timer1Set32KRegisters() {TMR1H = 0x56; TMR1L = 0x00;}       //Patch TULLI (My electronic component supplier, I use a crystal that is not 32768 Hz but more.)
    #define Timer1Enabled() {T1CONbits.TMR1ON = 0x1;}
    #define Timer1Disabled() {T1CONbits.TMR1ON = 0x0;}
#endif
#if defined(TMR3_AVAILABLE)
    #define Timer3EnableInterruptsLowPriority() {RCONbits.IPEN = 1; IPR2bits.TMR3IP = 0; PIE2bits.TMR3IE = 1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define Timer3DisableInterrupts() {PIE2bits.TMR3IE = 0;}
    #define Timer3ClearInterrupt() {PIR2bits.TMR3IF = 0;}
    #define Timer3ResetRegisters() {TMR3H = 0x00; TMR3L = 0x00;}
#endif

/***************************************
 * Timer1 16bit functions
 ***************************************/

void init_Timer1 (void);

/***************************************
 * Timer0 8bit functions
 ***************************************/

void init_Timer0 (void);


#endif	/* FREQUENCY_H */

