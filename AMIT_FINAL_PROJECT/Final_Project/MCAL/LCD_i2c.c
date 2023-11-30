/*
 * LCD_i2c.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Hesham
 */

#include <avr/io.h>
#include <util/delay.h>
#include "LCD_i2c.h"


void toggle ()
{
	TWDR |= 0x02;					//---PIN En de la LCD en = 1;  -----Latching data in to LCD data register using High to Low signal
	TWCR = (1<<TWINT) | (1<<TWEN);	//---Enable I2C and clear interrupt- Esta linea y la siguiente simepre van despues de querer mandar un coamndo por TDWR
	while  (!(TWCR &(1<<TWINT)));	//---Simepre poner despues de la linea anterior al mandar datos por TWDR
	delay(1);
	TWDR &= ~0x02;					//---PIN del Enable de la LCD en = 0;
	TWCR = (1<<TWINT) | (1<<TWEN);	//---Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
}

void lcd_send_cmd (uint8 cmd)
{
    TWDR&=~0x01;                    //rs = 0; ----Selecting register as command register
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    TWDR &= 0x0F;                   //----clearing the Higher 4 bits
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    TWDR |= (cmd & 0xF0);            //----Masking higher 4 bits and sending to LCD
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    toggle();

    TWDR &= 0x0F;                    //----clearing the Higher 4 bits
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    TWDR |= ((cmd & 0x0F)<<4);        //----Masking lower 4 bits and sending to LCD
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    toggle();
}

void lcd_send_hf_cmd(uint8 cmd)
{
	TWDR &=~0x01;					//PIN RS de la LCD rs = 0; ----Selecting register as Command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;					//----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (cmd & 0xF0);			//----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}


void lcd_send_char (uint8 data)
{
    TWDR|=0x01;                        //rs = 1; ----Selecting register as command register
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    TWDR &= 0x0F;                    //----clearing the Higher 4 bits
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    TWDR |= (data & 0xF0);            //----Masking higher 4 bits and sending to LCD
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    toggle();

    TWDR &= 0x0F;                    //----clearing the Higher 4 bits
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    TWDR |= ((data & 0x0F)<<4);        //----Masking lower 4 bits and sending to LCD
    TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
    while  (!(TWCR &(1<<TWINT)));
    toggle();
}


void lcd_send_number (uint8 data){

	uint8 mod;

	while(data > 0) //do till num greater than  0
	    {
	         mod = data % 10;  //split last digit from number

	        data = data / 10;    //divide num by 10. num /= 10 also a valid one
	    	lcd_send_char (mod+30);

	    }

}

void LCD_intgerToString(uint8 data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   lcd_send_string(buff); /* Display the string */
}

void lcd_init ()
{
    lcd_send_hf_cmd(0x30);       //-----Sequence for initializing LCD
    lcd_send_hf_cmd(0x30);       //-----     "            "              "               "
    lcd_send_hf_cmd(0x20);       //-----     "            "              "               "
    lcd_send_cmd(0x28);          //-----Selecting 16 x 2 LCD in 4Bit mode
    lcd_send_cmd(0x0C);          //-----Display ON Cursor OFF
    lcd_send_cmd(0x01);          //-----Clear display
    lcd_send_cmd(0x06);          //-----Cursor Auto Increment
    lcd_send_cmd(0x80);          //-----1st line 1st location of LCD
}

void delay (uint16 ms)
{
//	_delay_ms(ms);
    uint8 i,j;
    for(i=0;i<=ms;i++)
    for(j=0;j<=120;j++);
}

void lcd_send_string (uint8 *str)
{
    while (*str) lcd_send_char (*str++);
}

void lcd_moveCursor(uint16 row, uint16 col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}

void lcd_clear (void)
{
    uint8 i;
	lcd_send_cmd (0x80);
	for (i=0; i<70; i++)
	{
		lcd_send_char (' ');
	}
//	lcd_moveCursor(0,0);
}
