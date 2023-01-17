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

#include "SPILib.h"

// SPI_open Implementation
void SPI1_open (uint8_t device_type) {
    
    uint8_t data;  
    
    //IO pin initialization    
    if (device_type == SPI_MASTER_DEVICE) {
        SPI1_SCK_LINE_TRIS = 0x0;
        SPI1_SDI_LINE_TRIS = 0x1;
        SPI1_SDO_LINE_TRIS = 0x0;   
        SPI1_SS_LINE_TRIS = 0x0;
    } 
   
    if (device_type == SPI_SLAVE_DEVICE) {
        SPI1_SCK_LINE_TRIS = 0x1;
        SPI1_SDI_LINE_TRIS = 0x1;
        SPI1_SDO_LINE_TRIS = 0x0;
        SPI1_SS_LINE_TRIS = 0x1;
        
        //SS initialization by Slave mode
        SSPCON1 &= 0xF0;
        SSPCON1 |= SPI_SLAVE_SS_DISABLED;
    } 
   
    //Clear the register by reading it out
    data = SSPBUF;    
    
    //Clear history
    PIR1bits.SSPIF = 0x0;        
    SSPCON1bits.WCOL = 0x0;	
    SSPCON1bits.SSPOV = 0x0;
    
    //Data sampling in the middle of the bit
    SSPSTATbits.SMP = 0x0;
    
    //Enable SPI module 
    SSPCON1bits.SSPEN = 0x1; 
}

#ifdef SPI2_AVAILABLE
void SPI2_open (uint8_t device_type) {
    
    uint8_t data;  

    //IO pin initialization    
    if (device_type == SPI_MASTER_DEVICE){
        SPI2_SCK_LINE_TRIS = 0x0;
        SPI2_SDI_LINE_TRIS = 0x1;
        SPI2_SDO_LINE_TRIS = 0x0;
        SPI2_SS_LINE_TRIS = 0x0;
    } 

    if (device_type == SPI_SLAVE_DEVICE){
        SPI2_SCK_LINE_TRIS = 0x1;
        SPI2_SDI_LINE_TRIS = 0x1;
        SPI2_SDO_LINE_TRIS = 0x0;
        SPI2_SS_LINE_TRIS = 0x1;

        //SS initialization by Slave mode
        SSP2CON1 &= 0xF0;
        SSP2CON1 |= SPI_SLAVE_SS_DISABLED;

   } 

    //Clear the register by reading it out
    data = SSP2BUF;    

    //Clear history
    PIR3bits.SSP2IF = 0x0;        
    SSP2CON1bits.WCOL = 0x0;	
    SSP2CON1bits.SSPOV = 0x0;

    //Data sampling in the middle of the bit
    SSP2STATbits.SMP = 0x0;

    //Enable SPI module 
    SSP2CON1bits.SSPEN = 0x1; 
}
#endif


// SPI1_close Implementation
void SPI1_close (void) {
   
   //Disable SPI module 
   SSPCON1bits.SSPEN = 0x0;
}

#ifdef SPI2_AVAILABLE
void SPI2_close (void) {

   //Disable SPI module 
   SSP2CON1bits.SSPEN = 0x0;
}
#endif

// SPI1_baudrate Implementation
void SPI1_baudrate (uint8_t baudrate) {
    
    SSPCON1 &= 0xF0;     //0b11110000
    SSPCON1 |= baudrate;    
}

#ifdef SPI2_AVAILABLE
void SPI2_baudrate (uint8_t baudrate) {

    SSP2CON1 &= 0xFC;   //0b11110000
    SSP2CON1 |= baudrate;
}
#endif

// SPI1_mode Implementation
void SPI1_mode (uint8_t communication_mode) {
    
    // CKP : Clock Polarity Select bit
    // 1 = Idle state for clock is a high level
    // 0 = Idle state for clock is a low level
    
    // CKE : SPI Clock Select Edge
    // 1 = Transmit occurs on transition from active to Idle clock state
    // 0 = Transmit occurs on transition from Idle to active clock state
    
    // SPI Modes    CKP CKE
    // 0, 0         0   1
    // 0, 1         0   0
    // 1, 0         1   1
    // 1, 1         1   0
    
    SSPSTATbits.CKE = 0x0;
    
    switch (communication_mode) {
        
        case SPI_MODE_0:
            SSPCON1bits.CKP = 0x0;
            SSPSTATbits.CKE = 0x1;
            break;
                        
        case SPI_MODE_1:
            SSPCON1bits.CKP = 0x0;
            SSPSTATbits.CKE = 0x0;
            break;
                        
        case SPI_MODE_2:
            SSPCON1bits.CKP = 0x1;
            SSPSTATbits.CKE = 0x1;
            break;
                        
        case SPI_MODE_3:
            SSPCON1bits.CKP = 0x1;
            SSPSTATbits.CKE = 0x0;  
            break;                
    }       
}

#ifdef SPI2_AVAILABLE
void SPI2_mode (uint8_t communication_mode) {

    SSP2STATbits.CKE = 0x0;
    
    switch (communication_mode) {

        case SPI_MODE_0:
            SSP2CON1bits.CKP = 0x0;
            SSP2STATbits.CKE = 0x1;
            break;
                        
        case SPI_MODE_1:
            SSP2CON1bits.CKP = 0x0;
            SSP2STATbits.CKE = 0x0;
            break;
                        
        case SPI_MODE_2:
            SSP2CON1bits.CKP = 0x1;
            SSP2STATbits.CKE = 0x1;
            break;
                        
        case SPI_MODE_3:
            SSP2CON1bits.CKP = 0x1;
            SSP2STATbits.CKE = 0x0; 
            break;
    }
}
#endif


// SPI1_write_byte Implementation
int8_t SPI1_write_byte (uint8_t byte_to_send) {
  
    uint8_t data;  
  
    // Clear the register by reading it out
    data = SSPBUF;           

    // Clear history
    PIR1bits.SSPIF = 0x0;        
    SSPCON1bits.WCOL = 0x0;
    
    // Send the data out
    SSPBUF = byte_to_send;  
    
    // Check for bus collision
    if (SSPCON1bits.WCOL == 0x1){
        return (-1);   
    } 
    
    // Wait the end of transmission
    while(!SPI1_is_TX_over());
    
    //No error occured
    return (0);                
}

#ifdef SPI2_AVAILABLE
int8_t SPI2_write_byte (uint8_t byte_to_send){

    uint8_t data;  

    //Clear the register by reading it out
    data = SSP2BUF;           

    //Clear history
    PIR3bits.SSP2IF = 0x0;        
    SSP2CON1bits.WCOL = 0x0;			

    //Send the data out
    SSP2BUF = byte_to_send;  

    //Check for bus collision
    if (SSP2CON1bits.WCOL == 0x1){
        return (-1);   
    } 

    //Wait end of transmission
    while(!SPI2_is_TX_over()); 

    //No error occured
    return (0);                
}
#endif


// SPI1_read_byte Implementation
uint8_t SPI1_read_byte (void) {
  
    uint8_t data;
    data = SSPBUF;       
  
    //Clear history  
    PIR1bits.SSPIF = 0x0;      

    //Write 0x00 to initiate a write
    SSPBUF = 0x00;           

    //Wait end of transmission
    while(!SPI1_is_TX_over());  
    
    //Return the new byte out of the 0x00 sent out
    return (SSPBUF);      
}

#ifdef SPI2_AVAILABLE
uint8_t SPI2_read_byte (void) {

    uint8_t data;
    data = SSP2BUF;       

    //Clear history  
    PIR3bits.SSP2IF = 0x0;      

    //Write 0x00 to initiate a write
    SSP2BUF = 0x00;           

    //Wait end of transmission
    while(!SPI2_is_TX_over());  

    //Return the new byte out of the 0x00 sent out
    return (SSP2BUF);      
}
#endif
