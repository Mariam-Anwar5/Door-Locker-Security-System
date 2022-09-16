/******************************************************************************
 *
 * File Name: main_functions_2.h
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/


#ifndef MAIN_FUNCTIONS_2_H_
#define MAIN_FUNCTIONS_2_H_

#include "std_types.h"
#include <util/delay.h>
#include "string.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/********************************************************************************/
/*Description:function for receiving the password by UART from MCU-1*/
void receive_pass (uint8* rec_pass);


/********************************************************************************/
/*Description:function for saving the password in EEPROM*/
void save_pass (uint8* saved_pass);

/*******************************************************************************/
/*Description:function for sending commands by UART to MCU-1*/
void sending_comm (uint8 character);


/****************************************************************************************/
/*Description:function for comparing the received password with the one stored in EEPROM*/
uint8 compare_with_memory(uint8 *ptr1,uint8 *ptr2);

#endif /* MAIN_FUNCTIONS_2_H_ */
