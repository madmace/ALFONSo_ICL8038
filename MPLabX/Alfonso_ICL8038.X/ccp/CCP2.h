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

This Header contains all functions for used with CCP1 module
 
- Frequency counter. 

*******************************************************************************/

#ifndef CCP2_H
#define	CCP2_H

#include <xc.h>
#include "globals.h"

#include <CCPLIb.h>

/**
 * Take the time capture and return to the frequency in KHz
 *
 * @param capture_time CCPx capture Time
 * @param capture_mode Capture mode used :
 * 
 * CCPx_CAPTURE_1_FALL, CCPx_CAPTURE_1_RISE
 * CCPx_CAPTURE_4_RISE, CCPx_CAPTURE_16_RISE
 *
 * @return The Signal frequency 
 * 
 */
double getFrequencyFromTimer(uint16_t capture_time, uint8_t capture_mode);

/**
 * This macro function configure and initialize the CCP module
 * in capture mode for every 16th rising edge
 *
 * @param void
 *
 * @return void
 * 
 */
void CCP2_init (void);

/**
 * This macro function is called in interrupt request
 *
 * @param void
 *
 * @return void
 * 
 */
uint16_t CCP2CaptureTask (void);

#endif	/* CCP2_H */

