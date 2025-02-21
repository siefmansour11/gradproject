#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include"DIO.h"
#include "LCD4.h"
#include <stdlib.h>
#include <string.h>

void init_LCD4() {

    // Data Directions for all LCD PINs
    DIO_Set_PORT_DIR(LCD_DATA_PORT, 0xF0);
    DIO_Set_PIN_DIR(LCD_CONTROL_PINS_PORT, LCD_EN, OUTPUT);
    DIO_Set_PIN_DIR(LCD_CONTROL_PINS_PORT, LCD_RS, OUTPUT);
    DIO_Set_PIN_DIR(LCD_CONTROL_PINS_PORT, LCD_RW, OUTPUT);


    // Command to setup LCD
    // According to LCD Data Sheet
    _delay_ms(10);
    LCD4_cmd(0x02);
    LCD4_cmd(0x06);
    LCD4_cmd(0x0C);
    _delay_ms(10);

}

void LCD4_write(char data) {

    // Select Data Register
    DIO_Set_PIN_VALUE(LCD_CONTROL_PINS_PORT, LCD_RS, HIGH);
    // xxxxxxxx
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F)|(data & 0xf0);
    LCD4_Enable();
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F)|(data<<4);
    LCD4_Enable();
    
}

void LCD4_cmd(char cmd) {
    // Select Instruction Register
    DIO_Set_PIN_VALUE(LCD_CONTROL_PINS_PORT, LCD_RS, LOW);

    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F)|(cmd & 0xf0);
    LCD4_Enable();
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F)|(cmd<<4);
    LCD4_Enable();
}

void LCD4_clear() {
    LCD4_cmd(0x01);
    _delay_ms(10);
}

void LCD4_Enable() {
    DIO_Set_PIN_VALUE(LCD_CONTROL_PINS_PORT, LCD_EN, HIGH);
    _delay_us(50);
    DIO_Set_PIN_VALUE(LCD_CONTROL_PINS_PORT, LCD_EN, LOW);
}

void LCD4_str(char * arr) {
    for (int i = 0; arr[i] != '\0'; i++) {
        LCD4_write(arr[i]);
    }
}


void LCD4_num(int num){
    // Convert Num to a string
    char str[11];
    
    itoa(num, str, 10);
    
    LCD4_str(str);
}
void LCD4_newline(void) {
    LCD4_cmd(0xC0); 
}
