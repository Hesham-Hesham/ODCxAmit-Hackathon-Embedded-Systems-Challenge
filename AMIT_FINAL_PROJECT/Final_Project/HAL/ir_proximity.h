/*
 * ir_proximity.h
 *
 *  Created on: Nov 6, 2023
 *      Author: Hesha
 */

#ifndef IR_PROXIMITY_H_
#define IR_PROXIMITY_H_

#include "../MCAL/gpio.h"

#define NUM_OF_IR_SENSORS 6

#define IR_RIGHT_PORT_ID		PORTA_ID
#define IR_RIGHT_PIN_ID			PIN4_ID

#define IR_LEFT_PORT_ID			PORTA_ID
#define IR_LEFT_PIN_ID			PIN5_ID

#define IR_FRONT_PORT_ID		PORTA_ID
#define IR_FRONT_PIN_ID			PIN6_ID

#define IR_BACK_PORT_ID			PORTA_ID
#define IR_BACK_PIN_ID			PIN7_ID

#define IR_GROUND_L_PORT_ID			PORTD_ID
#define IR_GROUND_L_PIN_ID			PIN2_ID

#define IR_GROUND_R_PORT_ID			PORTD_ID
#define IR_GROUND_R_PIN_ID			PIN3_ID


typedef enum{
	LEFT_IR,RIGHT_IR,FRONT_IR,BACK_IR,GROUND_L_IR,GROUND_R_IR
}IR_sensors;




funcReturn IR_PROXIMITY_init(IR_sensors sensor_num);
funcReturn IR_PROXIMITY_read(IR_sensors sensor_num, uint8 *ret);


#endif /* IR_PROXIMITY_H_ */
