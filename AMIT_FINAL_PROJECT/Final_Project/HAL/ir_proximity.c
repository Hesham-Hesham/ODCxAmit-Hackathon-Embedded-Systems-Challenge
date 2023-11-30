/*
 * ir_proximity.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Hesha
 */


#include "ir_proximity.h"
#include "../MCAL/gpio.h"
#include "avr/io.h" /* To use the IO Ports Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

// 
// 



/*
 * Description: initialize
 */
funcReturn IR_PROXIMITY_init(IR_sensors sensor_num){
	switch(sensor_num){

	case LEFT_IR:
		GPIO_setupPinDirection(IR_LEFT_PORT_ID, IR_LEFT_PIN_ID, PIN_INPUT);
		break;

	case RIGHT_IR:
		GPIO_setupPinDirection(IR_RIGHT_PORT_ID, IR_RIGHT_PIN_ID, PIN_INPUT);
		break;

	case FRONT_IR:
		GPIO_setupPinDirection(IR_FRONT_PORT_ID, IR_FRONT_PIN_ID, PIN_INPUT);
		break;

	case BACK_IR:
		GPIO_setupPinDirection(IR_BACK_PORT_ID, IR_BACK_PIN_ID, PIN_INPUT);
		break;

	case GROUND_L_IR:
		GPIO_setupPinDirection(IR_GROUND_L_PORT_ID, IR_GROUND_L_PIN_ID, PIN_INPUT);
		break;

	case GROUND_R_IR:
		GPIO_setupPinDirection(IR_GROUND_R_PORT_ID, IR_GROUND_R_PIN_ID, PIN_INPUT);
		break;

	default:
		return NOT_OK;

	}

	return OK;

}


/*
 * Description: turn on the buzzer
 */
funcReturn IR_PROXIMITY_read(IR_sensors sensor_num, uint8 *ret){

	switch(sensor_num){

	case LEFT_IR:
		*ret=GPIO_readPin(IR_LEFT_PORT_ID, IR_LEFT_PIN_ID);
		break;

	case RIGHT_IR:
		*ret=GPIO_readPin(IR_RIGHT_PORT_ID, IR_RIGHT_PIN_ID);
		break;

	case FRONT_IR:
		*ret=GPIO_readPin(IR_FRONT_PORT_ID, IR_FRONT_PIN_ID);
		break;

	case BACK_IR:
		*ret=GPIO_readPin(IR_BACK_PORT_ID, IR_BACK_PIN_ID);
		break;

	case GROUND_L_IR:
		*ret=GPIO_readPin(IR_GROUND_L_PORT_ID, IR_GROUND_L_PIN_ID);
		break;

	case GROUND_R_IR:
		*ret=GPIO_readPin(IR_GROUND_R_PORT_ID, IR_GROUND_R_PIN_ID);
		break;

	default:
		return NOT_OK;

	}

	return OK;

}


