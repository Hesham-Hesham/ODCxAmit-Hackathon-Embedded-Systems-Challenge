/*
 * dc_motor.h
 *
 *  Created on: May 8, 2023
 *      Author: Hesham
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include "../MCAL/gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_ENABLE_PORT		PORTB_ID
#define DC_MOTOR_ENABLE_PIN			PIN3_ID

#define DC_MOTOR_FL_IN_PORT			PORTB_ID
#define DC_MOTOR_FL_IN_FIRST_PIN	PIN4_ID

#define DC_MOTOR_FR_IN_PORT			PORTC_ID
#define DC_MOTOR_FR_IN_FIRST_PIN	PIN2_ID

#define DC_MOTOR_BL_IN_PORT			PORTA_ID
#define DC_MOTOR_BL_IN_FIRST_PIN	PIN2_ID

#define DC_MOTOR_BR_IN_PORT			PORTC_ID
#define DC_MOTOR_BR_IN_FIRST_PIN	PIN6_ID


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

//To determine the rotation direction
typedef enum
{

	DC_MOTOR_STOP,DC_MOTOR_CW,DC_MOTOR_CCW
}DcMotor_State;


//To determine the rotation direction
typedef enum
{

	LB_DC,RB_DC,LF_DC,RF_DC
}DcMotor_Select;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description: initialize the motor driver
 */
funcReturn DCMotor_Init(void);



/*
 * Description: set the motor direction and rotation speed
 */
funcReturn DCMotor_Rotate(DcMotor_Select motor,DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
