
#include "motor.h"
#include "DIO.h"
#include <avr/io.h>
void Motor_Init() {
    DIO_Set_PIN_DIR(&PORTD, 4, OUTPUT);
}

void Motor_On() {
    DIO_Set_PIN_VALUE(&PORTD, 4, HIGH);
}

void Motor_Off() {
    DIO_Set_PIN_VALUE(&PORTD, 4, LOW);
}
