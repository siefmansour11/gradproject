
#ifndef MLCD4_H
#define	MLCD4_H


#define LCD_DATA_DIR            &DDRA
#define LCD_DATA_PORT           &PORTA

#define LCD_CONTROL_PINS_DIR    &DDRB
#define LCD_CONTROL_PINS_PORT   &PORTB


#define LCD_EN    PB3
#define LCD_RW    PB2
#define LCD_RS    PB1


// APIs
void init_LCD4();

void LCD4_write(char data);
void LCD4_cmd(char cmd);

void LCD4_clear();

void LCD4_Enable();

void LCD4_str(char * arr);

void LCD4_num(int num);
void LCD4_newline(void);

#endif	/* MLCD4_H */
