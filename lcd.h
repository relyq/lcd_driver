#ifndef LCD_H
#define LCD_H
/*
 * relyq's lcd library
 * atmega328
 * hd44780
 */

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

// all timings are in uS
#define LCD_DELAY_ENABLE_PULSE 1

#define LCD_ENABLE_DELAY() _delay_us(LCD_DELAY_ENABLE_PULSE)

#define LCD_ENABLE_SET()    LCD_INSTRUCTION_PORT |= _BV(LCD_EN)
#define LCD_ENABLE_CLEAR()  LCD_INSTRUCTION_PORT &= ~_BV(LCD_EN)
#define LCD_RS_SET()    LCD_INSTRUCTION_PORT |= _BV(LCD_RS)
#define LCD_RS_CLEAR()  LCD_INSTRUCTION_PORT &= ~_BV(LCD_RS)
#define LCD_RW_SET()    LCD_INSTRUCTION_PORT |= _BV(LCD_RW)
#define LCD_RW_CLEAR()  LCD_INSTRUCTION_PORT &= ~_BV(LCD_RW)

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
void LCD_putc(char c);


#endif
