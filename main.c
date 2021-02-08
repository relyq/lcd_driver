#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "lcd.h"

int main(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  LCD_init();
  LCD_puts("sogui<3");

  LCD_cursor_set(0, 1);
  while (1) {
    sleep_mode();
  }
}
