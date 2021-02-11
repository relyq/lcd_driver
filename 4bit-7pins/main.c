#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "lcd_4b7p.h"

int main(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  LCD_init();
  LCD_puts("funciona");
  LCD_cursor(1, 0);
  LCD_puts("o.o");

  while (1) {
    sleep_mode();
  }
}
