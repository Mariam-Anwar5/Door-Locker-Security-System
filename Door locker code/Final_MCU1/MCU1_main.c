 /******************************************************************************
 *
 * File Name: MCU1_main
 *
 * Description: Source file for the APP layer of HMI
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/


#include "keypad.h"
#include "Timer0.h"
#include "uart_driver.h"
#include "lcd.h"
#include "main_functions_1.h"


/*******************************************************************************
 *                               Definitions                             *
 *******************************************************************************/


#define PASSWORD_MATCH     0x01
#define PASSWORD_MISMATCH  0X02
#define DOOR_OPEN          0x03
#define CHANGE_PASSWORD    0x04
#define WRONG_PASSWORD     0x05


/*******************************************************************************
 *                               Global Variables                            *
 *******************************************************************************/

uint8 password [5]; /*array of 5 elements to store the password from the user*/
uint8 confirm_pass [5]; /*array of 5 elements to store the password from the user for second time*/
uint8 new_pass[5];/*array of 5 elements to store the new password*/
uint8 character; /*variable used for sending bytes by UART to MCU2*/

int main(void){

	/*initialization of LCD*/
	LCD_init();
	/*UART Configurations*/
	UART_ConfigType UART_CONFIG ={ONE_BIT ,EIGHT_BITS,DISABLE_PARITY};
	/*initialization of the UART*/
	UART_init(&UART_CONFIG);
	do
	{
		Enter_Password(password);
		confirm_password(confirm_pass);
		/*checking whether the two password entered by the user are the same*/
		compare(password, confirm_pass);
	}while (compare(password, confirm_pass)!=0);
    /*sending the password by UART to MCU2 be saved in EEPROM */
	sending_pass (password);

	while(1)
	{
		/*Displaying the main options to the user*/
		main_menu();
		if (KEYPAD_getPressedKey() == '+' )
		{
			Enter_Password (password);
			sending_pass (password);
			/*waiting to receive a command from MCU2 to ensure that the password is right*/
			character=rec_comm();
			if(character==PASSWORD_MATCH)
			{

				/*sending command to open the door as the password is entered right*/
				sending_comm (DOOR_OPEN);
				/*Displaying on LCD to the user that the door is being opened*/
				openDoor_LCD ();

			}
			else if(character==PASSWORD_MISMATCH)
			{
				sending_comm (WRONG_PASSWORD);
				LCD_clearScreen();
				LCD_moveCursor(0, 0);
				Timer0_delay(250, 1);
				LCD_displayString("wrong password");
				Timer0_delay(250, 1);

			}
		}
		else if (KEYPAD_getPressedKey() == '-' )
		{
			uint8 compare_status;
			Enter_Password (password);
			sending_pass (password);
			/*waiting to receive a command from MCU2 to ensure that the password is right*/
			character=rec_comm();
			if(character==PASSWORD_MATCH)
			{
				sending_comm (CHANGE_PASSWORD);
				while (compare(new_pass, confirm_pass)!=0)
				{
					/*asking the user to enter the new password*/
					New_Password(new_pass);
					/*asking the user to confirm the new password*/
					confirm_password(confirm_pass);
					/*checking if the two passwords entered by user are the same*/
					compare(new_pass, confirm_pass);
				}
				/*sending the new password to MCU2 to be saved in EEPROM*/
				sending_pass(new_pass);
				main_menu();
			}
			else if(character==PASSWORD_MISMATCH)
			{
				sending_comm (WRONG_PASSWORD);
				LCD_clearScreen();
				/*Displaying that the password that entered is wrong*/
				LCD_displayString("wrong password");
				Timer0_delay(250, 2);
				do{
					password_Change(password, confirm_pass);
					compare_status= compare(password, confirm_pass);
				}
				while(compare_status != 0);
				main_menu();
			}

		}

	}
}
