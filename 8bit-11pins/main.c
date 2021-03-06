#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "lcd.h"

int main(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  LCD_init();
  LCD_puts("123");
  LCD_command(LCD_CURSOR);
  LCD_cursor(1, 0);
  LCD_puts("456");

  while (1) {
    sleep_mode();
  }
}
