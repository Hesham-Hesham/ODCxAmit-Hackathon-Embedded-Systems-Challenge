/*
 * gps.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Hesha
 */
#include <avr/interrupt.h>
#include "util/delay.h"

#include "gps.h"
#include "../MCAL/uart.h"
#include "avr/io.h" /* To use the IO Ports Registers */
#include "common_macros.h"



uint8 buf[100];
volatile uint8 	i=0,
				flag,
				stringReceived;

uint8 gpgga[]={'$','G','P','G','G','A'};

uint8 latitude[12]={0};
uint8 logitude[12]={0};



void GPS_init(void){

	UART_ConfigType UART_GPS = {UART_8_Bits, UART_PARITY_DISABLED, UART_STOPBIT_1_BIT, 9600, UART_ASYNCHRONOUS};
	UART_init(&UART_GPS);
}

void GPS_readPosition(void){

	GPS_readDataStream();

	GPS_processData();
}

void GPS_readDataStream(void){

	buf[i] = UART_recieveByte();

	while(	stringReceived == 0){
		i++;

		buf[i] = UART_recieveByte();

//		LCD_intgerToString(buf[i]);
//		LCD_intgerToString(i);


		if(i<7)
		{

			if(buf[i-1] != gpgga[i-1]){               // $GPGGA
				i=0;
			}else{

			}
		}
		if(i>=50){
			stringReceived=1;
			SET_BIT(DDRA,0);
			CLEAR_BIT(PORTA,0);

			CLEAR_BIT(PORTA,0);
			SET_BIT(PORTA,0);
		}
	}

}


void GPS_processData(void){

	if(stringReceived == 1)

	{

		cli();

		i=0;

		stringReceived=0;



		for(int j=17,k=0;j<28;j++,k++)

		{
			latitude[k]=buf[j];

		}
		for(int j=29,k=0;j<41;j++,k++)

		{
			logitude[k]=buf[j];

		}


		_delay_ms(200);

		sei();

	}

}
