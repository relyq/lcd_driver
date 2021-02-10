#include "lcd.h"

#include <avr/io.h>
#include <util/delay.h>

// private functions
static void LCD_enablePulse(void) {
  LCD_ENABLE_CLEAR();  // there should be a delay between calls // works tho
  LCD_ENABLE_SET();
  LCD_ENABLE_DELAY();
  LCD_ENABLE_CLEAR();
}

static uint8_t LCD_read(uint8_t reg) {
  uint8_t data = 0;

  if (reg)
    LCD_RS_SET();
  else
    LCD_RS_CLEAR();
  LCD_RW_SET();

  LCD_DATA_DDR = 0;  // set data port to input

  LCD_enablePulse();

  data = LCD_DATA_PIN;

  return data;
}

static uint8_t LCD_waitbusy() {
  register uint8_t byte = LCD_read(0);

  while (byte & (1 << LCD_BUSYFLAG)) {
    byte = LCD_read(0);
  }

  _delay_us(LCD_DELAY_BUSYFLAG);

  return LCD_read(0);
}

static void LCD_write(uint8_t byte, uint8_t reg) {
  if (reg)
    LCD_RS_SET();
  else
    LCD_RS_CLEAR();

  LCD_RW_CLEAR();

  LCD_DATA_DDR = 0xff;  // set data port to output

  LCD_DATA_PORT = byte;

  LCD_enablePulse();
}

void LCD_data(uint8_t byte) {
  LCD_write(byte, 1);
  LCD_waitbusy();
}

// public interface functions

void LCD_command(uint8_t command) {
  LCD_write(command, 0);
  LCD_waitbusy();
}

void LCD_clear(void) { LCD_command(LCD_CLEAR); }

void LCD_function_set(void) {
  LCD_command((_BV(LCD_FUNCTION)) | (_BV(LCD_FUNCTION_8BIT)) |
              (_BV(LCD_FUNCTION_2LINES)));  // 8-bit; 2-line; 5x8 font
}

void LCD_display_control(void) {
  LCD_command(LCD_CURSOR);  // display on; static cursor
}

void LCD_entry_mode(void) {
  LCD_command((_BV(LCD_ENTRY)) | (_BV(LCD_ENTRY_INC)));
}

void LCD_init(void) {
  DDRB = (_BV(LCD_RW)) | (_BV(LCD_RS)) |
         (_BV(LCD_EN));  // PB0 = RW, PB1 = RS, PB2 = EN
  _delay_ms(10);         // wait for display internal initialization to end
  LCD_clear();
  LCD_function_set();
  LCD_display_control();
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
