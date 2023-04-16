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

This module contains the implementations of all generic utilities functions.
Such as special conversion between differents types.

*******************************************************************************/

#include "utilities.h"

// conv_int16_to_string Implementation
int8_t conv_int16_to_string (uint8_t * buffer, int16_t value) {

    uint8_t new_digit = 0;
    uint8_t digit_counter = 0;
    // he flag is set if you should not ignore the following digits
    // 0 ignore the digit
    // 1 do not ignore the digit
    uint8_t flag = 0;
    
    if (value < 0) {
        buffer[digit_counter] = '-'; 
        value = value * (-1);
        digit_counter++;
    } else {
//        buffer[digit_counter]= '+'; 
//        digit_counter++;
    }
    
    // MSB
    new_digit = (uint8_t) (value / 10000);
    // Adding 48 it will convert the integer in char
    if (new_digit != 0){
        buffer[digit_counter]= new_digit + 48; 
        value = value - (new_digit * 10000);
        flag = 1;
        digit_counter++;
    }  
    
    new_digit = (uint8_t) (value / 1000);
    if (new_digit != 0 || flag == 1){
        buffer[digit_counter]= new_digit + 48;
        value = value - (new_digit * 1000);
        flag = 1;
        digit_counter++;
    }

    new_digit = (uint8_t) (value / 100);
    if (new_digit != 0 || flag == 1){
        buffer[digit_counter]= new_digit + 48;
        value = value - (new_digit * 100);
        flag = 1;
        digit_counter++;
    }
        
    new_digit = (uint8_t) (value / 10);
    if (new_digit != 0 || flag == 1){
        buffer[digit_counter]= new_digit + 48;
        value = value - (new_digit * 10);
        flag = 1;
        digit_counter++;
    }
    
    // LSB
    new_digit = (uint8_t)value;
    buffer[digit_counter]= new_digit + 48;
    digit_counter++;
    
	buffer[digit_counter]= '\0';
    
	return (0); 
}

// get_string_length Implementation
uint8_t get_string_length (uint8_t * buffer){
    uint8_t counter = 0;
    
    while (buffer[counter] != '\0'){        
        counter++;
    }
    
    return(counter); 
}

// set_int16_by_bit_weight Implementation
void set_int16_by_bit_weight (volatile uint16_t * word, uint16_t weightbit, bool value) {
    
    // Invert mask
    uint16_t uiMask = ~weightbit;
    // Isolate weight bit
    *word &= uiMask;
    
    if (value) {
        // Set bit
        *word |= weightbit;
    }
}
