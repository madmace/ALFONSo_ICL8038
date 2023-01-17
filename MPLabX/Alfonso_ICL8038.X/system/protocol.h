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

This Header contains definitions for serial protocol

*******************************************************************************/

#ifndef PROTOCOL_H
#define	PROTOCOL_H

/*****************************
 * 
 * Commands for request states of VCO/Mixers from client.
 * 
 ******************************/

// Resquest all ALFONSo State
#define SYNC_ALL 0xFFFF

// Resquest VCO 1 State
#define SYNC_VCO_1 0xFFE0
// Resquest VCO 2 State
#define SYNC_VCO_2 0xFFE1
// Resquest VCO 3 State
#define SYNC_VCO_3 0xFFE2
// Resquest VCO 4 State
#define SYNC_VCO_4 0xFFE3

/*****************************
 * 
 * Commands for sets VCO/Mixers by client.
 * 
 ******************************/

// Request for enable/disable VCO 1
#define VCO_1_ENABLE 0x0001
// Request for enable/disable VCO 2
#define VCO_2_ENABLE 0x0002
// Request for enable/disable VCO 3
#define VCO_3_ENABLE 0x0003
// Request for enable/disable VCO 4
#define VCO_4_ENABLE 0x0004

// Request for set VCO 1 frequency
#define VCO_1_FREQUENCY 0x0010
// Request for set VCO 2 frequency
#define VCO_2_FREQUENCY 0x0011
// Request for set VCO 3 frequency
#define VCO_3_FREQUENCY 0x0012
// Request for set VCO 4 frequency
#define VCO_4_FREQUENCY 0x0013

// Request for set VCO 1 Duty cycle
#define VCO_1_DUTY_CYCLE 0x0020
// Request for set VCO 2 Duty cycle
#define VCO_2_DUTY_CYCLE 0x0021
// Request for set VCO 3 Duty cycle
#define VCO_3_DUTY_CYCLE 0x0022
// Request for set VCO 4 Duty cycle
#define VCO_4_DUTY_CYCLE 0x0023

// Request for enable VCO 1 Sine line
#define VCO_1_ENABLE_SINE 0x0030
// Request for enable VCO 2 Sine line
#define VCO_2_ENABLE_SINE 0x0031
// Request for enable VCO 3 Sine line
#define VCO_3_ENABLE_SINE 0x0032
// Request for enable VCO 4 Sine line
#define VCO_4_ENABLE_SINE 0x0033

// Request for enable VCO 1 Square line
#define VCO_1_ENABLE_SQUARE 0x0040
// Request for enable VCO 2 Square line
#define VCO_2_ENABLE_SQUARE 0x0041
// Request for enable VCO 3 Square line
#define VCO_3_ENABLE_SQUARE 0x0042
// Request for enable VCO 4 Square line
#define VCO_4_ENABLE_SQUARE 0x0043

// Request for enable VCO 1 Triangle line
#define VCO_1_ENABLE_TRIANGLE 0x0050
// Request for enable VCO 2 Triangle line
#define VCO_2_ENABLE_TRIANGLE 0x0051
// Request for enable VCO 3 Triangle line
#define VCO_3_ENABLE_TRIANGLE 0x0052
// Request for enable VCO 4 Triangle line
#define VCO_4_ENABLE_TRIANGLE 0x0053

/*****************************
 * 
 * States Response to client.
 * 
 ******************************/

// Response for VCO 1 frequency
#define VCO_1_ENABLE_TRIANGLE 0x0050
// Request for enable VCO 2 Triangle line
#define VCO_2_ENABLE_TRIANGLE 0x0051
// Request for enable VCO 3 Triangle line
#define VCO_3_ENABLE_TRIANGLE 0x0052
// Request for enable VCO 4 Triangle line
#define VCO_4_ENABLE_TRIANGLE 0x0053

#endif	/* PROTOCOL_H */
