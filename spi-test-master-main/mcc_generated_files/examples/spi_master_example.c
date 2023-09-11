/**
\file
\addtogroup doc_driver_spi_example
\brief This file contains sample source codes to demonstrate the SPI Foundation Services APIs.

For this example application to work the following needs to be done:
1. Configure the SPI module as follows:
    - Enable SPI: ticked
    - Modes: Master
    - Interrupt driven: unticked
    - Configure other settings as desired.
    - Select TX and RX pins in Pin Manager: Grid View.
2. Make loop back connection to MISO and MOSI or connect SPI pins to a slave
3. If connected to a slave, assign CS pin and add the necessary calls in drive_slave_select_low() and drive_slave_select_high()
4. Program the slave device to exchange the string "data"
5. Call SPI_Master_test() from main()   

This example works like this:
1. Upon reset, the application will transmit a string "data" and read the same number of bytes back.
2. The program will then compare the received string with "data". Returns 1 to indicate a match or 0 if not.

\copyright (c) 2020 Microchip Technology Inc. and its subsidiaries.
\page License
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <stdio.h>
#include <string.h>
#include "../drivers/spi_master.h"
#include <xc.h>

#define _XTAL_FREQ 16000000/4

//static uint8_t buffer[4]= {0x55, 0x33, 0xFF, 0x00};
static uint8_t buffer[4]= "data";
uint8_t buffer2[4];
uint8_t rMessage = "0x00";
uint8_t tMessage = "0xA9";
/*
 En este ejemplo cada uno de los 16 espacios de buffer es un byte.
 Por tanto cada letra de la palabra data es un byte, y el resto son 0x00
 
 'd' = 0x64 = 0b01100100
 'a' = 0x61 = 0b01100001
 't' = 0x74 = 0b01110100
 'a' = 0x61 = 0b01100001
 
 */

static void drive_slave_select_low(void);
static void drive_slave_select_high(void);

// Abstracted function defined in the driver to start the communication with the selected slave device
static void drive_slave_select_low()
{
	// Control GPIO to drive SS_bar low
	PORTAbits.RA5 = 0;
}

// Abstracted function defined in the driver to end the communication with the selected slave device
static void drive_slave_select_high()
{
	// Control GPIO to drive SS_bar high
	PORTAbits.RA5 = 1;
}

// First test in which one byte is exchanged
uint8_t SPI_Master_test(void)
{
	// Test if the SPI module is already enabled	
	if(!spi_master_open(MASTER0))
		// Not able to open SPI, call fail() or optionally do something 
		// else waiting for the SPI to become free
		return 0; 
	
    
    	// The slave device is selected to start the communication
    	drive_slave_select_low();


    	rMessage = SPI1_ExchangeByte(tMessage);   //An example to exchange a single byte with the slave

	//SPI1TXB = 0x33; //Se empieza la transferencia       0b01101001 
    	//SPI1TXB = 0x55;     //recordatorio que 0xF = 0b1111 -> 0xFF = 0b11111111 
    	//__delay_us(20);
    	//SPI1TXB = 0xAA; //Se empieza la transferencia       0b01101001 
    
    	drive_slave_select_high();
    
    	SPI1_Close();
    
   	
    }
    
	// Check that the correct data was received
	//if (strncmp((char*)buffer, "data", strlen("data")))
	//	return 0; // ERROR: Wrong data received
	
    
    
	// If we get here, everything was OK
	return 1;
}

// Second test in which a block of messages is exchanged uninterrumpted
uint8_t SPI_Master_2(void)      
{
	// Test driver, assume that the SPI MISO and MOSI pins have been looped back
	if(!spi_master_open(MASTER0))
		// Not able to open SPI, call fail() or optionally do something 
		// else waiting for the SPI to become free
		return 0; 
	
	drive_slave_select_low();
	
	// The defined number of bytes are exchanged
	SPI1_ExchangeBlock(buffer, sizeof(buffer));
    
    
    	drive_slave_select_high();

    	SPI1_Close();

	buffer2[0] = buffer[0];
	buffer2[1] = buffer[1];
    	buffer2[2] = buffer[2];
   	buffer2[3] = buffer[3];
    
   	// Check that the correct data was received
	if(buffer2[0]==0xC8 && buffer2[1]==0xC8 && buffer2[2]==0xC8 && buffer2[2]==0xC8)
 	{
        	PORTCbits.RC2 = 1;
		return 0; // wrong data was received
    
	}
	    
		// If we get here, everything was OK
		return 1;
}

/**
 End of File
 */
