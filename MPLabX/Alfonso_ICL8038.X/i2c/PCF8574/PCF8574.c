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

This source contains I2C Library functions implementations for
Remote 8bit I/O Expander I2C with interrupt series
PCF8574/PCF8574A

*******************************************************************************/

#include "PCF8574.h"

// PCF8574_I2C1_write_data Implementation
int8_t PCF8574_I2C1_write_data (uint8_t device_address, uint8_t data ) {
		
    // Start Condition and control if bytes are sent

    I2C1_wait_bus_IDLE();
	             
	I2C1_start_bit();     
	
  	if (I2C1_check_bus_collision()) {
        return (-1);
    }

	if (I2C1_write_byte(PCF8574_INTERNAL_ADDRESS | (uint8_t)(device_address << 1))) {
        return (-1);
    }
    
    // Data Byte is sent
    
    I2C1_wait_bus_IDLE();
      
    if (!I2C1_check_ACK ()) {
	    
        if (I2C1_write_byte(data)) {
            return (-1);
        }
    } else {
        return (-1);       
    }
    
    // Stop command is sent
    
	I2C1_wait_bus_IDLE();
    
  	if (!I2C1_check_ACK()) {
	
        I2C1_stop_bit();
  
    } else {
        return (-1);     
    }
  
    if (I2C1_check_bus_collision()) {
        return (-1);
    }
  
    return (0);                   
}

#ifdef I2C2_AVAILABLE
int8_t PCF8574_I2C2_write_data (uint8_t device_address, uint8_t data ) {
		
    // Start Condition and control if bytes are sent

    I2C2_wait_bus_IDLE();
	             
	I2C2_start_bit();      
	
  	if (I2C2_check_bus_collision()) {
        return (-1);
    }

	if (I2C2_write_byte(PCF8574_INTERNAL_ADDRESS | (device_address << 1))) {
        return (-1);
    }
    
    // Data Byte is sent
    
    I2C2_wait_bus_IDLE();
      
    if (!I2C2_check_ACK ()) {
	    
        if (I2C2_write_byte(data)) {
            return (-1);
        }
    } else {
        return (-1);            
    }
    
    // Stop command is sent
    
	I2C2_wait_bus_IDLE();
                   
  	if (!I2C2_check_ACK()) {
	
        I2C2_stop_bit();
  
    } else {
        return (-1);
    }
  
    if (I2C2_check_bus_collision()) {
        return (-1);
    }
  
    return (0);                   
}
#endif

// PCF8574_I2C1_read_data Implementation
int8_t PCF8574_I2C1_read_data (uint8_t device_address, uint8_t *data){
	
    uint8_t control_byte;

    control_byte = PCF8574_INTERNAL_ADDRESS | (uint8_t)(device_address << 1);
    
    // Start Condition and control if bytes are sent
    
	I2C1_wait_bus_IDLE();
              
	I2C1_start_bit();
  
	if (I2C1_check_bus_collision()) {
        return (-1);
	}
	
	if (I2C1_write_byte(control_byte + 1)) {
        return (-1);
	}

    // Data is Read

	I2C1_wait_bus_IDLE();
       
    if (!I2C1_check_ACK()) {

        // 1 byte reception
        I2C1_set_master_as_receiver();

        // Send not ACK condition 
        I2C1_negative_ACK();

        I2C1_stop_bit();

        if (I2C1_check_bus_collision()) {
            return (-1);
        }         

    } else {
        return (-1);
    }   
	
	*data = I2C1_read_byte();
    
	return (0);
}

#ifdef I2C2_AVAILABLE
int8_t PCF8574_I2C2_read_data (uint8_t device_address, uint8_t *data){
	
    uint8_t control_byte;

    control_byte = PCF8574_INTERNAL_ADDRESS | (device_address << 1);
    
    // Start Condition and control if bytes are sent
    
	I2C2_wait_bus_IDLE();
              
	I2C2_start_bit();
  
	if (I2C2_check_bus_collision()) {
        return (-1);
	}
	
	if (I2C2_write_byte(control_byte + 1)) {
        return (-1);
	} 

    // Data is Read

	I2C2_wait_bus_IDLE();
       
    if (!I2C2_check_ACK()) {

        // 1 byte reception
        I2C2_set_master_as_receiver();

        // Send not ACK condition 
        I2C2_negative_ACK();

        I2C2_stop_bit();

        if (I2C2_check_bus_collision()) {
            return (-1);
        }

    } else {
        return (-1);
    }   
	
	*data = I2C2_read_byte();
    
	return (0);
}
#endif
