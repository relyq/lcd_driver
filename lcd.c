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

// public interface functions
void LCD_clear(void) {
  LCD_write((_BV(LCD_CLEARDISPLAY)), 0);

  LCD_waitbusy();
}

void LCD_function_set(void) {
  LCD_write((_BV(LCD_FUNCTION)) | (_BV(LCD_FUNCTION_8BIT)) |
                (_BV(LCD_FUNCTION_2LINES)),
            0);  // 8-bit; 2-line; 5x8 font

  LCD_waitbusy();
}

void LCD_display_control(void) {
  LCD_write((_BV(LCD_ON)) | (_BV(LCD_ON_DISPLAY)) | (_BV(LCD_ON_CURSOR)),
            0);  // display on; static cursor

  LCD_waitbusy();
}

void LCD_entry_mode(void) {
  LCD_write((_BV(LCD_ENTRY)) | (_BV(LCD_ENTRY_INC)), 0);

  LCD_waitbusy();
}

void LCD_putc(char c) {
  LCD_write(c, 1);

  LCD_waitbusy();
}
