/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Description:Source file for the Buzzer driver
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/


#include "Buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the BUZZER:
 * 1. Setup the BUZZER pin direction by use the GPIO driver.
 * 2. Put an initial value zero to the pin
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection( BUZZER_PORT_ID,BUZZER_PIN_ID, PIN_OUTPUT);
	//GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * function to make the buzzer works by writing one to its pin using GPIO driver
 */

void Buzzer_ON(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}


/*
 * Description :
 * function to stop the buzzer by writing zero to its pin using GPIO driver
 */

void Buzzer_OFF(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
