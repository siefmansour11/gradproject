#include "keypad.h"
#include "DIO.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

const char keypad_keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void Keypad_init(void) {

    DIO_Set_PIN_DIR(&PORTB, KEYPAD_ROW1, OUTPUT);
    DIO_Set_PIN_DIR(&PORTB, KEYPAD_ROW2, OUTPUT);
    DIO_Set_PIN_DIR(&PORTB, KEYPAD_ROW3, OUTPUT);
    DIO_Set_PIN_DIR(&PORTB, KEYPAD_ROW4, OUTPUT);


    DIO_Set_PIN_DIR(&PORTC, KEYPAD_COL1, INPUT);
    DIO_Set_PIN_DIR(&PORTA, KEYPAD_COL2, INPUT);
    DIO_Set_PIN_DIR(&PORTA, KEYPAD_COL3, INPUT);
    DIO_Set_PIN_DIR(&PORTC, KEYPAD_COL4, INPUT);

    DIO_Set_PIN_VALUE(&PORTC, KEYPAD_COL1, HIGH);
    DIO_Set_PIN_VALUE(&PORTA, KEYPAD_COL2, HIGH);
    DIO_Set_PIN_VALUE(&PORTA, KEYPAD_COL3, HIGH);
    DIO_Set_PIN_VALUE(&PORTC, KEYPAD_COL4, HIGH);
}

char Keypad_GetKey(void) {
    int row, col;
    char key = '\0';
    char pin_value;

    for (row = 0; row < 4; row++) {

        DIO_Set_PIN_VALUE(&PORTB, KEYPAD_ROW1, HIGH);
        DIO_Set_PIN_VALUE(&PORTB, KEYPAD_ROW2, HIGH);
        DIO_Set_PIN_VALUE(&PORTB, KEYPAD_ROW3, HIGH);
        DIO_Set_PIN_VALUE(&PORTB, KEYPAD_ROW4, HIGH);


        DIO_Set_PIN_VALUE(&PORTB, KEYPAD_ROW1 + row, LOW);

        for (col = 0; col < 4; col++) {

            if (col == 0)
                DIO_Read_PIN(&PORTC, KEYPAD_COL1, &pin_value);
            else if (col == 1)
                DIO_Read_PIN(&PORTA, KEYPAD_COL2, &pin_value);
            else if (col == 2)
                DIO_Read_PIN(&PORTA, KEYPAD_COL3, &pin_value);
            else if (col == 3)
                DIO_Read_PIN(&PORTC, KEYPAD_COL4, &pin_value);

            if (pin_value == LOW) {
                key = keypad_keys[row][col];


                _delay_ms(50);
                while (pin_value == LOW) {
                    if (col == 0)
                        DIO_Read_PIN(&PORTC, KEYPAD_COL1, &pin_value);
                    else if (col == 1)
                        DIO_Read_PIN(&PORTA, KEYPAD_COL2, &pin_value);
                    else if (col == 2)
                        DIO_Read_PIN(&PORTA, KEYPAD_COL3, &pin_value);
                    else if (col == 3)
                        DIO_Read_PIN(&PORTC, KEYPAD_COL4, &pin_value);
                }
                return key;
            }
        }
    }
    return key;
}
