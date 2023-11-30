/*
 * ultrasonic_HCSR04.c
 *
 *  Created on: May 27, 2023
 *      Author: Hesham Hesham
 */

#include <util/delay.h> //to use _delay_us

#include "../MCAL/icu.h"
#include "../MCAL/gpio.h"
#include "std_types.h"
#include "ultrasonic_HCSR04.h"
#include "avr/io.h"


uint8 g_edgeCount = 0;


funcReturn Ultrasonic_init(void){

	funcReturn ret1;

	ICU_ConfigType Ultrasonic_ICU_Config = {ICU_RISING_EDGE,F_CPU_8};

	ICU_init(&Ultrasonic_ICU_Config);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	ret1=GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);

	if(ret1 == 0){
		return NOT_OK;
	}

	return OK;
}


funcReturn Ultrasonic_Trigger(void){

	funcReturn ret1,ret2;

	ret1=GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(15);
	ret2=GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);

	if(ret1 || ret2){
		return NOT_OK;
	}

	return OK;
}

void Ultrasonic_edgeProcessing(void){


	if(ICU_ISR_lastEdge){				//last edge was rising edge and now we're at a falling edge
		//Calculate captured pulse period
		ICU_CapturedValue=ICU_getInputCaptureValue();

		//Next time detect rising edge:

		//1) detect rising edge
		ICU_setEdgeDetectionType(ICU_RISING_EDGE);
		//2) next time (when ISR occurs) enter the "else condition"
		ICU_ISR_lastEdge=ICU_FALLING_EDGE;

	}else{								//last edge was falling edge and now we're at a rising edge
		//Reset the current time
		ICU_clearTimer();

		//Next time detect falling edge:

		//1) detect falling edge
		ICU_setEdgeDetectionType(ICU_FALLING_EDGE);
		//2) next time (when ISR occurs) enter the "if condition"
		ICU_ISR_lastEdge=ICU_RISING_EDGE;

	}



}



funcReturn Ultrasonic_readDistance(uint16 *ret){
	uint16 Ultrasonic_distance=0;
	Ultrasonic_Trigger();

	// distance = (time of flight / 2) * speed of sound in air in m/s * 100(to convert m to cm)
//	Ultrasonic_distance = (ICU_CapturedValue/2) * 340 * 100;

	/* Ftimer = Fcpu/prescale= 16MHz / 8 = 2 MHz
	 * Ttimer = 1 / Ftimer = 1 Microsecond = 5 * 10^-7 second
	 */

//	Ultrasonic_distance = Ultrasonic_distance / 1000000;
	Ultrasonic_distance = ICU_CapturedValue / (58.5*2);

	*ret=Ultrasonic_distance+1;

	if(Ultrasonic_distance==0){
		return NOT_OK;
	}
	return OK;
}
