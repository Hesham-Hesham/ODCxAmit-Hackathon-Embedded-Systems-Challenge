/*
 * external_interrupts.h
 *
 *  Created on: Nov 8, 2023
 *      Author: Hesha
 */

#ifndef MCAL_EXTERNAL_INTERRUPTS_H_
#define MCAL_EXTERNAL_INTERRUPTS_H_


#include "gpio.h"

#define EXTERNAL_INTERRUPTS_0_PORT_ID						PORTD_ID
#define EXTERNAL_INTERRUPTS_0_PIN_ID						PIN4_ID



extern volatile uint8 g_Interrupt_Flag;

void INT0_Init(void);

#endif /* MCAL_EXTERNAL_INTERRUPTS_H_ */
