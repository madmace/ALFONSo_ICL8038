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

This Header contains all generic utilities functions.
Such as special conversion between differents types.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef UTILITIES_H
#define	UTILITIES_H

#include <xc.h>
#include <stdbool.h>

/**
 * @brief
 * This function converts signed integer to a string of chars.
 * The returned string is always the shortest possible one containing the value.
 * Digit 0 contains - sign if the number is negative. The sign + is not shown.
 *
 * @param buffer Pointer to the array that will contain the string.
 *
 * @param value Integer value to convert
 * 
 * @return error 0: Conversion OK
 *              -1: Overflow - The number is too big  
 */
int8_t conv_int16_to_string (uint8_t * buffer, int16_t value);

/**
 * @brief 
 * This function returns the string length, marked with the '\0' character
 * The \0 character is not counted.
 *
 * @param buffer Pointer to the string that contains the char array ending with '\0'
 * 
 * @return value String length 
 *      
 */
uint8_t get_string_length (uint8_t * buffer);

/**
 * @brief
 * This function sets or resets a single bit in an 16bit word leaving all rest of
 * word bits at same value.
 *
 * @param word the 16-bit word to set or reset bit
 *
 * @param weightbit Is the mask or waight. A word with set 1, the only bit to be change.
 * (Ex 0x4000 0b0100 0000 0000 0000 will set or reset the fifteenth bit) 
 * 
 * @param value Is bit to set or reset
 * 
 * @return void
 *
 */
void set_int16_by_bit_weight (volatile uint16_t * word, uint16_t weightbit, bool value);

#endif	/* UTILITIES_H */

