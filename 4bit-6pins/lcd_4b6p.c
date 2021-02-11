#include "lcd_4b6p.h"

#include <avr/io.h>
#include <util/delay.h>

// private functions
static void LCD_enablePulse(void) {
  LCD_ENABLE_CLEAR();  // there should be a delay between calls // works tho
  LCD_ENABLE_SET();
  LCD_ENABLE_DELAY();
  LCD_ENABLE_CLEAR();
}

static void LCD_write(uint8_t byte, uint8_t reg) {
  if (reg)
    LCD_RS_SET();
  else
    LCD_RS_CLEAR();

  uint8_t port_bits;

  LCD_DATA_DDR |= 0x0f;  // set data port to output

  port_bits = LCD_DATA_PORT & 0xf0;
  LCD_DATA_PORT = port_bits | ((byte >> 4) & 0x0f);
  LCD_enablePulse();

  LCD_DATA_PORT = port_bits | (byte & 0x0f);
  LCD_enablePulse();

  LCD_DATA_PORT = port_bits | 0x0f;
}

void LCD_data(uint8_t byte) {
  LCD_write(byte, 1);
  _delay_us(39);
}

void LCD_function_set(void) {
  LCD_command((_BV(LCD_FUNCTION)) |
              (_BV(LCD_FUNCTION_2LINES)));  // 8-bit; 2-line; 5x8 font
}

void LCD_display_control(void) {
  LCD_command(LCD_CURSOR_OFF);  // display on; static cursor
}

void LCD_entry_mode(void) {
  LCD_command((_BV(LCD_ENTRY)) | (_BV(LCD_ENTRY_INC)));
}

// public interface functions

void LCD_command(uint8_t command) {
  LCD_write(command, 0);
  _delay_us(37);  // min delay should be 37us
}

void LCD_clear(void) {
  LCD_command(LCD_CLEAR);
  _delay_us(LCD_DELAY_CLEAR);
}

void LCD_init(void) {
  LCD_RS_DDR |= _BV(LCD_RS);
  LCD_EN_DDR |= _BV(LCD_EN);
  _delay_ms(40);  // wait for display internal initialization to end
  LCD_function_set();
  LCD_display_control();
  LCD_clear();
  LCD_entry_mode();
}

void LCD_cursor(uint8_t y, uint8_t x) {
  if (!y) {
    LCD_command((1 << LCD_SET_DDRAM) + LCD_LINE0_START + x);
  } else {
    LCD_command((1 << LCD_SET_DDRAM) + LCD_LINE1_START + x);
  }
}

void LCD_putc(char c) { LCD_data(c); }

void LCD_puts(const char* str) {
  while (*str) {
    LCD_putc(*str);
    str++;
  }
}
