/*
 * timer0_pwm.c
 *
 *  Created on: May 8, 2023
 *      Author: Hesham
 */


#include <avr/io.h>

#include "timer0_pwm.h"
#include "std_types.h"
#include "../MCAL/gpio.h"


/*
 * Description: start the pwm output with a certain duty cycle value
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
//	if(duty_cycle>100){
//		duty_cycle=100;
//	}
	// Set Timer Initial Value to 0
	TCNT0 = 0;

	//fast PWM, non-inverted mode
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	//to get percent: divide duty cycle by 100 then multiply with 256
	OCR0  = (uint8)(((uint16)255*duty_cycle)/100);

	//set direction as output for pin where the PWM signal is generated
	GPIO_setupPinDirection(PWM_ENABLE_PORT_ID,PWM_ENABLE_PIN_ID,PIN_OUTPUT);
}


