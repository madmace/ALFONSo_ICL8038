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

This source contains SPI Library functions implementations.

*******************************************************************************/

#include "I2CLib.h"

// I2C1_open Implementation
void I2C1_open (uint8_t device_type) {
  
    uint8_t dummy_read;
    
    // IO pin initialization
    I2C1_SDA_LINE_TRIS = 0x1;             
    I2C1_SCL_LINE_TRIS = 0x1;
    
    // Register initialization (Starting known value)
    SSPSTAT &= 0x3F;                
    SSPCON1 = 0x00;
    SSPCON2 = 0x00;                
    
    // Device definition Master or Slave   
    SSPCON1 |= device_type; 
    
    // Slew Rate Control set to ON by default
    // Disabled for Standard Speed mode (100 kHz and 1 MHz)
    SSPSTATbits.SMP = 0x1;                
  
    // Enable the I2C Module
    SSPCON1bits.SSPEN = 0x1;
    
    // Clear input buffer
    dummy_read = I2C1_read_byte();
}

#ifdef I2C2_AVAILABLE
void I2C2_open (uint8_t device_type) {
    
    uint8_t dummy_read;
    
    // IO pin initialization
    I2C2_SDA_LINE_TRIS = 0x01;             
    I2C2_SCL_LINE_TRIS = 0x01; 
    
    // Register initialization (Starting known value)
    SSP2STAT &= 0x3F;                
    SSP2CON1 = 0x00;                 
    SSP2CON2 = 0x00;                
    
    // Device definition Master or Slave   
    SSP2CON1 |= device_type;
    
    // Slew Rate Control set to ON by default
    // Disabled for Standard Speed mode (100 kHz and 1 MHz)
    SSP2STATbits.SMP = 0x1;                
  
    // Enable the I2C Module
    SSP2CON1bits.SSPEN = 0x1;
    
    // Clear input buffer
    dummy_read = I2C2_read_byte(); 
}
#endif

// I2C1_close Implementation
void I2C1_close (void) {
    
    //Disable I2C module
    SSPCON1bits.SSPEN = 0x0;
}

#ifdef I2C2_AVAILABLE 
void I2C2_close (void) {
    
    //Disable I2C module
    SSP2CON1bits.SSPEN = 0x0; 
}
#endif

// I2C1_baud_rate Implementation
void I2C1_baud_rate (uint16_t bus_baud_rate_KHz){
    
    uint16_t div_a = (uint16_t) (I2C_CLOCK /1000);
    uint16_t div_b = (4 * bus_baud_rate_KHz);    
    SSPADD = (uint8_t)(div_a / div_b) - 1;
}

#ifdef I2C2_AVAILABLE 
void I2C2_baud_rate (uint16_t bus_baud_rate_KHz){
    uint16_t div_a = (uint16_t) (I2C_CLOCK /1000);
    uint16_t div_b = (4 * bus_baud_rate_KHz); 
    SSP2ADD = (uint8_t) (div_a / div_b) - 1;
}
#endif

// I2C1_set_slave_address Implementation
void I2C1_set_slave_address (uint16_t device_address) {
    
    //Only one byte address is supported
    SSPADD = (uint8_t) device_address;
}

#ifdef I2C2_AVAILABLE 
void I2C2_set_slave_address (uint16_t device_address) {
    SSP2ADD = (uint8_t) device_address;
}
#endif

// I2C1_start_bit Implementation
void I2C1_start_bit (void) {
    
    SSPCON2bits.SEN = 0x1;
    //Waits until start bit is in idle
    while(SSPCON2bits.SEN);
}

#ifdef I2C2_AVAILABLE 
void I2C2_start_bit (void) {
    SSP2CON2bits.SEN = 0x1;
    //Waits until start bit is in idle
    while(SSP2CON2bits.SEN);
}
#endif

// I2C1_stop_bit Implementation
void I2C1_stop_bit (void) {
    SSPCON2bits.PEN = 0x1;
    while(SSPCON2bits.PEN);
}

#ifdef I2C2_AVAILABLE 
void I2C2_stop_bit (void) {
    SSP2CON2bits.PEN = 0x1;
    while(SSP2CON2bits.PEN);
}
#endif

// I2C1_write_byte Implementation
int8_t I2C1_write_byte (uint8_t byte_to_send) {
      
    // Writes the data to the output buffer
    SSPBUF = byte_to_send;           
    
    // Check for collision errors
    if (SSPCON1bits.WCOL)      
        return (-1);              
    else {
        // Slave mode only 
        if (((SSPCON1 & 0x0F) != 0x08) && ((SSPCON1 & 0x0F) != 0x0B)) {

            // Release clock line   
            SSPCON1bits.CKP = 0x1;       
      
            // Wait until the nineth clock pulse is received
            while (!PIR1bits.SSPIF);  
      
            // If R/W=0 and BF=0, NOT ACK was received
            if ((!SSPSTATbits.R_W) && (!SSPSTATbits.BF)) {
                return (-2);             
            }	
            else 
                return(0);		
        } else {   
            // Master mode only	    
            if (((SSPCON1 & 0x0F) == 0x08) || ((SSPCON1 & 0x0F) == 0x0B)) {
                
                // Wait until write cycle is complete    
                while(SSPSTATbits.BF);   
        
                I2C1_wait_bus_IDLE();                  
       
                // Test for ACK condition received
                if (SSPCON2bits.ACKSTAT ) 
                    return (-2);				
                else 
                    return (0);             
            }
        }
    }
    
    //Unknown Error  
    return (-3);  
}

#ifdef I2C2_AVAILABLE 
int8_t I2C2_write_byte (uint8_t byte_to_send) {
    
    // Writes the data to the output buffer
    SSP2BUF = byte_to_send;           
    
    // Check for collision errors
    if (SSP2CON1bits.WCOL)      
        return (-1);              
    else {
        // Slave mode only 
        if (((SSP2CON1 & 0x0F) != 0x08) && ((SSP2CON1 & 0x0F) != 0x0B)) {
            // Release clock line 
            SSP2CON1bits.CKP = 0x1;        
      
            // Wait until ninth clock pulse received
            while (!PIR3bits.SSP2IF);  
      
            // If R/W=0 and BF=0, NOT ACK was received
            if ((!SSP2STATbits.R_W) && (!SSP2STATbits.BF)) {
                return (-2);             
            }	
            else 
                return(0);		
        }
        else {
            // Master mode only	    
            if(((SSP2CON1 & 0x0F) == 0x08) || ((SSP2CON1 & 0x0F) == 0x0B)) {
        
                // Wait until write cycle is complete   
                while(SSP2STATbits.BF);    
        
                I2C2_wait_bus_IDLE(); 
        
                // Test for ACK condition received
                if (SSP2CON2bits.ACKSTAT) 
                    return (-2);				
                else 
                    return (0);
            }
        }
    }
    
    // Unknown Error  
    return (-3);  
}
#endif

// I2C1_wait_bus_IDLE Implementation
void I2C1_wait_bus_IDLE (void) {
    while((SSPCON2 & 0x1F) | (SSPSTATbits.R_W));
}

#ifdef I2C2_AVAILABLE
void I2C2_wait_bus_IDLE (void) {
    while((SSP2CON2 & 0x1F) | (SSP2STATbits.R_W));
}
#endif

// I2C1_reset_write_collision_flag Implementation
void I2C1_reset_write_collision_flag (void) {
    SSPCON1bits.WCOL = 0x0;
}
 
#ifdef I2C2_AVAILABLE 
void I2C2_reset_write_collision_flag (void) {
    SSP2CON1bits.WCOL = 0x0;       
}
#endif

// I2C1_write_byte_to_external_device Implementation
int8_t I2C1_write_byte_to_external_device (uint8_t control_byte, uint8_t register_address, uint8_t data) {
  
    I2C1_wait_bus_IDLE();                     
    I2C1_start_bit();                     
  
    // Test for bus collision
    if (PIR2bits.BCLIF) {
        return (-1);                
    }
    else {
        // write byte - R/W bit should be 0    
        if (I2C1_write_byte(control_byte)) {
            I2C1_stop_bit(); 
            return (-3);              
        }

        // Test for ACK condition received
        if (!SSPCON2bits.ACKSTAT) { 
            if (I2C1_write_byte(register_address)) {
                I2C1_stop_bit(); 
                return (-3);            
            }
            
            // Test for ACK condition received
            if (!SSPCON2bits.ACKSTAT ) { 
                if (I2C1_write_byte(data)) {
                    I2C1_stop_bit(); 
                    return (-3);          
                }
            } else {
                I2C1_stop_bit(); 
                return (-2);            
            }
        } else {
            I2C1_stop_bit(); 
            return (-2);              
        }
    }

    I2C1_stop_bit();                      

    // Test for bus collision
    if (PIR2bits.BCLIF) {
        return (-1);                
    }
    
    return (0);                   
}
 
#ifdef I2C2_AVAILABLE 
int8_t I2C2_write_byte_to_external_device (uint8_t control_byte, uint8_t register_address, uint8_t data) {
    
    I2C2_wait_bus_IDLE();                     
    I2C2_start_bit();                     
  
    // Test for bus collision
    if (PIR3bits.BCL2IF){
        return (-1);                
    }
    else {
        // Write byte - R/W bit should be 0    
        if (I2C2_write_byte(control_byte)) {
            I2C2_stop_bit(); 
            return (-3);              
        }

        // Test for ACK condition received
        if (!SSP2CON2bits.ACKSTAT) {   
            if (I2C2_write_byte(register_address)) {
                I2C2_stop_bit(); 
                return (-3);            
            }
          
            // Test for ACK condition received
            if (!SSP2CON2bits.ACKSTAT) { 
                if (I2C2_write_byte(data)) {
                    I2C2_stop_bit(); 
                    return (-3);          
                }
            } else {
                I2C2_stop_bit(); 
                return (-2);            
            }
        } else {
            I2C2_stop_bit(); 
            return (-2);              
        }
    }

    I2C2_stop_bit();                      

    // Test for bus collision
    if (PIR3bits.BCL2IF) {
        return (-1);                
    }
    
    return (0);       
}
#endif

// I2C1_read_byte_from_external_device Implementation
int8_t I2C1_read_byte_from_external_device (uint8_t control_byte, uint8_t register_address, uint8_t *data) {
   
    I2C1_wait_bus_IDLE();                     
    I2C1_start_bit();                     

    // Test for bus collision
    if (PIR2bits.BCLIF) {
        return (-1);                
    } else {
        if (I2C1_write_byte(control_byte)) {
            I2C1_stop_bit(); 
            return (-3);             
        }
        
        // Check for ACK condition
        if (!SSPCON2bits.ACKSTAT) {
            // WRITE word address for EEPROM 
            if (I2C1_write_byte(register_address)) {
                I2C1_stop_bit(); 
                return (-3);            
            }
            
            // Check for ACK condition
            if (!SSPCON2bits.ACKSTAT) {
              
                I2C1_restart_communication();            
            
                // Test for bus collision
                if (PIR2bits.BCLIF) {
                    return (-1);         
                }

                // Write 1 byte - R/W bit should be 1
                if (I2C1_write_byte(control_byte + 1)) {
                    I2C1_stop_bit(); 
                    return (-3);         
                }

                // Check for ACK condition
                if (!SSPCON2bits.ACKSTAT) {
                    // Enable master for 1 byte reception  
                    SSPCON2bits.RCEN = 1;   
                    // Check that receive sequence is over
                    while (SSPCON2bits.RCEN); 

                    // Send ACK condition
                    I2C1_negative_ACK();    

                    // Send STOP condition
                    I2C1_stop_bit();             

                    // Test for bus collision
                    if (PIR2bits.BCLIF) {
                        return (-1);         
                    }
                } else {
                    I2C1_stop_bit(); 
                    return (-2);          
                }
            } else {
                I2C1_stop_bit(); 
                return (-2);           
            }
        } else {
            I2C1_stop_bit(); 
            return (-2);              
        }
    }
    
    // if no error occurred the data is valid!
    *data = SSPBUF;
    
    return (0);     
}
 
#ifdef I2C2_AVAILABLE 
int8_t I2C2_read_byte_from_external_device (uint8_t control_byte, uint8_t register_address, uint8_t *data) {
    I2C2_wait_bus_IDLE();                     
    I2C2_start_bit();                     

    // Test for bus collision
    if (PIR3bits.BCL2IF) {
        return (-1);           
    } else {
        if (I2C2_write_byte(control_byte)) {
            I2C2_stop_bit(); 
            return (-3);             
        }
        
        // Check for ACK condition
        if (!SSP2CON2bits.ACKSTAT) {
            // WRITE word address for EEPROM 
            if (I2C2_write_byte(register_address)) {
                I2C2_stop_bit(); 
                return (-3);
            }
        
            // Check for ACK condition
            if (!SSP2CON2bits.ACKSTAT) {
              
                I2C2_restart_communication();            
            
                // Test for bus collision
                if (PIR3bits.BCL2IF) {
                    return (-1);         
                }

                // Write 1 byte - R/W bit should be 1
                if (I2C2_write_byte(control_byte + 1)) {
                    I2C1_stop_bit(); 
                    return (-3);         
                }

                // Check for ACK condition
                if (!SSP2CON2bits.ACKSTAT) {
                    // Enable master for 1 byte reception  
                    SSP2CON2bits.RCEN = 1;   
                    // Check that receive sequence is over
                    while (SSP2CON2bits.RCEN); 

                    // Send ACK condition
                    I2C2_negative_ACK();    

                    // Send STOP condition
                    I2C2_stop_bit();             

                    // Test for bus collision
                    if (PIR3bits.BCL2IF) {
                        return (-1);         
                    }
                } else {
                    I2C2_stop_bit(); 
                    return (-2);          
                }
            } else {
                I2C2_stop_bit(); 
                return (-2);           
            }
        } else {
            I2C2_stop_bit(); 
            return (-2);              
        }
    }
    
    // if no error occurred the data is valid!
    *data = SSP2BUF;
    
    return (0);  
}
#endif
