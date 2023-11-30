/*
 * external_interrupts.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Hesha
 */



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "external_interrupts.h"
#include "common_macros.h"
#include "std_types.h"


volatile uint8 g_Interrupt_Flag = 0;


ISR(INT0_vect)
{
	// set the interrupt flag to indicate that INT1 occurs
	g_Interrupt_Flag = 1;

}


/* External INT1 enable and configuration function */
void INT0_Init(void)
{

	CLEAR_BIT(DDRD,EXTERNAL_INTERRUPTS_0_PIN_ID);

	// Trigger INT0 with both edges
	SET_BIT(MCUCR,0);


	GICR  |= (1<<INT0);    // Enable external interrupt pin INT0

}


