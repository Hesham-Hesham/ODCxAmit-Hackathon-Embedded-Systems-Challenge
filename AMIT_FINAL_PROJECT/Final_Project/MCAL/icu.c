/*
 * icu.c
 *
 *  Created on: May 27, 2023
 *      Author: Hesham Hesham
 */

#include <avr/io.h> 		// To use ICU registers
#include <avr/interrupt.h>	// To use ISR

#include "icu.h"
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"			//To set pin direction

/*******************************************************************************
 *                          Private Global Variables                           *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*ICU_g_callBackPtr)(void) = NULL_PTR;

  uint16 ICU_CapturedValue=0;
  uint8 ICU_ISR_lastEdge=0;

ISR(TIMER1_CAPT_vect){
	if(ICU_g_callBackPtr != NULL_PTR)

	(*ICU_g_callBackPtr)();	//Call the callback function that is stored in the pointer

//	SET_BIT(TIFR,ICF1);		//Lower the ICU flag
}





void ICU_init(const ICU_ConfigType *Config_ptr){

	//Timer1 normal mode
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	CLEAR_BIT(TCCR1B,WGM12);
	CLEAR_BIT(TCCR1B,WGM13);

	//Non PWM mode
	CLEAR_BIT(TCCR1A,FOC1A);
	CLEAR_BIT(TCCR1A,FOC1B);

	//Set direction of ICU1 pin (PORTD PIN6)
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

	//insert prescaler bits into the first 3 of TCCR1B (Bit 2:0 – CS12:0: Clock Select)
	TCCR1B=(TCCR1B & 0xF8) | (Config_ptr->prescaler  & ~(0xF8));

	//Select default edge type
	ICU_setEdgeDetectionType(Config_ptr->edge_type);

	//Reset the current time register
	ICU_clearTimer();

	//Reset the captured value register
	ICR1=0;

	//Enable ICU Interrupt
	SET_BIT(TIMSK,TICIE1);

}


void ICU_setEdgeDetectionType(const ICU_Edge_Type edge_type)
{
	//Select edge type
	if(edge_type){						//Rising edge configuration
		SET_BIT(TCCR1B,6);
	}else{								//Falling edge configuration
		CLEAR_BIT(TCCR1B,6);
	}
}


uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}


void ICU_clearTimer(void)
{
	TCNT1 = 0;
}

void ICU_setCallBack(void(*a_ptr)(void)){
	ICU_g_callBackPtr=a_ptr;
}
