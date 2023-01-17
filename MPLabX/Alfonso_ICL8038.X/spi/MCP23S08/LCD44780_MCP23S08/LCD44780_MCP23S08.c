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

This source contains SPI Library functions implementations for
Dual Digital Potentiometer series
MCP425X

*******************************************************************************/

#include "LCD44780_MCP23S08.h"
#include "utilities.h"

// Hardware address for MCP23S08
uint8_t MCP23S08_Address = 0x00;
// Snapshot buffer to MPC23S08
uint8_t MCP23S08_data_buffer = 0x00;

// LCD44780_MCP23S08_write_buffer_SPI1 Implementation
void LCD44780_MCP23S08_write_buffer_SPI1 () {
    
    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_OLAT, MCP23S08_data_buffer);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;
    
    __delay_us(50);
}
// LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1 Implementation
void LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1 () {
    
    // Set ENABLE to 1
    MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_E;
    
    // Set buffer to MCP23S08
    LCD44780_MCP23S08_write_buffer_SPI1();
    
    //NOTE: Enable Line must be up for at least 450us!
	//NOTE: Data must be valid after 320us from LCD_ENABLE rising
	__delay_us(LCD44780_MCP23S08_CMD_DATA_DELAY);
    
    // Reset ENABLE to 0
    MCP23S08_data_buffer &= ~LCD44780_MCP23S08_LCD_E;
    
    // Set buffer to MCP23S08
    LCD44780_MCP23S08_write_buffer_SPI1();
}

// LCD44780_MCP23S08_busy_SPI1 Implementation
uint8_t LCD44780_MCP23S08_busy_SPI1 (void) {
    
	uint8_t ucDataVal;
    uint8_t bRetVal;

    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Set GPIO for DB7 as input
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_IODIR, 0x08);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;
    
    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Set DB4, DB5, DB6, DB7 to 0 and ENABLE = 1, RW = 1 and RS = 0
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_GPIO, 0x30);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;
    
	// NOTE: Enable Line must be up for at least 450us!
	// NOTE: Data must be valid after 320us from LCD_ENABLE rising
	__delay_us(LCD44780_MCP23S08_BUSY_DELAY);
    
    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Read from LCD
    MCP23S08_Read_Register_SPI1(MCP23S08_Address, MCP23S08_GPIO, &ucDataVal);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;
	
	// Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Set DB4, DB5, DB6, DB7 to 0 and ENABLE = 0, RW = 0 ans RS = 0
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_GPIO, 0x00);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;

	// Mask all but busy flag
	ucDataVal = ucDataVal & 0x08;
	if(ucDataVal == 0x08){
		bRetVal = 0x01;
	}
	else
	{
		bRetVal = 0x00;
	}
    
    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Set all GPIO as output
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_IODIR, 0x00);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;
    
    return bRetVal;
}

// LCD44780_MCP23S08_set_low_nibble_buffer Implementation
void LCD44780_MCP23S08_set_low_nibble_buffer (uint8_t data) {
    
    // Clear the nibble data bits
	MCP23S08_data_buffer &= ~(LCD44780_MCP23S08_LCD_D0 | LCD44780_MCP23S08_LCD_D1 | LCD44780_MCP23S08_LCD_D2 | LCD44780_MCP23S08_LCD_D3); 
    
    if (data & 0x01) {
        // Set First lower bit
        MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_D0;
    }
    
    if (data & 0x02) {
        // Set Second bit
        MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_D1;
    }
    
    if (data & 0x04) {
        // Set Third bit
        MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_D2;
    }
      
    if (data & 0x08) {
        // Set Fourth Higher bit
        MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_D3;
    }
}

// LCD44780_MCP23S08_send_nibble_SPI1 Implementation
void LCD44780_MCP23S08_send_nibble_SPI1 (uint8_t command) {
    
    // Use only DB4, DB5, DB6, DB7 for this nibble
    LCD44780_MCP23S08_set_low_nibble_buffer(command);
    // Set RW and RS to 0
    MCP23S08_data_buffer &= ~(LCD44780_MCP23S08_LCD_RW | LCD44780_MCP23S08_LCD_RS);
    // Write buffer an trigger the Enable
    LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1();
}

// LCD44780_MCP23S08_send_cmd_SPI1 Implementation
void LCD44780_MCP23S08_send_cmd_SPI1 (uint8_t command) {
    
	uint8_t ucDataVal;

#ifdef LCD44780_MCP23S08_BUSY_FLAG_AVAIL
    // Wait for LCD to be ready
    while(LCD44780_MCP23S08_busy_SPI1() == 1) {}
#else
    // Busy Flag not supported
    __delay_us(LCD44780_MCP23S08_BUSY_DELAY);
#endif
    
    // Mask for High nibble and shift at right by one nibble
    // Put High nibble in low nibble.
    ucDataVal = (command & 0xF0) >> 4;
    
    // Use only DB4, DB5, DB6, DB7 for this nibble
    LCD44780_MCP23S08_set_low_nibble_buffer(ucDataVal);
    // Set RW and RS to 0
    MCP23S08_data_buffer &= ~(LCD44780_MCP23S08_LCD_RW | LCD44780_MCP23S08_LCD_RS);
    // Write buffer an trigger the Enable
    LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1();
    
    // Mask for Low nibble
    ucDataVal = command & 0x0F;
    
    // Use only DB4, DB5, DB6, DB7 for this nibble
    LCD44780_MCP23S08_set_low_nibble_buffer(ucDataVal);
    // Set RW and RS to 0
    MCP23S08_data_buffer &= ~(LCD44780_MCP23S08_LCD_RW | LCD44780_MCP23S08_LCD_RS);
    // Write buffer an trigger the Enable
    LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1();
}

// LCD44780_MCP23S08_lcd_clear_SPI1 Implementation
void LCD44780_MCP23S08_lcd_clear_SPI1(void) {
	// Send the command
	LCD44780_MCP23S08_send_cmd_SPI1(LCD44780_MCP23S08_CLEAR_LCD);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_CLEAR_DELAY);
}

// LCD44780_MCP23S08_home_SPI1 Implementation
void LCD44780_MCP23S08_lcd_home_SPI1 (void) {
	// Send the command
	LCD44780_MCP23S08_send_cmd_SPI1(LCD44780_MCP23S08_HOME_LCD);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_HOME_DELAY);
}

// LCD44780_MCP23S08_lcd_emode_SPI1 Implementation
void LCD44780_MCP23S08_lcd_emode_SPI1 (uint8_t options) {
	// Ensure that only valid range of bits set
	options = options & 0x03;
	// Set display command bit
	options = options | 0x04;
	// Send the command
	LCD44780_MCP23S08_send_cmd_SPI1(options);
}

// LCD44780_MCP23S08_lcd_dmode_SPI1 Implementation
void LCD44780_MCP23S08_lcd_dmode_SPI1 (uint8_t options) {
	// Ensure that only valid range of bits set
	options = options & 0x07;
	// Set display command bit
	options = options | 0x08;
	// Send the command
	LCD44780_MCP23S08_send_cmd_SPI1(options);
}

// LCD44780_MCP23S08_lcd_cmode_SPI1 Implementation
void LCD44780_MCP23S08_lcd_cmode_SPI1 (uint8_t options) {
	// Ensure that only valid range of bits set
	options = options & 0x0C;
	// Set display command bit
	options = options | 0x10;
	// Send the command
	LCD44780_MCP23S08_send_cmd_SPI1(options);
}

// LCD44780_MCP23S08_lcd_fmode_SPI1 Implementation
void LCD44780_MCP23S08_lcd_fmode_SPI1 (uint8_t options) {
	// Ensure that only valid range of bits set
	options = options & 0x1F;
	// Set display command bit
	options = options | 0x20;
	// Send the command
	LCD44780_MCP23S08_send_cmd_SPI1(options);
}

// LCD44780_MCP23S08_lcd_init_SPI1 Implementation
void LCD44780_MCP23S08_lcd_init_SPI1 (uint8_t device_address) {
    
    // Set address
    MCP23S08_Address = device_address;
    // Initial set of buffer
    // Data 0x0 and RW = 0, RS = 0, ENABLE = 0
    MCP23S08_data_buffer = 0x00;
    // Switch on backlight
    MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_TURN_ON_LED;
    
    // Set CS port as output
    LCD44780_MCP23S08_CS_LINE_TRIS = 0x0;
    
    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Set configuration
    // All disable except for hardware address, polarity active-high
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_IOCON, 0x0A);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;       
        
    // Set CS state in select state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x0;
    // Set all GPIO as output
    MCP23S08_Write_Register_SPI1(MCP23S08_Address, MCP23S08_IODIR, 0x00);
    // Set CS state in unselect state
    LCD44780_MCP23S08_CS_LINE_PORT = 0x1;
    
    // Wait for more than 30ms for startup
    __delay_ms(LCD44780_MCP23S08_POWERON_DELAY);
    
    // Set DB4 and DB5 to 1, DB6, DB7 to 0 and RW = 0 and RS = 0
    LCD44780_MCP23S08_send_nibble_SPI1(LCD44780_MCP23S08_SYNC_LCD);
    // Wait for more than 5ms for startup
    __delay_ms(LCD44780_MCP23S08_FIRST_SYNC_DELAY);
    
    // Set DB4 and DB5 to 1, DB6, DB7 to 0 and RW = 0 and RS = 0
    LCD44780_MCP23S08_send_nibble_SPI1(LCD44780_MCP23S08_SYNC_LCD);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_SECOND_SYNC_DELAY);
    
    // Set DB4 and DB5 to 1, DB6, DB7 to 0 and RW = 0 and RS = 0
    LCD44780_MCP23S08_send_nibble_SPI1(LCD44780_MCP23S08_SYNC_LCD);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_SECOND_SYNC_DELAY);
    
    // Set DB5 to 1, DB4, DB6, DB7 to 0 and ENABLE = 0, RW = 0 and RS = 0
    LCD44780_MCP23S08_send_nibble_SPI1(LCD44780_MCP23S08_HOME_LCD);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_SECOND_SYNC_DELAY);
        
    // Select Function Set (4 bit mode and dual lines)
	LCD44780_MCP23S08_lcd_fmode_SPI1(LCD44780_MCP23S08_IFACE_4BIT | LCD44780_MCP23S08_DUAL_LINE);
    // Wait for more than 1ms for startup
    __delay_ms(2000);
    
    // Turn off display
    LCD44780_MCP23S08_lcd_dmode_SPI1(LCD44780_MCP23S08_DISPLAY_OFF | LCD44780_MCP23S08_CURSOR_OFF | LCD44780_MCP23S08_BLINK_OFF);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_SECOND_SYNC_DELAY);
       
    // Clear LCD
	LCD44780_MCP23S08_lcd_clear_SPI1();
	
	// Set entry mode
	LCD44780_MCP23S08_lcd_emode_SPI1(LCD44780_MCP23S08_INC_CURSOR | LCD44780_MCP23S08_SHIFT_OFF);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_SECOND_SYNC_DELAY);
	
	// Turn on display
	LCD44780_MCP23S08_lcd_dmode_SPI1(LCD44780_MCP23S08_DISPLAY_ON | LCD44780_MCP23S08_CURSOR_OFF | LCD44780_MCP23S08_BLINK_OFF);
    // Wait for more than 1ms for startup
    __delay_ms(LCD44780_MCP23S08_SECOND_SYNC_DELAY);
}

// LCD44780_MCP23S08_send_data_SPI1 Implementation
void LCD44780_MCP23S08_send_data_SPI1 (uint8_t value) {
    
	uint8_t ucDataVal;

#ifdef LCD44780_MCP23S08_BUSY_FLAG_AVAIL
    // Wait for LCD to be ready
    while(LCD44780_MCP23S08_busy_SPI1() == 1) {}
#else
    // Busy Flag not supported
    __delay_us(LCD44780_MCP23S08_BUSY_DELAY);
#endif
    
    // Mask for High nibble and shift at right by one nibble
    // Put High nibble in low nibble.
    ucDataVal = (value & 0xF0) >> 4;
    
    // Use only DB4, DB5, DB6, DB7 for this nibble
    LCD44780_MCP23S08_set_low_nibble_buffer(ucDataVal);
    // Set RW to 0 and RS to 1
    MCP23S08_data_buffer &= ~LCD44780_MCP23S08_LCD_RW;
    MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_RS;
    // Write buffer an trigger the Enable
    LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1();
    
    // Mask for Low nibble
    ucDataVal = value & 0x0F;
    
    // Use only DB4, DB5, DB6, DB7 for this nibble
    LCD44780_MCP23S08_set_low_nibble_buffer(ucDataVal);
    // Set RW to 0 and RS to 1
    MCP23S08_data_buffer &= ~LCD44780_MCP23S08_LCD_RW;
    MCP23S08_data_buffer |= LCD44780_MCP23S08_LCD_RS;
    // Write buffer an trigger the Enable
    LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1();
}

// LCD44780_MCP23S08_send_message_SPI1 Implementation
void LCD44780_MCP23S08_send_message_SPI1 (const char *buffer) {
	
	 // Write data to LCD up to null
    while(*buffer) {
	    
	    // Write character to LCD
	    LCD44780_MCP23S08_send_data_SPI1(*buffer);
	    // Increment buffer
	    buffer++;              
   }
}

// LCD44780_MCP23S08_send_string_SPI1 Implementation
void LCD44780_MCP23S08_send_string_SPI1 (uint8_t *buffer) {
	
	// Write data to LCD up to null
	while(*buffer){
		
		// Write character to LCD
		LCD44780_MCP23S08_send_data_SPI1(*buffer);
		// Increment buffer
		buffer++;               
	}
}

// LCD44780_MCP23S08_goto_line_SPI1 Implementation
void LCD44780_MCP23S08_goto_line_SPI1 (uint8_t line) {

    switch(line) {

        case LCD44780_MCP23S08_FIRST_LINE: 
            LCD44780_MCP23S08_send_cmd_SPI1(0x80);
            break;

        case LCD44780_MCP23S08_SECOND_LINE:
            LCD44780_MCP23S08_send_cmd_SPI1(0xC0);
            break;

        case LCD44780_MCP23S08_THIRD_LINE:
            LCD44780_MCP23S08_send_cmd_SPI1(0x94);
            break;

        case LCD44780_MCP23S08_FOURTH_LINE:
            LCD44780_MCP23S08_send_cmd_SPI1(0xD4);     
	}
}

// LCD44780_MCP23S08_backlight_SPI1 Implementation
void LCD44780_MCP23S08_backlight_SPI1 (uint8_t active) {

	// Clear the LED bit
	MCP23S08_data_buffer &= ~LCD44780_MCP23S08_LCD_TURN_ON_LED;

	// Write the data within the buffer
	MCP23S08_data_buffer |= active;
    
    // Write buffer to GPIO of MCP23S08
    LCD44780_MCP23S08_write_buffer_SPI1();
}

// LCD44780_MCP23S08_shift_SPI1 Implementation
void LCD44780_MCP23S08_shift_SPI1 (uint8_t shift, uint8_t number_of_shift) {
	
	uint8_t i;
	
	for (i = 0; i < number_of_shift; i++) {	
		LCD44780_MCP23S08_send_cmd_SPI1(0x18 | shift);
	}	
}

// LCD_shift_cursor_SPI1 Implementation
void LCD44780_MCP23S08_shift_cursor_SPI1 (uint8_t shift, uint8_t number_of_shift){
	
	uint8_t i;
	
	for (i = 0; i < number_of_shift; i++) {
		LCD44780_MCP23S08_send_cmd_SPI1(0x10 | shift);
	} 		
}

// LCD44780_MCP23S08_goto_xy_SPI1 Implementation
void LCD44780_MCP23S08_goto_xy_SPI1 (uint8_t x, uint8_t y){

    LCD44780_MCP23S08_goto_line_SPI1(y);
    LCD44780_MCP23S08_shift_cursor_SPI1(LCD44780_MCP23S08_SHIFT_RIGHT, x - 1);
}

// LCD44780_MCP23S08_write_integer_SPI1 Implementation
void LCD44780_MCP23S08_write_integer_SPI1 (int16_t value, uint8_t number_of_digits, uint8_t zero_cleaning) {
	
    // The array size is 6, plus end of string '\0'
	uint8_t convertedInt [7];

	uint8_t string_length;
    uint8_t counter;
    uint8_t shift_counter;
	
	// Integer is converted to string
    conv_int16_to_string(&convertedInt[0], value);
    
    string_length = get_string_length(&convertedInt[0]);

    // Make the string as long as needed by appending 0 on the left
    for (counter = 0; counter < (number_of_digits - string_length); counter++){
        // Shift right as needed by adding 0
        for (shift_counter = number_of_digits; shift_counter > 0; shift_counter--){
            convertedInt[shift_counter] = convertedInt[shift_counter-1];
        }   
        
        // After each shift a 0 is inserted for positive numbers
        // For negative numbers and empty space is added
        if (convertedInt[0] == '-' || convertedInt[0] == ' '){
            convertedInt[0] = ' ';
        } else {
            convertedInt[0] = '0';
        }        
    }    
    
    string_length = get_string_length(&convertedInt[0]);
    
    // Remove the 0 on the left, if required
    if (zero_cleaning == LCD44780_MCP23S08_ZERO_CLEANING_ON) {       
        // I keep at least one 0, thus I do not check the entire string length
        for (counter = 0; counter < string_length; counter++){
            if (convertedInt[counter] == '0'){
                convertedInt[counter] = ' ';
            } else {
                // Setting the counter to this value will terminate the for.
                counter = string_length;
            }   
        }  
    }  

	LCD44780_MCP23S08_send_string_SPI1(convertedInt);		
}

// LCD44780_MCP23S08_cursor_SPI1  Implementation
void LCD44780_MCP23S08_cursor_SPI1 (uint8_t active, uint8_t blinking) {
	
	LCD44780_MCP23S08_send_cmd_SPI1(0x0C | active | blinking);
}
