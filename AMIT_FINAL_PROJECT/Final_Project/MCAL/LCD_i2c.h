

#include "std_types.h"

#define LCD_1   0x72


//-----Proto-Type-------//
void lcd_init();			//----LCD Initializing Function
void toggle();				//----Latching function of LCD
void lcd_send_cmd (uint8 cmd);		//----Function to send Command to LCD
void lcd_send_hf_cmd(uint8 cmd);      //----Function to send half Command to LCD
void lcd_send_char (uint8 data);		//----Function to send data to LCD
void lcd_send_number (uint8 data);
void LCD_intgerToString(uint8 data);

void lcd_clear(void);			//----Function to clear LCD
void lcd_moveCursor(uint16 row, uint16 col);		//----Function to change Cursor of Lcd
void lcd_send_string(uint8 *str);		//----Function to Send String to LCD
void delay(uint16 ms);
//----------------------//


