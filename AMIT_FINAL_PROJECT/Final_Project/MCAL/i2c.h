/* Heder file for I2C */

#include <avr/io.h>
#include "std_types.h"



void i2c_init();

		//Start condition
void i2c_start();

		//I2C stop condition
void i2c_write(uint8 x);


char i2c_read();
