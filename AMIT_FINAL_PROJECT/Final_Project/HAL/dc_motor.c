/*
 * dc_motor.c
 *
 *  Created on: May 8, 2023
 *      Author: Hesham
 */

#include "../MCAL/gpio.h"
#include "../HAL/dc_motor.h"
#include "../MCAL/timer0_pwm.h"


/*
 * Description: initialize the motor driver
 */
funcReturn DCMotor_Init(void){

	funcReturn ret1;

	//set the enable pin as output
	GPIO_setupPinDirection(DC_MOTOR_ENABLE_PORT, DC_MOTOR_ENABLE_PIN, PIN_OUTPUT);

	//set the IN pins as output
	GPIO_setupPinDirection(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+0, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+1, PIN_OUTPUT);


	GPIO_setupPinDirection(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+0, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+1, PIN_OUTPUT);


	GPIO_setupPinDirection(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+0, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+1, PIN_OUTPUT);


	GPIO_setupPinDirection(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+0, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+1, PIN_OUTPUT);


	//Stop the motor
	ret1=GPIO_writePin(DC_MOTOR_ENABLE_PORT, DC_MOTOR_ENABLE_PIN, DC_MOTOR_STOP);

	if(ret1 == 0){
		return NOT_OK;
	}

	return OK;

}



/*
 * Description: set the motor direction and rotation speed
 */
funcReturn DCMotor_Rotate(DcMotor_Select motor,DcMotor_State state,uint8 speed){

	switch(state){
		case DC_MOTOR_CW:
			//set the direction as CW by the IN pins
			GPIO_writePin(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+1, LOGIC_HIGH);


			GPIO_writePin(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+1, LOGIC_HIGH);


			GPIO_writePin(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+1, LOGIC_HIGH);


			GPIO_writePin(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+1, LOGIC_HIGH);
			break;

		case DC_MOTOR_CCW:
			//set the direction as CW by the IN pins
			GPIO_writePin(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+0, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+1, LOGIC_LOW);


			GPIO_writePin(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+0, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+1, LOGIC_LOW);


			GPIO_writePin(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+0, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+1, LOGIC_LOW);


			GPIO_writePin(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+0, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+1, LOGIC_LOW);
			break;


		case DC_MOTOR_STOP:
			//Stop the motor by the IN pins
			GPIO_writePin(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_FL_IN_PORT, DC_MOTOR_FL_IN_FIRST_PIN+1, LOGIC_LOW);


			GPIO_writePin(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_FR_IN_PORT, DC_MOTOR_FR_IN_FIRST_PIN+1, LOGIC_LOW);


			GPIO_writePin(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_BL_IN_PORT, DC_MOTOR_BL_IN_FIRST_PIN+1, LOGIC_LOW);


			GPIO_writePin(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+0, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_BR_IN_PORT, DC_MOTOR_BR_IN_FIRST_PIN+1, LOGIC_LOW);
			break;

		default:
			return NOT_OK;
	}

	//set the motor speed by passing the PWM value to the function
	PWM_Timer0_Start(speed);

	return OK;

}

