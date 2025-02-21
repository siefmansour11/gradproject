
#include "led.h"
#include "DIO.h"
#include <avr/io.h>

void init_LEDs() {
    DIO_Set_PIN_DIR(LED0_PORT, LED0, OUTPUT);
    DIO_Set_PIN_DIR(LED1_PORT, LED1, OUTPUT);
    DIO_Set_PIN_DIR(LED2_PORT, LED2, OUTPUT);
    DIO_Set_PIN_DIR(LED3_PORT, LED3, OUTPUT);
    DIO_Set_PIN_DIR(LED4_PORT, LED4, OUTPUT);
}

void LEDs_ON() {
    LED_ON(LED0_ID);
    LED_ON(LED1_ID);
    LED_ON(LED2_ID);
    LED_ON(LED3_ID);
    LED_ON(LED4_ID);
}

void LEDs_OFF() {
    LED_OFF(LED0_ID);
    LED_OFF(LED1_ID);
    LED_OFF(LED2_ID);
    LED_OFF(LED3_ID);
    LED_OFF(LED4_ID);
}

void LED_ON(uint8_t LED) {
    switch (LED) {
        case LED0_ID:
            DIO_Set_PIN_VALUE(LED0_PORT, LED0, HIGH);
            break;
        case LED1_ID:
            DIO_Set_PIN_VALUE(LED1_PORT, LED1, HIGH);
            break;
        case LED2_ID:
            DIO_Set_PIN_VALUE(LED2_PORT, LED2, HIGH);
            break;
        case LED3_ID:
            DIO_Set_PIN_VALUE(LED3_PORT, LED3, HIGH);
            break;
        case LED4_ID:
            DIO_Set_PIN_VALUE(LED4_PORT, LED4, HIGH);
            break;
        default:
            break;
    }
}

void LED_OFF(uint8_t LED) {
    switch (LED) {
        case LED0_ID:
            DIO_Set_PIN_VALUE(LED0_PORT, LED0, LOW);
            break;
        case LED1_ID:
            DIO_Set_PIN_VALUE(LED1_PORT, LED1, LOW);
            break;
        case LED2_ID:
            DIO_Set_PIN_VALUE(LED2_PORT, LED2, LOW);
            break;
        case LED3_ID:
            DIO_Set_PIN_VALUE(LED3_PORT, LED3, LOW);
            break;
        case LED4_ID:
            DIO_Set_PIN_VALUE(LED4_PORT, LED4, LOW);
            break;
        default:
            break;
    }
}
