/*
 * servo.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Hesha
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "../MCAL/gpio.h"
#define SERVO_PORT_ID	PORTB_ID

#define SERVO_PIN_ID	PIN0_ID




typedef enum{

	DEG_0,DEG_45,DEG_90,DEG_135,DEG_180
}SERVO_angles;

funcReturn SERVO_init(void);
funcReturn SERVO_rotate(SERVO_angles angle);

#endif /* SERVO_H_ */
