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

This Header contains definitions for serial protocol

*******************************************************************************/

#ifndef PROTOCOL_H
#define	PROTOCOL_H

/*****************************
 * 
 * Request Protocol Structure
 * 
 ******************************/

// Position of Low byte part of command
#define CMD_PART_LOW_BYTE 0
// Position of High byte part of command
#define CMD_PART_HIGH_BYTE 1
// Initial position of the first byte of payload
#define START_REQ_PAYLOAD 2

/*****************************
 * 
 * Commands for request states of VCO/Mixers from client.
 * 
 ******************************/

// Request all ALFONSo State
#define SYNC_REQ_ALL 0xFFFF
// Length for SYNC_REQ_ALL request
#define SYNC_REQ_ALL_LEN 38

// Request VCO 1 State
#define SYNC_REQ_VCO_1 0xFFE0
// Request VCO 2 State 
#define SYNC_REQ_VCO_2 0xFFE1
// Request VCO 3 State
#define SYNC_REQ_VCO_3 0xFFE2
// Request VCO 4 State
#define SYNC_REQ_VCO_4 0xFFE3
// Length for SYNC_REQ_VCO_X request
#define SYNC_REQ_VCO_LEN 3

/*****************************
 * 
 * Commands for sets VCO/Mixers by client.
 * 
 ******************************/

// Request for enable/disable VCO 1
#define VCO_1_REQ_ENABLE 0x0001
// Request for enable/disable VCO 2
#define VCO_2_REQ_ENABLE 0x0002
// Request for enable/disable VCO 3
#define VCO_3_REQ_ENABLE 0x0003
// Request for enable/disable VCO 4
#define VCO_4_REQ_ENABLE 0x0004
// Length for VCO_X_REQ_ENABLE request
#define VCO_REQ_ENABLE_LEN 3

// Request for set VCO 1 frequency Range
#define VCO_1_REQ_FREQ_SELECTOR 0x0010
// Request for set VCO 2 frequency Range
#define VCO_2_REQ_FREQ_SELECTOR 0x0011
// Request for set VCO 3 frequency Range
#define VCO_3_REQ_FREQ_SELECTOR 0x0012
// Request for set VCO 4 frequency Range
#define VCO_4_REQ_FREQ_SELECTOR 0x0013
// Length for VCO_X_REQ_FREQ_SELECTOR request
#define VCO_REQ_FREQ_SELECTOR_LEN 3
        
// Request for set VCO 1 frequency coarse
#define VCO_1_REQ_FREQCOARSE 0x0020
// Request for set VCO 2 frequency coarse
#define VCO_2_REQ_FREQCOARSE 0x0021
// Request for set VCO 3 frequency coarse
#define VCO_3_REQ_FREQCOARSE 0x0022
// Request for set VCO 4 frequency coarse
#define VCO_4_REQ_FREQCOARSE 0x0023
// Length for VCO_X_REQ_FREQUENCY request
#define VCO_REQ_FREQCOARSE_LEN 3

// Request for set VCO 1 frequency fine
#define VCO_1_REQ_FREQFINE 0x0030
// Request for set VCO 2 frequency fine
#define VCO_2_REQ_FREQFINE 0x0031
// Request for set VCO 3 frequency fine
#define VCO_3_REQ_FREQFINE 0x0032
// Request for set VCO 4 frequency fine
#define VCO_4_REQ_FREQFINE 0x0033
// Length for VCO_X_REQ_FREQFINE request
#define VCO_REQ_FREQFINE_LEN 3

// Request for set VCO 1 Duty cycle
#define VCO_1_REQ_DUTY_CYCLE 0x0040
// Request for set VCO 2 Duty cycle
#define VCO_2_REQ_DUTY_CYCLE 0x0041
// Request for set VCO 3 Duty cycle
#define VCO_3_REQ_DUTY_CYCLE 0x0042
// Request for set VCO 4 Duty cycle
#define VCO_4_REQ_DUTY_CYCLE 0x0043
// Length for VCO_X_REQ_DUTY_CYCLE request
#define VCO_REQ_DUTY_CYCLE_LEN 3

// Request for enable VCO 1 Sine line
#define VCO_1_REQ_ENABLE_SINE 0x0050
// Request for enable VCO 2 Sine line
#define VCO_2_REQ_ENABLE_SINE 0x0051
// Request for enable VCO 3 Sine line
#define VCO_3_REQ_ENABLE_SINE 0x0052
// Request for enable VCO 4 Sine line
#define VCO_4_REQ_ENABLE_SINE 0x0053
// Length for VCO_X_REQ_ENABLE_SINE request
#define VCO_REQ_ENABLE_SINE_LEN 3

// Request for enable VCO 1 Square line
#define VCO_1_REQ_ENABLE_SQUARE 0x0060
// Request for enable VCO 2 Square line
#define VCO_2_REQ_ENABLE_SQUARE 0x0061
// Request for enable VCO 3 Square line
#define VCO_3_REQ_ENABLE_SQUARE 0x0062
// Request for enable VCO 4 Square line
#define VCO_4_REQ_ENABLE_SQUARE 0x0063
// Length for VCO_X_REQ_ENABLE_SQUARE request
#define VCO_REQ_ENABLE_SQUARE_LEN 3

// Request for enable VCO 1 Triangle line
#define VCO_1_REQ_ENABLE_TRIANGLE 0x0070
// Request for enable VCO 2 Triangle line
#define VCO_2_REQ_ENABLE_TRIANGLE 0x0071
// Request for enable VCO 3 Triangle line
#define VCO_3_REQ_ENABLE_TRIANGLE 0x0072
// Request for enable VCO 4 Triangle line
#define VCO_4_REQ_ENABLE_TRIANGLE 0x0073
// Length for VCO_X_REQ_ENABLE_TRIANGLE request
#define VCO_REQ_ENABLE_TRIANGLE_LEN 3

/*****************************
 * 
 * Commands for only get states of VCO/Mixers by client.
 * 
 ******************************/

// Request for get current frequency on VCO 1
#define VCO_1_REQ_FREQUENCY 0x0100
// Request for get current frequency on VCO 2
#define VCO_2_REQ_FREQUENCY 0x0101
// Request for get current frequency on VCO 3
#define VCO_3_REQ_FREQUENCY 0x0102
// Request for get current frequency on VCO 4
#define VCO_4_REQ_FREQUENCY 0x0103
// Length for VCO_X_REQ_FREQUENCY request
#define VCO_REQ_FREQUENCY_LEN 3

/*****************************
 * 
 * Relative Payload for command.
 * 
 ******************************/

// Payload HVCO for set VCOs frequency Range
#define HVCO_REQ_FREQ_SELECTOR 0x1
#define VCO_REQ_FREQ_SELECTOR 0x2
#define LFO_REQ_FREQ_SELECTOR 0x3
#define VLFO_REQ_FREQ_SELECTOR 0x4

/*****************************
 * 
 * States Response to client.
 * 
 ******************************/

// Response for VCO 1 frequency
#define VCO_1_RSP_FREQUENCY 0x1000
// Response for VCO 2 frequency
#define VCO_2_RSP_FREQUENCY 0x1001
// Response for VCO 3 frequency
#define VCO_3_RSP_FREQUENCY 0x1002
// Response for VCO 4 frequency
#define VCO_4_RSP_FREQUENCY 0x1003

#endif	/* PROTOCOL_H */
