/******************************************************************************
 *
 * File Name: main_functions_1.c
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/
#include "main_functions_1.h"


/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/



/*******************************************************************************/
 /*Description:function for getting the password from the user*/
void Enter_Password (uint8 * password)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Enter Password");
	LCD_moveCursor(1,0);
	uint8 pressed_key=0;
	int i;
	for ( i =0 ; i<5 ; i++)
	{
		pressed_key = KEYPAD_getPressedKey();  /*getting the pressed key from the pasuser*/
		_delay_ms(500);
		if ((pressed_key >= 0 ) && (pressed_key <=9))
		{
			LCD_displayCharacter('*');
			password [i]=pressed_key+48; /*storing the password */
		}
		else
		{
			i--;
		}
		_delay_ms(200);
	}
	password[i]='\0';
}



/*******************************************************************************/
/*Description:function for getting the password from the user again to confirm it*/
void confirm_password(uint8 * confirm_pass)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Enter Pass again");
	LCD_moveCursor(1,3);
	uint8 pressed_key=0;
	int i;
	for (i =0 ; i<5 ; i++)
	{
		pressed_key = KEYPAD_getPressedKey();  /*getting the pressed key from the user*/
		if ((pressed_key >= 0 ) && (pressed_key <=9))
		{
			LCD_displayCharacter('*');
			 confirm_pass [i] = pressed_key +48; /*storing the password for second time*/
		}
		else
		{
			continue;
			i--;
		}
		_delay_ms(200);
	}
	confirm_pass[i]='\0';
}

/*******************************************************************************/
 /*Description:function for getting the new password from the user*/
void New_Password (uint8 * new_pass)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Enter New Pass.");
	LCD_moveCursor(1,0);
	uint8 pressed_key=0;
	int i;
	for ( i =0 ; i<5 ; i++)
	{
		pressed_key = KEYPAD_getPressedKey();  /*getting the pressed key from the pasuser*/
		_delay_ms(500);
		if ((pressed_key >= 0 ) && (pressed_key <=9))
		{
			LCD_displayCharacter('*');
			new_pass [i]=pressed_key+48; /*storing the password */
		}
		else
		{
			i--;
		}
		_delay_ms(200);
	}
	new_pass[i]='\0';
}

/*******************************************************************************/
/*Description:function for displaying main options for the user*/
void main_menu (void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("+:open door");
	LCD_moveCursor(1,0);
	LCD_displayString("-:change password");
}


/*******************************************************************************/
/*Description:function for changing the password*/
void password_Change (uint8* new_pass, uint8* confirm_pass)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	New_Password(new_pass);
	confirm_password(confirm_pass);

}

/*******************************************************************************/
/*Description:function for displaying that the door is getting opened*/
void openDoor_LCD (void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Door is opening");
	Timer0_delay(250, 15);
	LCD_clearScreen();
	Timer0_delay(250, 3);
	LCD_moveCursor(0,0);
	LCD_displayString("Door is closing");
	Timer0_delay(250, 15);
	LCD_clearScreen();
}


/*******************************************************************************/
/*Description:function for displaying that the door is getting closed*/
void closeDoor_LCD (void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"The door is closing");
	_delay_ms(18000);
}

/*******************************************************************************/
/*Description:function for comparing the two passwords*/
uint8 compare(uint8 *ptr1,uint8 *ptr2){
	uint8 x=1;
	x=strcmp(ptr1,ptr2);
	return x;

}
/*******************************************************************************/
/*Description:function for sending commands by UART to MCU-2*/
void sending_comm (uint8 character)
{
	UART_sendByte(character);
	_delay_ms(2000);
}

/*******************************************************************************/
/*Description:function for receiving commands by UART from MCU-2*/
uint8 rec_comm (void)
{
    uint8 character=UART_recieveByte();
	_delay_ms(200);
	return character;
}

/*******************************************************************************/
/*Description:function for sending password by UART to MCU-2*/
void sending_pass (uint8* send_pass)
{
	for(char i=0 ; i<3 ;i++)
	{
	UART_sendByte(send_pass[i]);
	_delay_ms(200);
	}
}




