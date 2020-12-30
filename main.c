#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>

#define LCD_DATA_PORT         PORTD
#define LCD_INSTRUCTION_PORT  PORTB
#define LCD_DATA_DDR          DDRD
#define LCD_INSTRUCTION_DDR   DDRB

#define LCD_RW PB0
#define LCD_RS PB1
#define LCD_EN PB2

#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_FUNCTIONSET     0x20

#define LCD_ENABLE_SET() LCD_INSTRUCTION_PORT |= _BV(LCD_EN)
#define LCD_ENABLE_CLEAR() LCD_INSTRUCTION_PORT &= ~_BV(LCD_EN)

#define LCD_SEND_INSTRUCTION() {  \
  LCD_INSTRUCTION_PORT = 0;       \
  LCD_enablePulse();              \
}

void LCD_enablePulse(void);
void LCD_init(void);
void LCD_clear(void);
void LCD_function_set(void);
void LCD_display_control(void);
void LCD_entry_mode(void);

int main(void){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  DDRD = 0xff; // port d is lcd data byte
  DDRB = (_BV(LCD_RW)) | (_BV(LCD_RS)) | (_BV(LCD_EN)); // PB0 = RW, PB1 = RS, PB2 = EN

  _delay_ms(10); // wait for display internal initialization to end

  LCD_clear();

  LCD_function_set();

  LCD_display_control();

  LCD_entry_mode();
 
  LCD_DATA_PORT = 's';
  LCD_INSTRUCTION_PORT = (_BV(PB1));
  LCD_enablePulse();

  while (1) {
    sleep_mode();
  }
}

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
  LCD_DATA_PORT = LCD_FUNCTIONSET | (_BV(PD4)) | (_BV(PD3)); // 8-bit; 2-line; 5x8 font
  LCD_INSTRUCTION_PORT = 0; 
  LCD_enablePulse();

  _delay_us(37);
}

void LCD_display_control(void){
  LCD_DATA_PORT = LCD_DISPLAYCONTROL | (_BV(PD2)) | (_BV(PD1)); // display on; static cursor
  LCD_INSTRUCTION_PORT = 0; 
  LCD_enablePulse();

  _delay_us(37);
}

void LCD_entry_mode(void){
  LCD_DATA_PORT = LCD_ENTRYMODESET | (_BV(PD1));
  LCD_INSTRUCTION_PORT = 0;
  LCD_enablePulse();

  _delay_us(37);
}
