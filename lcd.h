#ifndef LCD_H
#define LCD_H
/*
 * relyq's lcd library
 * atmega328
 * hd44780
 */

#define LCD_DATA_PORT        PORTD
#define LCD_INSTRUCTION_PORT PORTB
#define LCD_DATA_DDR         DDRD
#define LCD_INSTRUCTION_DDR  DDRB
#define LCD_DATA_PIN         PIND

#define LCD_RW PB0
#define LCD_RS PB1
#define LCD_EN PB2

#define LCD_CLEARDISPLAY    0
#define LCD_RETURNHOME      1
#define LCD_ENTRY           2
#define LCD_ENTRY_INC       1
#define LCD_ENTRY_SHIFT     0
#define LCD_ON              3
#define LCD_ON_DISPLAY      2
#define LCD_ON_CURSOR       1
#define LCD_ON_BLINK        0
#define LCD_FUNCTION        5
#define LCD_FUNCTION_8BIT   4
#define LCD_FUNCTION_2LINES 3

// instruction bit position
#define LCD_BUSYFLAG 7

// all timings are in uS
#define LCD_DELAY_ENABLE_PULSE 1
#define LCD_DELAY_BUSYFLAG     4

#define LCD_ENABLE_DELAY() _delay_us(LCD_DELAY_ENABLE_PULSE)

#define LCD_ENABLE_SET()   LCD_INSTRUCTION_PORT |= _BV(LCD_EN)
#define LCD_ENABLE_CLEAR() LCD_INSTRUCTION_PORT &= ~_BV(LCD_EN)
#define LCD_RS_SET()       LCD_INSTRUCTION_PORT |= _BV(LCD_RS)
#define LCD_RS_CLEAR()     LCD_INSTRUCTION_PORT &= ~_BV(LCD_RS)
#define LCD_RW_SET()       LCD_INSTRUCTION_PORT |= _BV(LCD_RW)
#define LCD_RW_CLEAR()     LCD_INSTRUCTION_PORT &= ~_BV(LCD_RW)

#define LCD_SEND_INSTRUCTION() \
  {                            \
    LCD_INSTRUCTION_PORT = 0;  \
    LCD_enablePulse();         \
  }

void LCD_init(void);
void LCD_clear(void);
void LCD_function_set(void);
void LCD_display_control(void);
void LCD_entry_mode(void);
void LCD_putc(char c);

#endif
