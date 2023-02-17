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

This module contains main startup function and the startup always loop

*******************************************************************************/

#include <xc.h>
#include "globals.h"
#include "system.h"

/*
 * 
 */
int main (void) {

    // Startup the main setup configuration
    ConfigSystemState(SYSTEM_STATE_START_INIT);
    
    // TO DO !!!
    // Wait for one second
    __delay_ms(1000);
    // TO DO !!!
    
    // Initializes the USB device stack it in the default state.
    USBDeviceInit();
    // Checks if VBUS is present, and that the USB module is not already
    // initialized, and if so, enables the USB module so as to signal device
    // attachment to the USB host.
    USBDeviceAttach();
    
    // Startup completed
    ConfigSystemState(SYSTEM_STATE_COMPLETED_INIT);
    
	// Infinite loop
	while (1) {
        
        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            USBDeviceTasks();
        #endif

        //Exec main task
        MainSystemTasks();
 	}

}
