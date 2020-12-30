#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include "lcd.h"

int main(void){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  DDRD = 0xff; // port d is lcd data byte
  DDRB = (_BV(LCD_RW)) | (_BV(LCD_RS)) | (_BV(LCD_EN)); // PB0 = RW, PB1 = RS, PB2 = EN

  _delay_ms(10); // wait for display internal initialization to end

  LCD_clear();
  LCD_function_set();
  LCD_display_control();
  LCD_entry_mode();
  LCD_putc('s');
  LCD_putc('o');
  LCD_putc('g');
  LCD_putc('u');
  LCD_putc('i');
  LCD_putc('<');
  LCD_putc('3');

  while (1) {
    sleep_mode();
  }
}
