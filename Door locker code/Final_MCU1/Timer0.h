/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description: Header file for Timer0 AVR driver
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/


#ifndef TIMER0_H_
#define TIMER0_H_

#include "gpio.h"
#include "std_types.h"
#include <avr/io.h>
#include "Common_Macros.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
    OVERFLOW_MODE , COMPARE_MODE
}Timer0_Mode;

typedef enum
{
	 NO_CLOCK , NO_PRE_SCALAR, PRE_SCALAR_8 , PRE_SCALAR_64 , PRE_SCALAR_256 , PRE_SCALAR_1024
}Timer0_Pre_Scalar;

typedef enum
{
    EN_OVERFLOW_INT = 1 , EN_COMPARE_INT
}Timer0_Interrupt_Enable;

typedef struct
{
	Timer0_Mode mode;
	uint16 initial_value;
	uint16 compare_value;
	Timer0_Pre_Scalar prescalar;
	Timer0_Interrupt_Enable interrupt_en;

}Timer0_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize Timer0:
 * 1. Setup the Mode
 * 2. Setup initial value
 * 3. Setup compare value
 * 4. Setup pre_scalar
 */
void Timer0_init(const Timer0_configType*Config_Ptr );


/*
 * Description :
 * setting the call back function for Timer0
 */
void Timer0_SetCallBack (void(*a_ptr)(void));


/*
 * Description :
 * function to stop Timer0
 */

void Timer0_Deinit(void);

/*
 * Description :
 * function for delay using Timer0 Module
 */
void Timer0_delay(uint8 compare_value,uint8 seconds);


/*
 * Description : Interrupt Service Routine to increment the counter of for Timer0
 */
void delay_ISR(void);
#endif /* TIMER0_H_ */
