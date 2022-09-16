/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/

#include "uart_driver.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType*Config_Ptr)
{
	uint16 baud_rate=9600;
	uint16 ubrr_value = 0;

	/************************************ UCSRA **************************************/
	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);


	/************************************* UCSRB *************************************/
	/*
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable bits_num
	 */
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*selecting the number of data bits in the UART frame by user
	 * 1.UCSZ2 = 0 for 5,6,7,8-bit Modes
	 * 2.UCSZ2 = 1 for 9-bit Mode
	 */
	UCSRB = (UCSRB & 0xFB) | (((Config_Ptr -> bits_num) & 0x04) <<2);


	/************************************* UCSRC ****************************************/
	/* URSEL= 1 The URSEL must be one when writing the UCSRC*/
	UCSRC = (1<<URSEL);

	/* UPM1:0 ---> Setting Parity Mode
	 * 1. UPM1:0 = 00 Disable Parity Mode
	 * 2. UPM1:0 = 10 Enable Parity Mode with Even Parity
	 * 3. UPM1:0 = 11 Enable Parity Mode with ODD Parity
	 */
	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr -> parity) <<4);


    /* Number of Stop Bits Selected to be inserted by the transmitter
     * 1. USBS = 0 for 1-stop bit
     * 2. USBS = 1 for 2-stop bits
     */
    UCSRC = (UCSRC & 0xF7) | ((Config_Ptr -> stop_bit) <<3);

    /*selecting the number of data bits in the UART frame by user
     * 1. UCSZ1:0= 00 for 5-bit mode
     * 2. UCSZ1:0= 01 for 6-bit mode
     * 3. UCSZ1:0= 10 for 7-bit mode
     * 4. UCSZ1:0= 11 for 8-bit mode or 9-bit Mode
     */
    UCSRC = (UCSRC & 0xF9) | (((Config_Ptr -> bits_num) & 0x03) <<2);



	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}


/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;
}


/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}

	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
