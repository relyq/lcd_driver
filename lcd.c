#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void LCD_enablePulse(void){
  LCD_ENABLE_CLEAR(); // there should be a delay between calls // works tho
  LCD_ENABLE_SET();
  LCD_ENABLE_CLEAR();
}

void LCD_clear(void){
  LCD_DATA_PORT = LCD_CLEARDISPLAY;
  LCD_SEND_INSTRUCTION();

  _delay_us(2000);
}

void LCD_function_set(void){
  LCD_DATA_PORT = LCD_FUNCTIONSET | (_BV(4)) | (_BV(3)); // 8-bit; 2-line; 5x8 font
  LCD_INSTRUCTION_PORT = 0; 
  LCD_enablePulse();

  _delay_us(37);
}

void LCD_display_control(void){
  LCD_DATA_PORT = LCD_DISPLAYCONTROL | (_BV(2)) | (_BV(1)); // display on; static cursor
  LCD_INSTRUCTION_PORT = 0; 
  LCD_enablePulse();

  _delay_us(37);
}

void LCD_entry_mode(void){
  LCD_DATA_PORT = LCD_ENTRYMODESET | (_BV(1));
  LCD_INSTRUCTION_PORT = 0;
  LCD_enablePulse();

  _delay_us(37);
}

void LCD_putc(char c){
  LCD_DATA_PORT = c;
  LCD_INSTRUCTION_PORT = (_BV(LCD_RS));
  LCD_enablePulse();

  _delay_us(37);
}
