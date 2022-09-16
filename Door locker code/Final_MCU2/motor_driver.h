/*
 * motor_driver.h
 *
 *  Created on: Oct 12, 2021
 *      Author: Mariam Anwar
 */

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_IN1_PORT_ID   PORTD_ID
#define MOTOR_IN1_PIN_ID    PIN3_ID
#define MOTOR_IN2_PORT_ID   PORTD_ID
#define MOTOR_IN2_PIN_ID    PIN4_ID
#define MOTOR_E1_PORT_ID    PORTB_ID
#define MOTOR_E1_PIN_ID     PIN3_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	MOTOR_STOP , MOTOR_CW , MOTOR_ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for setup the direction for the two motor pins.
 */
void DcMotor_Init(void);
/*
 * Description :
 *function responsible for rotate the DC Motor CW/ or A-CW or stop the motor.
 */
void DcMotor_Rotate(DcMotor_State state);
#endif /* MOTOR_DRIVER_H_ */
