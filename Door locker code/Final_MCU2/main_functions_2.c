/******************************************************************************
 *
 * File Name: main_functions_2.c
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/
#include "main_functions_2.h"
/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*Description:function for receiving the password from MCU1 */
void receive_pass (uint8* rec_pass)
{
	for(char j=0 ; j<3 ; j++)
	{
		rec_pass[j]=UART_recieveByte();
		LCD_intgerToString(rec_pass[j]);
		_delay_ms(50);

	}
}

/*******************************************************************************/
/*Description:function for getting the password from the user again to confirm it*/
void save_pass (uint8* saved_pass)
{
	char j;
	for( j=0 ; j<5 ; j++)
	{
		EEPROM_writeByte( (0x0001 + j) , saved_pass [j]);
		_delay_ms(40);

	}
	EEPROM_writeByte( (0x0001 + j) , '\0');
			_delay_ms(40);
	/*for( j=0 ; j<3 ; j++)
	{
	EEPROM_readByte( (0x0001 + j) , pass+ j);
	}*/
	LCD_clearScreen();
	LCD_displayString(saved_pass);
}

/*******************************************************************************/
/*Description:function for sending commands by UART to MCU-1*/
void sending_comm (uint8 character)
{
	UART_sendByte(character);
	_delay_ms(2000);
}


/****************************************************************************************/
/*Description:function for comparing the received password with the one stored in EEPROM*/
uint8 compare_with_memory(uint8 *ptr1,uint8 *ptr2)
{
	uint8 x;
	//uint8 stored_pass=EEPROM_readByte(0x0001, ptr1);
	x=strcmp(ptr1,ptr2);
	return x;
}




