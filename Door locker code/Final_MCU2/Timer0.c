/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.c
 *
 * Description:Source file for Timer0 AVR driver
 *
 * Author: Mariam Anwar
 *
 *******************************************************************************/

#include "Timer0.h"
#include "common_macros.h"
#include "std_types.h"
uint16 Timer0_counter=0;

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/*ISR for Timer Overflow Mode */
ISR (TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected*/
		(*g_callBackPtr)();
	}
}

/*ISR for Timer Compare Mode */
ISR (TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected*/
		(*g_callBackPtr)();
	}
}
/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize Timer0:
 * 1. Setup the Mode
 * 2. Setup initial value for the timer
 * 3. Setup compare value for the timer in-case of compare mode
 * 4. Select the pre_scalar
 */
void Timer0_init(const Timer0_configType*Config_Ptr )
{
	/*Enable the Global Interrupt*/
	SREG |= (1<<7);
	/*non-PWM Mode*/
	TCCR0=(1<<FOC0);
	/* Timer's initial value by user*/
	TCNT0 = (TCNT0 & 0x00) | (Config_Ptr -> initial_value );
	/*Timer's compare value by user*/
    OCR0 = (OCR0 & 0x00) | (Config_Ptr -> compare_value);
    /*Pre-scalar Select*/
    TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr -> prescalar);
    /*Setup the Timer Mode whether it's overflow or compare mode*/
    TCCR0 = (TCCR0 & 0xBF) | (((Config_Ptr -> mode) & 0x01)<<6);
    TCCR0 = (TCCR0 & 0xF7) | (((Config_Ptr -> mode) & 0x02)<<3);
    /*Enabling the Overflow interrupt or Compare interrupt based on Timer Mode set by the user*/
    /* Interrupt Mask Register TIMSK
     * 1. OCIE0=0 , TOIE0=1 in-case of Overflow Mode
     * 2. OCIE0=1 , TOIE0=0 in-case of Compare Mode
     */
    TIMSK = (TIMSK & 0xFC) | ((Config_Ptr -> interrupt_en));
}

/*
 * Description: Function to set the Call Back function address.
 */

void Timer0_SetCallBack (void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}


/*
 * Description : function to stop Timer0
 */
void Timer0_Deinit(void)
{
    /*Stop the timer by stopping the clock in Control Register TCCR0 (No clock source)
     * 1. CS00=0
     * 2. CS02=0
     * 3. CS02=0
     */
	CLEAR_BIT(TCCR0,CS00);
	CLEAR_BIT(TCCR0,CS01);
	CLEAR_BIT(TCCR0,CS02);

	/***********************************or***************************************************
	 *all registers to zero
	/*initial value equals to zero
	TCNT0 = 0;
	/* Timer/Counter Control Register to zero value
	TCCR0 = 0;
	/* Interrupt Flag Register to zero value
	TIFR=0;
	/*Interrupt Mask Register to zero value
	TIMSK=0;
	*/

}


/*
 * Description : function for delaying using Timer0 Module
 */
void Timer0_delay(uint8 compare_value,uint8 seconds)
{

	Timer0_configType time0_config;
	time0_config.prescalar =PRE_SCALAR_1024;
	time0_config.mode= COMPARE_MODE;
	time0_config.compare_value=compare_value;
	time0_config.interrupt_en=EN_COMPARE_INT;
	Timer0_SetCallBack(&delay_ISR);
	Timer0_init(&time0_config);
	while(Timer0_counter<=(seconds*31)){}
	Timer0_Deinit();
	Timer0_counter=0;
}



/*
 * Description : Interrupt Service Routine to increment the counter of for Timer0
 */
void delay_ISR(void){
	Timer0_counter++;
}

