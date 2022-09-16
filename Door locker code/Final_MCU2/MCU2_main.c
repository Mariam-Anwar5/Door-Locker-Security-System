/******************************************************************************
 *
 * File Name: MCU2_main
 *
 * Description: Source file for the APP layer of control ECU
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/

#include "Timer0.h"
#include "uart_driver.h"
#include "main_functions_2.h"
#include "twi.h"
#include "motor_driver.h"
#include"Buzzer.h"
#include "external_eeprom.h"
#include "string.h"
#include "lcd.h"


/*******************************************************************************
 *                               Definitions                             *
 *******************************************************************************/

#define PASSWORD_MATCH     0x01
#define PASSWORD_MISMATCH  0x02
#define DOOR_OPEN          0x03
#define CHANGE_PASSWORD    0x04
#define WRONG_PASSWORD     0x05


/*******************************************************************************
 *                               Global Variables                            *
 *******************************************************************************/


uint8 rec_pass [5];/*array of five elements to store the received password*/
uint8 passInMemory[5]; /*array for storing the password that's saved in EEPROM*/
char character; /*variable used for receiving bytes by UART from MCU1*/
uint8 counter=0;/*variable for counting how many times the password has been entered wrong*/



int main (void)
{
	/*array to store the received password from MCU1*/
	uint8 command[10];
	/*initialization of the DC motor*/
	DcMotor_Init();
	/*initialization of LCD*/
	LCD_init();
	/*initialization of the Buzzer*/
	Buzzer_init();
	/*UART Configurations*/
	UART_ConfigType UART_CONFIG ={ONE_BIT ,EIGHT_BITS,DISABLE_PARITY};
	/*initialization of the UART*/
	UART_init(&UART_CONFIG);
    /*receiving the password entered by user*/
	receive_pass (passInMemory);
	/*saving the password in EEPROM */
	save_pass (passInMemory);
	while(1)
	{
		/*receiving a password*/
		receive_pass (command);
		/*comparing between the entered password and the saved one in EEPROM*/
		compare_with_memory(passInMemory ,command);
		_delay_ms(200);
		/*checking whether the entered password and the saved one in EEPROM are matching */
		if(compare_with_memory(passInMemory ,command) != 0)
		{

			sending_comm(PASSWORD_MISMATCH);
			character = UART_recieveByte();
			counter++;
		}
		else if (compare_with_memory(passInMemory ,command) == 0)
		{
			sending_comm(PASSWORD_MATCH);
			character = UART_recieveByte();
			if (character == DOOR_OPEN)
			{
                /*opening the door for 15 seconds*/
				DcMotor_Rotate(MOTOR_CW);
				Timer0_delay(250, 15);
				/* hold the door for 3 seconds*/
				DcMotor_Rotate(MOTOR_STOP);
				Timer0_delay(250, 3);
				/*closing the door*/
				DcMotor_Rotate(MOTOR_ACW);
				Timer0_delay(250, 15);
				/* hold the door*/
				DcMotor_Rotate(MOTOR_STOP);
			}
			else if(character == CHANGE_PASSWORD)
			{
				/*receiving the new password*/
				receive_pass(rec_pass);
				/*saving the new password*/
				save_pass(rec_pass);
				LCD_clearScreen();
			}
			else if(character == WRONG_PASSWORD){
				LCD_clearScreen();
				LCD_displayString("wrong password");
			}
		}
		if (counter ==3)
		{
			/*For counting how many times the password has been entered wrong*/
			counter=0;
			LCD_clearScreen();
			LCD_moveCursor(0, 8);
			LCD_displayString("!!!");
			/*turning the buzzer on for 60 seconds*/
			Buzzer_ON();
			Timer0_delay(250,60);
			/*turning the buzzer off*/
			Buzzer_OFF();
			LCD_clearScreen();
		}
	}
}
