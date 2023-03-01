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

This Header contains SPI Library functions for
control an LCD based on Hitachi 44780 controller via
8-Bit I/O Expander MCP23S08.
 
The Hitachi 44780 controller will be set on 4-Bit Interface mode.
It's the only mode supported for use with MCP23S08.

Hardware connections are :

MCP23S08 GP0 -> LCD D4 
MCP23S08 GP1 -> LCD D5 
MCP23S08 GP2 -> LCD D6 
MCP23S08 GP3 -> LCD D7 
MCP23S08 GP4 -> LCD E 
MCP23S08 GP5 -> LCD R/W 
MCP23S08 GP6 -> LCD RS 
MCP23S08 GP7 -> LCD LED (use a PNP or NPN transistor as buffer to drive the backlight LED).

Attention !!
Not include CS operations. It will be managed out functions provided.
Affect Single and Daisy-Chain transactions.

*******************************************************************************/

#ifndef LCD44780_MCP23S08_H
#define	LCD44780_MCP23S08_H

#include <xc.h>
#include "SPILib.h"
#include "MCP23S08.h"

// LCD constants
// Each bit is connected to the MC23S08 
#define LCD44780_MCP23S08_LCD_D0  1
#define LCD44780_MCP23S08_LCD_D1  2
#define LCD44780_MCP23S08_LCD_D2  4	
#define LCD44780_MCP23S08_LCD_D3  8	
#define LCD44780_MCP23S08_LCD_E   16	
#define LCD44780_MCP23S08_LCD_RW  32
#define LCD44780_MCP23S08_LCD_RS  64	
#define LCD44780_MCP23S08_LCD_LED 128

// Constant Definitions
#define LCD44780_MCP23S08_COLUMNS 16
#define LCD44780_MCP23S08_ROWS 2
#define LCD44780_MCP23S08_FIRST_LINE 0
#define LCD44780_MCP23S08_SECOND_LINE 1
#define LCD44780_MCP23S08_THIRD_LINE 3
#define LCD44780_MCP23S08_FOURTH_LINE 4

// Basic mode variables
#define LCD44780_MCP23S08_CLEAR_LCD 0x01
#define LCD44780_MCP23S08_HOME_LCD 0x02
#define LCD44780_MCP23S08_SYNC_LCD 0x03

// Entry mode variables
#define LCD44780_MCP23S08_INC_CURSOR 0x02
#define LCD44780_MCP23S08_DEC_CURSOR 0x00
#define LCD44780_MCP23S08_SHIFT_ON 0x01
#define LCD44780_MCP23S08_SHIFT_OFF 0x00

// Display control variables
#define LCD44780_MCP23S08_DISPLAY_ON 0x04
#define LCD44780_MCP23S08_DISPLAY_OFF 0x00
#define LCD44780_MCP23S08_CURSOR_ON 0x02
#define LCD44780_MCP23S08_CURSOR_OFF 0x00
#define LCD44780_MCP23S08_BLINK_ON 0x01
#define LCD44780_MCP23S08_BLINK_OFF 0x00

// Cursor move variables
#define LCD44780_MCP23S08_SHIFT_DISP 0x08
#define LCD44780_MCP23S08_SHIFT_RIGHT 0x04
#define LCD44780_MCP23S08_SHIFT_LEFT 0x00

// Function set variables
#define LCD44780_MCP23S08_IFACE_4BIT 0x00
#define LCD44780_MCP23S08_IFACE_8BIT 0x10
#define LCD44780_MCP23S08_SINGLE_LINE 0x00
#define LCD44780_MCP23S08_DUAL_LINE 0x08
#define LCD44780_MCP23S08_DOTS_5X7 0x00
#define LCD44780_MCP23S08_DOTS_5X10 0x04

// LCD Back Light driver
#define LCD44780_MCP23S08_DRIVER_NPN
//#define LCD44780_MCP23S08_DRIVER_PNP

// LCD ON-OFF Backlight state is used
#ifdef LCD44780_MCP23S08_DRIVER_NPN
    #define LCD44780_MCP23S08_LCD_TURN_ON_LED LCD44780_MCP23S08_LCD_LED
    #define LCD44780_MCP23S08_LCD_TURN_OFF_LED 0x00  
#endif

#ifdef LCD44780_MCP23S08_DRIVER_PNP
    #define LCD44780_MCP23S08_LCD_TURN_ON_LED 0x00
    #define LCD44780_MCP23S08_LCD_TURN_OFF_LED LCD44780_MCP23S08_LCD_LED
#endif

// Chip Select definition for MCP23S08 used for LCD
#ifndef LCD44780_MCP23S08_CS_LINE_TRIS
    #define LCD44780_MCP23S08_CS_LINE_TRIS TRISAbits.RA1
#endif

#ifndef LCD44780_MCP23S08_CS_LINE_PORT
    #define LCD44780_MCP23S08_CS_LINE_PORT LATAbits.LATA1
#endif

// LCD Busy Flag functionality
// Some LCD tested not original 44780 Hitachi from China
// NOT SUPPORT the Busy Flag.
//#define LCD44780_MCP23S08_BUSY_FLAG_AVAIL
#define LCD44780_MCP23S08_BUSY_FLAG_NOT_AVAIL

// LCD Synch Timing Class
#define LCD44780_MCP23S08_FAST_CLASS
//#define LCD44780_MCP23S08_SLOW_CLASS

#ifdef LCD44780_MCP23S08_SLOW_CLASS
    #define LCD44780_MCP23S08_POWERON_DELAY 200     // 200 ms
    #define LCD44780_MCP23S08_FIRST_SYNC_DELAY 50   // 50 ms
    #define LCD44780_MCP23S08_SECOND_SYNC_DELAY 10  // 10 ms
    #define LCD44780_MCP23S08_CLEAR_DELAY 20        // 20 ms
    #define LCD44780_MCP23S08_HOME_DELAY 20         // 20 ms
    #define LCD44780_MCP23S08_CMD_DATA_DELAY 100    // 100 us
    #define LCD44780_MCP23S08_BUSY_DELAY 100        // 100 us
#else
    #define LCD44780_MCP23S08_POWERON_DELAY 30      // 30 ms
    #define LCD44780_MCP23S08_FIRST_SYNC_DELAY 5    // 5 ms
    #define LCD44780_MCP23S08_SECOND_SYNC_DELAY 1   // 1 ms
    #define LCD44780_MCP23S08_CLEAR_DELAY 2         // 2 ms
    #define LCD44780_MCP23S08_HOME_DELAY 2          // 2 ms
    #define LCD44780_MCP23S08_CMD_DATA_DELAY 1      // 1 us
    #define LCD44780_MCP23S08_BUSY_DELAY 1          // 1 us
#endif

// Number conversion constants 
#define LCD44780_MCP23S08_ZERO_CLEANING_ON 0x01
#define LCD44780_MCP23S08_ZERO_CLEANING_OFF 0x00

/**
 * @brief This function set the MCP23S08 with internal buffer
 *
 * @warning This function is a Private one. It should not be used by the user.
 */
void LCD44780_MCP23S08_write_buffer_SPI1 (void);

/**
 * @brief
 * This function set the MCP23S08 with internal buffer
 * and before and after setting GPIO respectively up/down the enable
 *
 * @warning This function is a Private one. It should not be used by the user.
 */
void LCD44780_MCP23S08_EN_trigger_write_buffer_SPI1 (void);

/**
 * @brief This function controls if LCD is in busy state
 *
 * @param none
 *
 * @return status 1: LCD is in busy state
 *                0: LCD is free
 */
uint8_t LCD44780_MCP23S08_busy_SPI1 (void);

/**
 * @brief This function set then lower 4bit of buffer, leaves the higher bit intact.
 *
 * @param buffer Byte to be write on MCP23S08
 * 
 * @warning This function is a Private one. It should not be used by the user.
 */
void LCD44780_MCP23S08_set_low_nibble_buffer (uint8_t data);

/**
 * @brief 
 * This function send half byte command pad
 * 4 bit LCD mode, one nibble will be send.
 *
 * @param command Command nibble to be send (only low four bits are used)
 *
 * @warning This function is a Private one. It should not be used by the user.
 */
void LCD44780_MCP23S08_send_nibble_SPI1 (uint8_t command);

/**
 * @brief 
 * This function send a full command pad
 * 4 bit LCD mode, two nibble will be send.
 * High nibble first.
 *
 * @param command Command byte to be send
 *
 * @warning This function is a Private one. It should not be used by the user.
 */
void LCD44780_MCP23S08_send_cmd_SPI1 (uint8_t command);

/**
 * @brief This Function cleans the LCD display.
 *
 */
void LCD44780_MCP23S08_lcd_clear_SPI1 (void);

/**
 * @brief This function locates the cursor at home location. First line first character.
 *
 */
void LCD44780_MCP23S08_lcd_home_SPI1 (void);

/**
 * @brief 
 * This function define the Set entry mode
 * for LCD 44780
 * 
 * @param options constant of relative set for entry modes
 *
 * @note
 * Options:
 * INC_CURSOR - Incremnt cursor after character written
 * DEC_CURSOR - Decrement cursor after character written
 * SHIFT_ON - Switch Cursor shifting on
 * 
 */
void LCD44780_MCP23S08_lcd_emode_SPI1 (uint8_t options);

/**
 * @brief
 * This function define the display mode
 * for LCD 44780
 * 
 * @param options constant of relative set for display modes
 *
 * @note
 * Options:
 * DISPLAY_ON - Turn Display on
 * DISPLAY_OFF - Turn Display off
 * CURSOR_ON  - Turn Cursor on
 * BLINK_ON - Blink Cursor
 * 
 */
void LCD44780_MCP23S08_lcd_dmode_SPI1(uint8_t options);

/**
 * @brief This function define the cursor mode
 * 
 * @param options constant of relative set for cursor modes
 *
 * @note
 * Options:
 * SHIFT_DISP - Shift Display
 * SHIFT_RIGHT - Move cursor right
 * SHIFT_LEFT - Move cursor left
 * 
 */
void LCD44780_MCP23S08_lcd_cmode_SPI1 (uint8_t options);

/**
 * @brief This function define the function settings
 *
 * @param options constant of relative set for the function settings
 * 
 * @note
 * Options:
 * 4BIT_IFACE - 4-bit interface
 * 8BIT_IFACE - 8-bit interface
 * 1_16_DUTY - 1/16 duty 
 * 5X10_DOTS - 5x10 dot characters
 * 
 */
void LCD44780_MCP23S08_lcd_fmode_SPI1 (uint8_t options);

/** 
 * @brief This function initializes the LCD to work in 4 bit modality.
 *
 * @param device_address Address hardware configured for MCP23S08
 *
 * @note You must properly set the microcontroller pins using the TRISx registers.
 */
void LCD44780_MCP23S08_lcd_init_SPI1 (uint8_t device_address);

/**
 * @brief This function shifts the LCD screen on the left or right.
 *
 * @param shift Specify where the shift should be [LCD_LEFT, LCD_RIGHT].
 *
 * @param number_of_shift Specify the number of times the shift is executed.
 *
 * @note 
 * Use the constants LEFT, RIGHT to specify the direction
 * to ensure the compatibility with LCD_44780 library.
 * 
 */
void LCD44780_MCP23S08_shift_SPI1 (uint8_t shift, uint8_t number_of_shift);

/**
 * @brief
 * This function shifts the LCD cursor on the left or right. The position of the cursor is where the
 * next writing will be performed.
 *
 * @param shift Specify where the shift should be [LCD_LEFT, LCD_RIGHT].
 *
 * @param number_of_shift Specify the number of times the shift is executed.
 *
 * @note 
 * Use the constants LEFT, RIGHT to specify the direction
 * to ensure the compatibility with LCD_44780 library.
 * 
 */
void LCD44780_MCP23S08_shift_cursor_SPI1 (uint8_t shift, uint8_t number_of_shift);

/**
 * @brief This function locates the LCD cursor on the selected line. Tested on 20x4 16x2 LCD displays.
 *
 * @param line Specify the number of the line
 *
 * @warning It might not work with all the LCD Displays.
 * 
 */
void LCD44780_MCP23S08_goto_line_SPI1 (uint8_t line);

/**
 * @brief 
 * This function locates the LCD cursor to an arbitrary X Y location.
 * Y represents the line number from top.
 *
 * @param x It Specifies horizontal position
 *
 * @param y It Specifies vertical position (line number)
 *
 * @warning It might not work with all the LCD Displays. Tested on 20x4 16x2 LCD displays.
 * 
 */
void LCD44780_MCP23S08_goto_xy_SPI1 (uint8_t x, uint8_t y);

/**
 * @brief This function writes a char to the LCD display. (e.g LCD_write_char ('a'); )
 *
 * @param value Specify the character to be sent [0-128 ASCII code].
 *
 * @note The function accept ASCII integer or constants 'a'..'z'.
 * 
 */
void LCD44780_MCP23S08_send_data_SPI1 (uint8_t value);

/**
 * @brief This function writes a const string to the LCD display, e.g LCD_write_message ("Hello"); .
 *
 * @param buffer Is a const string written in rom (is not an array).
 *
 * @note 
 * The function accepts strings written in rom (constant), it does not accept array.
 * To write arrays refers the LCD44780_MCP23S08_send_string_SPI1 () function.
 *
 */
void LCD44780_MCP23S08_send_message_SPI1 (const char *buffer);

/**
 * @brief This function writes an array of char to the LCD display, terminated with /0 .
 *
 * @param buffer It is an array of char terminated with /0 .
 *
 * @note
 * The function accepts strings within an array.
 * To use const array within rom use write_message_LCD ().
 *
 */
void LCD44780_MCP23S08_send_string_SPI1 (uint8_t *buffer);

/**
 * @brief This function writes an integer to the LCD display. The integer is converted to string.
 *
 * @param value It is integer that must be written to the LCD display.
 *
 * @param
 * numeber_of_digits It specifies the number of shown digit [0-5].
 * 0: Left Justified
 * 1-5: Right Justified with n digit
 *
 * @param zero_cleaning It specifies whether the left zero must be removed [LCD44780_MCP23S08_ZERO_CLEANING_ON, LCD44780_MCP23S08_ZERO_CLEANING_OFF].
 *
 * @note
 * If you set a number of digit less than required the digit will be lost starting from the less
 * significant digit. Minus is like a digit.
 *
 */
void LCD44780_MCP23S08_write_integer_SPI1 (int16_t value, uint8_t number_of_digits, uint8_t zero_cleaning);

/**
 * @brief This function controls the cursor option (blinking, active)
 *
 * @param active Activate the cursor, showing it or not [LCD_TURN_ON_CURSOR, LCD_TURN_OFF_CURSOR]
 *
 * @param blinking  Let the cursor blink [LCD_BLINK_ON, LCD_BLINK_OFF]
 *
 * @note
 * You must use the constant LCD_TURN_ON_CURSOR, LCD_TURN_OFF_CURSOR, LCD_BLINKING_ON, LCD_BLINKING_OFF
 * to ensure the compatibility with LCD_44780 library.
 *
 */
void LCD44780_MCP23S08_cursor_SPI1 (uint8_t active, uint8_t blinking);

/**
 * @brief This function controls the backligth LED.
 *
 * @param active Activate the LED backlight [LCD_TURN_ON_LED, LCD_TURN_OFF_LED]
 *
 * @param blinking  Let the cursor blink [LCD_BLINKING_ON, LCD_BLINKING_OFF]
 *
 * @note
 * You must use the constant LCD_TURN_ON_LED, LCD_TURN_OFF_LED
 * to ensure the compatibility with LCD_44780 library.
 * 
 */
void LCD44780_MCP23S08_backlight_SPI1 (uint8_t active);

#endif	/* LCD44780_MCP23S08_H */
