/*
 * servo.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Hesha
 */

#include "../HAL/servo.h"

#include "../MCAL/gpio.h"
#include "util/delay.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/io.h"


funcReturn SERVO_init(void){

	funcReturn ret1,ret2,ret3;

	ret1=GPIO_setupPinDirection(SERVO_PORT_ID, SERVO_PIN_ID, PIN_OUTPUT);
	ret2=GPIO_writePin(SERVO_PORT_ID, SERVO_PIN_ID, LOGIC_LOW);

	ret3=SERVO_rotate(DEG_90);
	if(ret1 || ret2 || ret3){
		return NOT_OK;
	}

	return OK;
}


funcReturn  SERVO_rotate(SERVO_angles angle){

	funcReturn ret1,ret2;
	uint16 rotation_delay_us=0;

	switch(angle){

	case DEG_0:
		rotation_delay_us=500;
		break;

	case DEG_45:
		rotation_delay_us=748;
		break;

	case DEG_90:
		rotation_delay_us=1010;
		break;

	case DEG_135:
		rotation_delay_us=1260;
		break;

	case DEG_180:
		rotation_delay_us=1509;
		break;

	default:
		return NOT_OK;

	}

	ret1=GPIO_writePin(SERVO_PORT_ID, SERVO_PIN_ID, LOGIC_HIGH);
	_delay_us(rotation_delay_us-39);
	ret2=GPIO_writePin(SERVO_PORT_ID, SERVO_PIN_ID, LOGIC_LOW);

	if(ret1 || ret2){
		return NOT_OK;
	}
	return OK;

	return OK;
}
