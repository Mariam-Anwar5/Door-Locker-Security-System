/******************************************************************************
 *
 * File Name: main_functions_1.h
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/



#ifndef MAIN_FUNCTIONS_1_H_
#define MAIN_FUNCTIONS_1_H_

#include "std_types.h"
#include "lcd.h"
#include "keypad.h"
#include"uart_driver.h"
#include <util/delay.h>
#include "string.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/********************************************************************************/
/*Description:function for getting the password from the user*/
void Enter_Password (uint8 * password);

/********************************************************************************/
/*Description:function for getting the password from the user again to confirm it*/
void confirm_password(uint8 * confirm_pass);
/********************************************************************************/
/*Description:function for getting the new password*/
void New_Password (uint8 * new_pass);
/*******************************************************************************/
/*Description:function for displaying that the door is getting opened*/
void openDoor_LCD (void);
/*******************************************************************************/
/*Description:function for displaying that the door is getting closed*/
void closeDoor_LCD (void);

/*******************************************************************************/
/*Description:function for changing the password*/
void password_Change (uint8* password , uint8* confirm_pass);

/*******************************************************************************/
/*Description:function for comparing the two passwords entered by the user*/
uint8 compare(uint8 *ptr1,uint8 *ptr2);

/*******************************************************************************/
/*Description:function for sending commands by UART to MCU-2*/
void sending_comm (uint8 character);

/*******************************************************************************/
/*Description:function for receiving commands by UART from MCU-2*/
uint8 rec_comm (void);

/*******************************************************************************/
/*Description:function for sending password by UART to MCU-2*/
void sending_pass (uint8* send_pass);


#endif /* MAIN_FUNCTIONS_1_H_ */
