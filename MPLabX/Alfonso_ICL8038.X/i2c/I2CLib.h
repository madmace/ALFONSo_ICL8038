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

This Header contains I2C Library functions.

*******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef I2CLIB_H
#define	I2CLIB_H

#include <xc.h>
#include "globals.h"

// Device type
#define I2C_SLAVE_7_BIT_ADDRESS     0x06
#define I2C_SLAVE_10_BIT_ADDRESS    0x07    	
#define I2C_MASTER                  0x08     	

/****************************************************
 *
 * This function Opens the I2C module enabling SCL and SDA lines. 
 *
 * @param device_type It specifies if the device is a Master or a Slave [I2C_MASTER, I2C_SLAVE_7_BIT_ADDRESS, I2C_SLAVE_10_BIT_ADDRESS] 
 *
 *
 * @return void
 *
 * @Note
 * You must use the constants I2C_MASTER, I2C_SLAVE_7_BIT_ADDRESS, I2C_SLAVE_10_BIT_ADDRESS.
 * By default the slew rate is turned on to support communications up to 400KHz.
 *
 */
void I2C1_open (uint8_t device_type);
#ifdef I2C2_AVAILABLE
    void I2C2_open (uint8_t device_type);
#endif

 /**
 * This function Closes the I2C module. 
 *
 * @param none
 *
 * @return void
 *
 */
void I2C1_close (void);
#ifdef I2C2_AVAILABLE 
    void I2C2_close (void);
#endif

/**
 * This function sets the bus baudrate in case the device is a Master device. 
 *
 * @param bus_baud_rate_KHZ Baud Rate is in KHz [min: 1, max:400]
 *
 * @return void
 * 
 * @Warning
 * You must not set the baudrate for a slave device. Doing so may change the slave address. 
 *
 */  
void I2C1_baud_rate (uint16_t bus_baud_rate_KHz);
#ifdef I2C2_AVAILABLE 
    void I2C2_baud_rate (uint16_t bus_baud_rate_KHz);
#endif

/**
 * This function sets I2C slave address. 
 *
 * @param device_address Slave Address 
 *
 * @return void
 * 
 */     
void I2C1_set_slave_address (uint16_t device_address);
#ifdef I2C2_AVAILABLE 
    void I2C2_set_slave_address (uint16_t device_address);
#endif

/**
 * This macro reads the input buffer.
 *
 * @param void
 *
 * @return Input buffer value
 *
 */  
#define I2C1_read_byte() (SSPBUF)
#ifdef I2C2_AVAILABLE 
    #define I2C2_read_byte() (SSP2BUF)
#endif

/**
 * This function writes a byte to the output buffer and performs several error tests.
 *
 * @param byte_to_send Byte to be sent out
 *
 * @return error 0: ACK received for the byte sent out
 *              -1: Bus Conflict occurs  
 *              -2: NACK has been received
 *              -3: Unknown Error
 *
 */    
int8_t I2C1_write_byte (uint8_t byte_to_send);
#ifdef I2C2_AVAILABLE 
    int8_t I2C2_write_byte (uint8_t byte_to_send);
#endif

 /**
 * This function waits for the bus to be Idle before continuing. 
 *
 * @param void
 *
 * @return void
 *
 */  
void I2C1_wait_bus_IDLE (void);
#ifdef I2C2_AVAILABLE 
    void I2C2_wait_bus_IDLE (void);
#endif  

/**
 * This function releases the start bit and waits until Start bit is out (idle). 
 *
 * @param void
 *
 * @return void
 *
 * @Warning
 * This is a blocking function.
 * 
 */     
void I2C1_start_bit (void);
#ifdef I2C2_AVAILABLE 
    void I2C2_start_bit (void);
#endif   
    
    
 /**
 * This function releases the stop bit and waits until Stop bit is out (idle). 
 *
 * @param void
 *
 * @return void
 *
 * @Warning
 * This is a blocking function.
 *
 */     
void I2C1_stop_bit (void);
#ifdef I2C2_AVAILABLE 
    void I2C2_stop_bit (void);
#endif
    
/**
 * This function resets the write collision bit.
 *
 * @param void
 *
 * @return void
 *
 */     
void I2C1_reset_write_collision_flag (void);
 
#ifdef I2C2_AVAILABLE 
    void I2C2_reset_write_collision_flag (void);
#endif
    
/**
 * This function write a byte to an external device made of 1 control byte, 1 address byte and 1 byte data.
 *
 * @param control_byte Control byte of the external device
 *        register_address Address to be written within the external device
 *        data Data to be written within the pointed address                  
 *
 * @return error Communication error
 *               0: No communication error
 *              -1: Bus Collision error 
 *              -2: Not ACK Error
 *              -3: Write Collision
 */     
int8_t I2C1_write_byte_to_external_device (uint8_t control_byte, uint8_t register_address, uint8_t data);
#ifdef I2C2_AVAILABLE 
    int8_t I2C2_write_byte_to_external_device (uint8_t control_byte, uint8_t register_address, uint8_t data);
#endif   
    
    
/**
 * This function read a byte from an external device made of 1 control byte, 1 address byte.
 *
 * @param control_byte Control byte of the external device
 *        register_address Address to be written within the external device
 *        data pointer to the variable where the read data will be written into. 
 * 
 * @return error Communication error or data byte
 *               0: No communication error
 *              -1: Bus Collision error 
 *              -2: Not ACK Error
 *              -3: Write Collision               
 *
 * @return void
 *
 */     
int8_t I2C1_read_byte_from_external_device (uint8_t control_byte, uint8_t register_address, uint8_t *data);
#ifdef I2C2_AVAILABLE 
    int8_t  I2C2_read_byte_from_external_device (uint8_t control_byte, uint8_t register_address, uint8_t *data);
#endif   
   
/**
 * This function write a word (16bits) to an external device made of 1 control byte, 1 address byte and 2 bytes of data.
 *
 * @param control_byte Control byte of the external device
 *        register_address Address to be written within the external device
 *        data Data to be written within the pointed address                  
 *
 * @return error Communication error
 *               0: No communication error
 *              -1: Bus Collision error 
 *              -2: Not ACK Error
 *              -3: Write Collision
 */     
int8_t I2C1_write_word_to_external_device (uint8_t control_byte, uint8_t register_address, uint16_t data);
#ifdef I2C2_AVAILABLE 
    int8_t I2C2_write_word_to_external_device (uint8_t control_byte, uint8_t register_address, uint16_t data);
#endif

/**
 * This function read a word (16 bits) from an external device made of 1 control byte, 1 address byte.
 *
 * @param control_byte Control byte of the external device
 *        register_address Address to be written within the external device
 *        data pointer to the variable where the read data will be written into. 
 * 
 * @return error Communication error or data byte
 *               0: No communication error
 *              -1: Bus Collision error 
 *              -2: Not ACK Error
 *              -3: Write Collision               
 *
 * @return void
 *
 */     
int8_t I2C1_read_word_from_external_device (uint8_t control_byte, uint8_t register_address, uint16_t *data);
#ifdef I2C2_AVAILABLE 
    int8_t  I2C2_read_word_from_external_device (uint8_t control_byte, uint8_t register_address, uint16_t *data);
#endif       
    
/**
 * This macro checks if there is any data ready in the RX buffer.
 *
 * @param void
 *
 * @return flag It returns data ready flag. 
 *              0: Buffer is empty
 *              1: Buffer is full
 */     
#define I2C1_check_data_ready() (SSPSTATbits.BF)
#ifdef I2C2_AVAILABLE 
    #define I2C2_check_data_ready() (SSP2STATbits.BF)
#endif
    
/**
 * This macro checks if received command is a read or write operation.
 *
 * @param void
 *
 * @return flag It returns RW flag. 
 *              0: Write Command
 *              1: Read Command
 *
 */     
#define I2C1_check_read_write_operation() (SSPSTATbits.R_W)
#ifdef I2C2_AVAILABLE 
    #define I2C2_check_read_write_operation() (SSP2STATbits.R_W)
#endif

/**
 * This macro checks if the stop bit has been detected.
 *
 * @param void
 *
 * @return flag It returns Stop bit flag. 
 *              0: Stop bit is not detected
 *              1: Stop bit has been detected
 *
 */      
#define I2C1_check_stop_bit() (SSPSTATbits.P)
#ifdef I2C2_AVAILABLE 
    #define I2C2_check_stop_bit() (SSP2STATbits.P)
#endif
    
 /**
 * This macro checks if the start bit has been detected.
 *
 * @param void
 *
 * @return flag It returns Start bit flag. 
 *              0: Start bit is not detected
 *              1: Start bit has been detected
 */    
#define I2C1_check_start_bit() (SSPSTATbits.S)
#ifdef I2C2_AVAILABLE 
    #define I2C2_check_start_bit() (SSP2STATbits.S)
#endif 

/**
 * This macro checks if a bus collision happened.
 *
 * @param void
 *
 * @return flag It returns the bus collision status. 
 *              0: Normal transmission
 *              1: Bus collision has been detected
 *
 */
#define I2C1_check_bus_collision() (PIR2bits.BCLIF)
#ifdef I2C2_AVAILABLE 
    #define I2C2_check_bus_collision() (PIR3bits.BCL2IF)
#endif

#ifdef COMPILER_XC32
    #define I2C1_check_bus_collision() (I2C1STATbits.BCL)

    #ifdef I2C2_AVAILABLE 
        #define I2C2_check_bus_collision() (I2C2STATbits.BCL)
    #endif 
#endif    
 
/**
 * This macro checks if the ACK has been received.
 *
 * @param void
 *
 * @return flag It returns the ACK status. 
 *              0: ACK has been received
 *              1: ACK has not been received
 */     
#define I2C1_check_ACK() (SSPCON2bits.ACKSTAT)
#ifdef I2C2_AVAILABLE 
    #define I2C2_check_ACK() (SSP2CON2bits.ACKSTAT)
#endif
    
/**
 * This macro restarts the I2C module
 *
 * @param void
 *
 * @return void
 */     
#define I2C1_restart_communication() SSPCON2bits.RSEN = 1; while(SSPCON2bits.RSEN)
#ifdef I2C2_AVAILABLE 
    #define I2C2_restart_communication() SSP2CON2bits.RSEN = 1; while(SSP2CON2bits.RSEN)
#endif

 /**
 * This macro releases an ACK sequence 
 *
 * @param void
 *
 * @return void
 *
 */ 
#define I2C1_ACK() SSPCON2bits.ACKDT = 0, SSPCON2bits.ACKEN = 1; while(SSPCON2bits.ACKEN)
#ifdef I2C2_AVAILABLE 
    #define I2C2_ACK() SSP2CON2bits.ACKDT = 0, SSP2CON2bits.ACKEN = 1; while(SSP2CON2bits.ACKEN)
#endif  
    
/**
 * This macro releases a negative ACK sequence NACK
 *
 * @param void
 *
 * @return void
 *
 */ 
#define I2C1_negative_ACK() SSPCON2bits.ACKDT = 1, SSPCON2bits.ACKEN = 1;while(SSPCON2bits.ACKEN)
#ifdef I2C2_AVAILABLE 
    #define I2C2_negative_ACK() SSP2CON2bits.ACKDT = 1, SSP2CON2bits.ACKEN = 1; while(SSP2CON2bits.ACKEN)
#endif      
    
/**
 * This macro sets the I2C module as receiver to enable the data read (read sequence).
 *
 * @param void
 *
 * @return void
 *
 */
#define I2C1_set_master_as_receiver()  SSPCON2bits.RCEN = 1; while (SSPCON2bits.RCEN)
#ifdef I2C2_AVAILABLE 
    #define I2C2_set_master_as_receiver() SSP2CON2bits.RCEN = 1; while (SSP2CON2bits.RCEN)
#endif
    
#endif	/* I2CLIB_H */

