#ifndef LCD_H
#define LCD_H
/*
 * relyq's lcd library
 * atmega328
 * hd44780
 */

#include <stdint.h>

#define LCD_SAME_DATA_PORT    1  // if all data pins are on the same port
#define LCD_ORDERED_DATA_PINS 1  // if data pins are D4-D7 = 0-3

// if connecting data lines to the same port, use this
#if LCD_SAME_DATA_PORT
#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR  DDRD
#define LCD_DATA_PIN  PIND

// if connecting data lines to different ports, use this
#else
#define LCD_DATA4_PORT PORTD
#define LCD_DATA5_PORT PORTD
#define LCD_DATA6_PORT PORTD
#define LCD_DATA7_PORT PORTD

#define LCD_DATA4_DDR DDRD
#define LCD_DATA5_DDR DDRD
#define LCD_DATA6_DDR DDRD
#define LCD_DATA7_DDR DDRD

#define LCD_DATA4_PIN PIND
#define LCD_DATA5_PIN PIND
#define LCD_DATA6_PIN PIND
#define LCD_DATA7_PIN PIND
#endif

#if !LCD_ORDERED_DATA_PINS
#define LCD_DATA4 PD0
#define LCD_DATA5 PD1
#define LCD_DATA6 PD2
#define LCD_DATA7 PD3
#endif

// instruction lines
#define LCD_RS_PORT PORTB
#define LCD_EN_PORT PORTB

#define LCD_RS_DDR DDRB
#define LCD_EN_DDR DDRB

#define LCD_RS PB1
#define LCD_EN PB2

#define LCD_INSTRUCTION_DDR DDRB

// command macros       // lcd_command()
#define LCD_CLEAR      _BV(LCD_CLEARDISPLAY)
#define LCD_CURSOR_OFF _BV(LCD_ON) | _BV(LCD_ON_DISPLAY)
#define LCD_CURSOR     LCD_CURSOR_OFF | _BV(LCD_ON_CURSOR)
#define LCD_BLINK      LCD_CURSOR_OFF | _BV(LCD_ON_BLINK)
#define LCD_CURBLINK   LCD_CURSOR | _BV(LCD_ON_BLINK)

// bit position macros  // lcd_write()
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
#define LCD_SET_CGRAM       6
#define LCD_SET_DDRAM       7

#define LCD_LINE0_START 0x00
#define LCD_LINE1_START 0x40

// instruction bit position
#define LCD_BUSYFLAG 7

// all timings are in uS
#define LCD_DELAY_ENABLE_PULSE 1
#define LCD_DELAY_BUSYFLAG     4
#define LCD_DELAY_CLEAR        1600
#define LCD_DELAY_HOME         1600

#define LCD_ENABLE_DELAY() _delay_us(LCD_DELAY_ENABLE_PULSE)

#define LCD_ENABLE_SET()   LCD_EN_PORT |= _BV(LCD_EN)
#define LCD_ENABLE_CLEAR() LCD_EN_PORT &= ~_BV(LCD_EN)
#define LCD_RS_SET()       LCD_RS_PORT |= _BV(LCD_RS)
#define LCD_RS_CLEAR()     LCD_RS_PORT &= ~_BV(LCD_RS)

void LCD_init(void);
void LCD_command(uint8_t command);
void LCD_clear(void);
void LCD_cursor(uint8_t y, uint8_t x);
void LCD_putc(char c);
void LCD_puts(const char* str);

#endif
