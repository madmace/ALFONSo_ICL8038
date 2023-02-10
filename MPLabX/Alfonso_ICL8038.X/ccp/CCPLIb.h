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

This module contains functionalities for use capture/compare in standard mode.

CCP2 is fixed to RC1.
#pragma config CCP2MX =	1   //OFF	CCP2 input/output is multiplexed with RC1

For capture :
Functions their fix the T3CCP2:T3CCP1: Timer3 and Timer1 to CCPx Enable bits as
Timer3 is the capture/compare clock source for CCP2
Timer1 is the capture/compare clock source for CCP1

*******************************************************************************/

#ifndef CCPLIB_H
#define	CCPLIB_H

#include <xc.h>
#include "globals.h"

// CCPxCON Standard CCPx Control Register Configuration
#define CCPx_CAPTURE_1_FALL 0x4
#define CCPx_CAPTURE_1_RISE 0x5
#define CCPx_CAPTURE_4_RISE 0x6
#define CCPx_CAPTURE_16_RISE 0x7

// Timer prescaler configuration for CCPx functionality
#define CCPx_TIMER_PRESCALE_1 0x1
#define CCPx_TIMER_PRESCALE_2 0x2
#define CCPx_TIMER_PRESCALE_4 0x3
#define CCPx_TIMER_PRESCALE_8 0x4

// CCPxCON Standard CCPx Interrupt functions
#if defined(CCP1_INTERRUPT) && defined(CCP1_AVAILABLE)
    #define CCP1EnableInterrupts() {RCONbits.IPEN = 1; IPR1bits.CCP1IP = 0; PIE1bits.CCP1IE = 1;INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define CCP1ClearInterrupt() {PIR1bits.CCP1IF = 0;}
    #define CCP1MaskInterrupts() {PIE1bits.CCP1IE = 0;}
    #define CCP1UnmaskInterrupts() {PIE1bits.CCP1IE = 1;}
    #define CCP1InterruptFlag PIR1bits.CCP1IF;
    #define CCP1DisableInterrupts() {PIE1bits.CCP1IE = 0;}
    #define Timer1EnableInterrupts() {RCONbits.IPEN = 1; IPR1bits.TMR1IP = 0; PIE1bits.TMR1IE =  1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define Timer1DisableInterrupts() {PIE1bits.TMR1IE =  0;}
#endif
#if defined(CCP2_INTERRUPT) && defined(CCP2_AVAILABLE)
    #define CCP2EnableInterrupts() {RCONbits.IPEN = 1; IPR2bits.CCP2IP = 0; PIE2bits.CCP2IE = 1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define CCP2ClearInterrupt() {PIR2bits.CCP2IF = 0;}
    #define CCP2MaskInterrupts() {PIE2bits.CCP2IE = 0;}
    #define CCP2UnmaskInterrupts() {PIE2bits.CCP2IE = 1;}
    #define CCP2InterruptFlag PIR2bits.CCP2IF
    #define CCP2DisableInterrupts() {PIE2bits.CCP2IE = 0;}
    #define Timer3EnableInterrupts() {RCONbits.IPEN = 1; IPR2bits.TMR3IP = 0; PIE2bits.TMR3IE = 1; INTCONbits.GIEL = 1; INTCONbits.GIEH = 1;}
    #define Timer3DisableInterrupts() {PIE2bits.TMR3IE = 0;}
#endif

/**
 * Configure the CCPx in standard mode for capture
 *
 * @param sampling_type  Is the four bits in CCPxCON register CCPxCON<3:0>
 *        These are the value :
 * 
 *        CCPx_CAPTURE_1_FALL   Capture every falling edge
 *        CCPx_CAPTURE_1_RISE   Capture every rising edge
 *        CCPx_CAPTURE_4_RISE   Capture every 4th rising edge
 *        CCPx_CAPTURE_16_RISE  Capture every 16th rising edge
 * 
 * @param timer_prescale Is ratio to set to Timer's prescaler.
 * 
 *        CCPx_TIMER_PRESCALE_1 1:1 Prescale
 *        CCPx_TIMER_PRESCALE_2 1:2 Prescale
 *        CCPx_TIMER_PRESCALE_4 1:4 Prescale
 *        CCPx_TIMER_PRESCALE_8 1:8 Prescale
 *
 * @return void
 * 
 */
#ifdef CCP1_AVAILABLE
    void CCP1_init_capture (uint8_t sampling_type, uint8_t timer_prescale);
#endif
#ifdef CCP2_AVAILABLE
    void CCP2_init_capture (uint8_t sampling_type, uint8_t timer_prescale);
#endif

 /**
 * Configuration of T1CON for use with CCP1
 *
 * @param void
 *
 * @return void
 * 
 */
 void Timer1_config (uint8_t prescaler_value);
 
/**
 * Configuration of T3CON for use with CCP2
 *
 * @param timer_prescale Is ratio to set to Timer's prescaler.
 * 
 *        CCPx_TIMER_PRESCALE_1 1:1 Prescale
 *        CCPx_TIMER_PRESCALE_2 1:2 Prescale
 *        CCPx_TIMER_PRESCALE_4 1:4 Prescale
 *        CCPx_TIMER_PRESCALE_8 1:8 Prescale
 *
 * @return void
 * 
 */
 void Timer3_config (uint8_t prescaler_value);
 
 /**
 * Preliminary configuration of T3CON for CCPX
 * 
 * Fixes the T3CCP2:T3CCP1: Timer3 and Timer1 to CCPx Enable bits as
 * Timer3 is the capture/compare clock source for CCP2
 * Timer1 is the capture/compare clock source for CCP1
 *
 * @param timer_prescale Is ratio to set to Timer's prescaler.
 * 
 *        CCPx_TIMER_PRESCALE_1 1:1 Prescale
 *        CCPx_TIMER_PRESCALE_2 1:2 Prescale
 *        CCPx_TIMER_PRESCALE_4 1:4 Prescale
 *        CCPx_TIMER_PRESCALE_8 1:8 Prescale
 *
 * @return void
 * 
 */
 void Timer3_CCPX_enable();

#endif	/* CCPLIB_H */

