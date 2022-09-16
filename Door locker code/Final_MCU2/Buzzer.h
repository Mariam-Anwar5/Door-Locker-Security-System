/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description:Header file for the Buzzer driver
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/



#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"
#include "GPIO.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID                 PORTA_ID
#define BUZZER_PIN_ID                  PIN0_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the BUZZER:
 * 1. Setup the BUZZER pin direction by use the GPIO driver.
 * 2. Put zero to the pin
 */
void Buzzer_init(void);

/*
 * Description :
 * function to make the buzzer works by writing one to its pin using GPIO driver
 */

void Buzzer_ON(void);


/*
 * Description :
 * function to stop the buzzer by writing zero to its pin using GPIO driver
 */

void Buzzer_OFF(void);

#endif /* BUZZER_H_ */
