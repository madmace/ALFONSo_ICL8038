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

This Header contains all global definition for all modules linked.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef GLOBALS_H
#define	GLOBALS_H

#include <xc.h>                             // include processor files - each processor file is guarded.
#include <stdbool.h>

// **************************************
// Clocks references
//
#define SYSTEM_CLOCK 48000000               // Define main oscillator Frequency 48Mhz
#define UART_CLOCK SYSTEM_CLOCK             // Define clock for UART Module
#define SPI_CLOCK SYSTEM_CLOCK              // Define clock for SPI Module
#define I2C_CLOCK SYSTEM_CLOCK              // Define clock for I2C Module
#define _XTAL_FREQ SYSTEM_CLOCK             // Clock Frequency for _delay functions
#define TCYCLE_CLOCK SYSTEM_CLOCK / 4       // Clock Frequency T Cycle used

// **************************************
// MCU configurations
//
#ifdef __16F88                      // Setup Register Config for 16F88
    #pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
    #pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
    #pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
    #pragma config MCLRE = ON		// RA5/MCLR/VPP Pin Function Select bit: RA5/MCLR/VPP pin function is MCLR
    #pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
    #pragma config CCPMX = RB0		// CCP1 Pin Selection bit: CCP1 function on RB0
    #pragma config DEBUG = OFF		// In-Circuit Debugger Mode bit: In-Circuit Debugger disabled, RB6 and RB7 are general purpose I/O pins
    #pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
    #pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
    #pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
    #pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)

    // Define bit for enable/Disable Weak Pull-Up internal resistors
    #define PULL_UP_ENABLE_BIT OPTION_REGbits.nRBPU
#endif

#ifdef __16F877                      // Setup Register Config for 16F877
#endif

#ifdef __16F877A                     // Setup Register Config for 16F877A
#endif

#ifdef __18F46K22                    // Setup Register Config for 18F46K22
#endif

#ifdef __18F4550                     // Setup Register Config for 18F4550

    // Register: CONFIG1L @ 0x300000
    #pragma config CPUDIV =	OSC1_PLL2   //OSC1_PLL2	[Primary Oscillator Src: /1][96 MHz PLL Src: /2]
    #pragma config PLLDIV =	5           //5	Divide by 5 (20 MHz oscillator input)
    #pragma config USBDIV =	2           //2	USB clock source comes from the 96 MHz PLL divided by 2
    
    // Register: CONFIG1H @ 0x300001
    #pragma config IESO = OFF           //OFF	Oscillator Switchover mode disabled
    #pragma config FOSC = HSPLL_HS      //HSPLL_HS	HS oscillator, PLL enabled (HSPLL)
    #pragma config FCMEN = OFF          //OFF	Fail-Safe Clock Monitor disabled

    // Register: CONFIG2L @ 0x300002
    #pragma config VREGEN = ON          //ON	USB voltage regulator disabled
    #pragma config BOR = OFF            //OFF	Brown-out Reset disabled in hardware and software
    #pragma config BORV = 0             //0     Maximum setting
    #pragma config PWRT = ON            //ON	PWRT enabled

    
    // Register: CCONFIG2H @ 0x300003
    #pragma config WDTPS = 1            //1	1:1
    #pragma config WDT = OFF            //OFF	WDT disabled (control is placed on the SWDTEN bit)

    // Register: CONFIG3H @ 0x300005
    #pragma config CCP2MX =	0           //OFF	CCP2 input/output is multiplexed with RB3
    #pragma config PBADEN =	OFF         //OFF	PORTB<4:0> pins are configured as digital I/O on Reset
    #pragma config LPT1OSC = OFF        //OFF	Timer1 configured for higher power operation
    #pragma config MCLRE = ON           //ON	MCLR pin enabled; RE3 input pin disabled

    // Register: CONFIG4L @ 0x300006
    #pragma config DEBUG = OFF          //OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
    #pragma config STVREN =	ON          //ON	Stack full/underflow will cause Reset
    #pragma config ICPRT =	OFF         //Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit
    #pragma config XINST =	OFF         //OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
    #pragma config LVP = OFF            //OFF	Single-Supply ICSP disabled

    // Register: CONFIG5L @ 0x300008
    #pragma config CP0 = OFF            //OFF	Block 0 (000800-001FFFh) is not code-protected
    #pragma config CP1 = OFF            //OFF	Block 1 (002000-003FFFh) is not code-protected
    #pragma config CP2 = OFF            //OFF	Block 2 (004000-005FFFh) is not code-protected
    #pragma config CP3 = OFF            //OFF	Block 3 (006000-007FFFh) is not code-protected

    // Register: CONFIG5H @ 0x300009
    #pragma config CPD = OFF            //OFF	Data EEPROM is not code-protected
    #pragma config CPB = OFF            //OFF	Boot block (000000-0007FFh) is not code-protected

    // Register: CONFIG6L @ 0x30000A
    #pragma config WRT0 = OFF           //OFF	Block 0 (000800-001FFFh) is not write-protected
    #pragma config WRT1 = OFF           //OFF	Block 1 (002000-003FFFh) is not write-protected
    #pragma config WRT2 = OFF           //OFF	Block 2 (004000-005FFFh) is not write-protected   
    #pragma config WRT3 = OFF           //OFF	Block 3 (006000-007FFFh) is not write-protected

    // Register: CONFIG6H @ 0x30000B
    #pragma config WRTB = OFF           //OFF	Boot block (000000-0007FFh) is not write-protected
    #pragma config WRTC = OFF           //OFF	Configuration registers (300000-3000FFh) are not write-protected
    #pragma config WRTD = OFF           //OFF	Data EEPROM is not write-protected

    // Register: CONFIG7L @ 0x30000C
    #pragma config EBTR0 = OFF          //OFF	Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks
    #pragma config EBTR1 = OFF          //OFF	Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks
    #pragma config EBTR2 = OFF          //OFF	Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks
    #pragma config EBTR3 = OFF          //OFF	Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks

    // Register: CONFIG7H @ 0x30000D
    #pragma config EBTRB = OFF          //OFF	Boot block (000000-0007FFh) is not protected from table reads executed in other blocks

    // Define bit for enable/Disable Weak Pull-Up internal resistors
    #define PULL_UP_ENABLE_BIT INTCON2bits.RBPU

    // **************************************
    // USART Debug definition 
    //
    // Used for enable printf() to serial console
    // 
    // Warning ! If definited take USART and RC6/TX/CK
    //
    //#define ENABLE_USART_PRINTF

    // **************************************
    // Timers definitions
    //

    // Timers available
    #define TMR0_AVAILABLE
    #define TMR1_AVAILABLE
    #define TMR3_AVAILABLE

    // Timer1, Timer3 interrupts module definitions
    #define TMR0_INTERRUPT
    #define TMR1_INTERRUPT
    #define TMR3_INTERRUPT

    // **************************************
    // USB Library definitions
    //

    // Fixed addresses for USB Buffer
    #define FIXED_ADDRESS_MEMORY

    #if(__XC8_VERSION < 2000)
        #define IN_DATA_BUFFER_ADDRESS_TAG      @0x500
        #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x540
        #define CONTROL_BUFFER_ADDRESS_TAG      @0x580
        #define DRIVER_DATA_ADDRESS_TAG         @0x588
    #else
        #define IN_DATA_BUFFER_ADDRESS_TAG      __at(0x500)
        #define OUT_DATA_BUFFER_ADDRESS_TAG     __at(0x540)
        #define CONTROL_BUFFER_ADDRESS_TAG      __at(0x580)
        #define DRIVER_DATA_ADDRESS_TAG         __at(0x588)
    #endif

    // **************************************
    // SPI Library definitions
    // 

    // Only 1 SPI Port available
    #define SPI1_AVAILABLE

    // Common 4 wires (SS for Slave Mode)
    #define SPI1_SCK_LINE_TRIS TRISBbits.RB1
    #define SPI1_SDI_LINE_TRIS TRISBbits.RB0
    #define SPI1_SDO_LINE_TRIS TRISCbits.RC7
    #define SPI1_SS_LINE_TRIS TRISAbits.RA5

    // **************************************
    // I2C Library definitions
    //

    // Only 1 I2C Port available
    #define I2C1_AVAILABLE
    
    // Common 2 Wires (Clock and Data)
    #define I2C1_SDA_LINE_TRIS TRISBbits.RB0              
    #define I2C1_SCL_LINE_TRIS TRISBbits.RB1

    // **************************************
    // CCP Library definitions
    //

    // 2 CCP Ports available
    #define CCP1_AVAILABLE
    #define CCP2_AVAILABLE

    // Capture/Compare/PWM CCP1 module definitions
    #define CCP1_INTERRUPT
    #define CCP2_INTERRUPT

    // CCP lines
    #define CCP1_LINE_TRIS TRISCbits.RC2
    #define CCP2_LINE_TRIS TRISCbits.RC1
    
#endif

#ifdef __18F14K50                    // Setup Register Config for 18F14K50
#endif

#ifdef __18F4580                     // Setup Register Config for 18F4580
#endif

#endif	/* GLOBALS_H */
