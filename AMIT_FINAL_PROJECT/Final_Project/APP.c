/*
 * APP.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Hesha
 */



#include "avr/io.h" /* To use the IO Ports Registers */

#include "util/delay.h"
#include <avr/interrupt.h>
#include <ctype.h>

#include "common_macros.h" /* To use the macros like SET_BIT */
#include "../HAL/gps.h"
#include "../HAL/dc_motor.h"
#include "../HAL/servo.h"
#include "../HAL/ultrasonic_HCSR04.h"
#include "../HAL/ir_proximity.h"
#include "../MCAL/uart.h"
#include "../MCAL/i2c.h"
#include "../MCAL/LCD_i2c.h"
#include "../MCAL/external_interrupts.h"



#define COLLISION_AVOIDANCE_DISTANCE 50		//50 cm


/*	Starting position is:
 *	3014.3864,N,
 *	09748.9411,W,
 */
uint8 startingN_Pos[12]={3,0,1,4,'.',3,8,6,4};
uint8 startingW_Pos[12]={0,9,7,4,8,'.',9,4,1,1};


uint8 beginMovement=0;

uint8 ground_L_ir_return=0;
uint8 ground_R_ir_return=0;
uint8 back_ir_return=0;
uint8 front_ir_return=0;
uint8 left_ir_return=0;
uint8 right_ir_return=0;
uint16 ultrasonic_return=0;

funcReturn move_forward(void);
funcReturn move_backward(void);
funcReturn move_forward_slightly_right(void);
funcReturn move_forward_slightly_left(void);
funcReturn stop_moving(void);
funcReturn pass_theObstacle(void);
funcReturn check_surroudings(void);




int main(){

	SREG |= (1<<7);


	UART_ConfigType UART_GPS = {UART_8_Bits, UART_PARITY_DISABLED, UART_STOPBIT_1_BIT, 9600, UART_ASYNCHRONOUS};
	UART_init(&UART_GPS);

	i2c_init();
	i2c_start();
	i2c_write(LCD_1);
	lcd_init();


	i2c_init();
	i2c_start();
	i2c_write(LCD_1);
	lcd_init();
	lcd_clear();


	lcd_moveCursor(0, 0);

	SERVO_init();

	DCMotor_Init();

	IR_PROXIMITY_init(LEFT_IR);
	IR_PROXIMITY_init(RIGHT_IR);
	IR_PROXIMITY_init(FRONT_IR);
	IR_PROXIMITY_init(BACK_IR);
	IR_PROXIMITY_init(GROUND_L_IR);
	IR_PROXIMITY_init(GROUND_R_IR);

	Ultrasonic_init();

	lcd_send_string("waiting for the");
	lcd_moveCursor(1, 0);
	lcd_send_string("start");

	_delay_ms(1000);


	beginMovement=UART_recieveByte();

	lcd_clear();
	_delay_ms(500);

	for(;;){
		if(beginMovement == 1){

			Ultrasonic_readDistance(&ultrasonic_return);

			while(ultrasonic_return >= COLLISION_AVOIDANCE_DISTANCE){
				lcd_moveCursor(0, 0);
				lcd_send_string("Obstacle detected at ");

				lcd_moveCursor(1, 0);
				LCD_intgerToString(ultrasonic_return);
				lcd_send_string("m");
				_delay_ms(500);
				lcd_clear();

				stop_moving();
				check_surroudings();
				pass_theObstacle();
				_delay_ms(500);
				lcd_clear();

				Ultrasonic_readDistance(&ultrasonic_return);

			}

			IR_PROXIMITY_read(GROUND_L_IR, &ground_L_ir_return);
			IR_PROXIMITY_read(GROUND_R_IR, &ground_R_ir_return);

			//Line is between the two wheels
			if( 		(ground_L_ir_return==0) && (ground_R_ir_return==0) ){
				move_forward();
			}

			//Line is closer to the left wheel
			else if(	(ground_L_ir_return==1) && (ground_R_ir_return==0) ){
				move_forward_slightly_right();
			}

			//Line is closer to the right wheel
			else if(	(ground_L_ir_return==0) && (ground_R_ir_return==1) ){
				move_forward_slightly_left();
			}

			//Line has ended
			else if(	(ground_L_ir_return==1) && (ground_R_ir_return==1) ){
				stop_moving();
			}


		}

	}
	return 0;
}


funcReturn move_forward(void){

	funcReturn ret1,ret2,ret3;


	lcd_moveCursor(0, 0);
	//	lcd_clear();
	lcd_send_string("Forward       ");
	ret1=SERVO_rotate(DEG_90);
	ret2=DCMotor_Rotate(LB_DC, DC_MOTOR_CW, 100);
	ret3=DCMotor_Rotate(RB_DC, DC_MOTOR_CW, 100);

	if(ret1 || ret2 || ret3 ){
		return NOT_OK;
	}
	return OK;

}

funcReturn move_backward(void){
	funcReturn ret1,ret2,ret3;


	lcd_moveCursor(0, 0);
	lcd_send_string("Backward        ");
	ret1=SERVO_rotate(DEG_90);
	ret2=DCMotor_Rotate(LB_DC, DC_MOTOR_CCW, 100);
	ret3=DCMotor_Rotate(RB_DC, DC_MOTOR_CCW, 100);

	if(ret1 || ret2 || ret3 ){
		return NOT_OK;
	}
	return OK;

}



funcReturn move_forward_slightly_right(void){
	funcReturn ret1,ret2,ret3;

	lcd_moveCursor(0, 0);
	lcd_send_string("Slightly right");
	ret1=SERVO_rotate(DEG_45);
	ret2=DCMotor_Rotate(LB_DC, DC_MOTOR_CW, 100);
	ret3=DCMotor_Rotate(RB_DC, DC_MOTOR_CW, 100);

	if(ret1 || ret2 || ret3 ){
		return NOT_OK;
	}
	return OK;

}


funcReturn move_forward_slightly_left(void){
	funcReturn ret1,ret2,ret3;

	lcd_moveCursor(0, 0);
	lcd_send_string("Slightly left ");
	ret1=SERVO_rotate(DEG_135);
	ret2=DCMotor_Rotate(LB_DC, DC_MOTOR_CW, 100);
	ret3=DCMotor_Rotate(RB_DC, DC_MOTOR_CW, 100);

	if(ret1 || ret2 || ret3 ){
		return NOT_OK;
	}
	return OK;

}


funcReturn stop_moving(void){
	funcReturn ret1,ret2,ret3;

	lcd_moveCursor(0, 0);
	lcd_send_string("Stopped       ");
	ret1=SERVO_rotate(DEG_90);
	ret2=DCMotor_Rotate(LB_DC, DC_MOTOR_STOP, 0);
	ret3=DCMotor_Rotate(RB_DC, DC_MOTOR_STOP, 0);

	if(ret1 || ret2 || ret3 ){
		return NOT_OK;
	}
	return OK;

}


funcReturn check_surroudings(void){

	funcReturn ret1,ret2,ret3,ret4;

	ret1=IR_PROXIMITY_read(RIGHT_IR, &right_ir_return);
	ret2=IR_PROXIMITY_read(LEFT_IR, &left_ir_return);
	ret3=IR_PROXIMITY_read(FRONT_IR, &front_ir_return);
	ret4=IR_PROXIMITY_read(BACK_IR, &back_ir_return);

	if(ret1 || ret2 || ret3 || ret4){
		return NOT_OK;
	}
	return OK;
}


funcReturn pass_theObstacle(void){

	funcReturn ret1,ret2,ret3;

	if( (right_ir_return==0) && (left_ir_return==1) && (back_ir_return==0) ){	//back and right are empty
		move_backward();
		_delay_ms(500);

		move_forward_slightly_right();
		_delay_ms(1000);

		move_forward_slightly_left();
		_delay_ms(500);

		while(left_ir_return==1){
			ret1=IR_PROXIMITY_read(LEFT_IR, &left_ir_return);
			move_forward();
			_delay_ms(500);
			if(ret1 == 0){
				return NOT_OK;
			}
		}

		move_forward_slightly_left();
		_delay_ms(500);
		move_forward();

		lcd_moveCursor(0, 0);
		lcd_send_string("passed obstacle");
	}
	else if( (right_ir_return==1) && (left_ir_return==0) && (back_ir_return==0) ){	//back and left are empty
		move_backward();
		_delay_ms(500);

		move_forward_slightly_left();
		_delay_ms(1000);

		move_forward_slightly_right();
		_delay_ms(500);

		while(right_ir_return==1){
			ret2=IR_PROXIMITY_read(RIGHT_IR, &right_ir_return);
			move_forward();
			_delay_ms(500);
			if(ret2 == 0){
				return NOT_OK;
			}
		}
		SET_BIT(DDRA,0);
		CLEAR_BIT(PORTA,0);

		CLEAR_BIT(PORTA,0);
		SET_BIT(PORTA,0);
		move_forward_slightly_right();
		_delay_ms(500);
		move_forward();

		lcd_moveCursor(0, 0);
		lcd_send_string("passed obstacle");

	}
	else if( (right_ir_return==1) && (left_ir_return==1) && (back_ir_return==1) ){	//back and left are empty
		stop_moving();

		lcd_moveCursor(0, 0);
		lcd_send_string("obstacle can't be passed");
	}else{
		move_backward();
		_delay_ms(500);

		move_forward_slightly_right();
		_delay_ms(1000);

		move_forward_slightly_left();
		_delay_ms(500);

		while(left_ir_return==1){
			ret3=IR_PROXIMITY_read(LEFT_IR, &left_ir_return);
			move_forward();
			_delay_ms(500);
			if(ret3 == 0){
				return NOT_OK;
			}
		}

		move_forward_slightly_left();
		_delay_ms(500);
		move_forward();

		lcd_moveCursor(0, 0);
		lcd_send_string("passed obstacle");
	}

	return OK;
}


//void debug(void){
//	SET_BIT(DDRA,0);
//	CLEAR_BIT(PORTA,0);
//
//	CLEAR_BIT(PORTA,0);
//	SET_BIT(PORTA,0);
//}
//
//
//void displayData(uint8 *arr){
//
//	uint8 c=0;
//
//	//	uint8 ch=0;
//
//	for(c=0;c<11;c++){
//		//		ch= arr[i];
//		//		if( (arr[i]<=57) && (arr[i]>=48) ){
//		//				if( (arr[i]<=0) && (arr[i]>=9) ){
//		//		if(isdigit(ch)){
//		//		if( ch >= '0' && ch <= '9' ){
//		if( (arr[c]==1) || (arr[c]==2) || (arr[c]==3) || (arr[c]==4) || (arr[c]==5) || (arr[c]==6) || (arr[c]==7) || (arr[c]==8) || (arr[c]==9)|| (arr[c]==0) ){
//			LCD_intgerToString(arr[c]);
//		}else{
//			lcd_send_char(arr[c]);
//		}
//	}
//
//
//}




