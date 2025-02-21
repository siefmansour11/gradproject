#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <avr/io.h> 
#define LED0_ID  0
#define LED1_ID  1
#define LED2_ID  2
#define LED3_ID  3
#define LED4_ID  4

#define LED0  PC2
#define LED1  PC7
#define LED2  PD3
#define LED3  PD4
#define LED4  PD1

#define LED0_PORT  &PORTC
#define LED1_PORT  &PORTC
#define LED2_PORT  &PORTD
#define LED3_PORT  &PORTD
#define LED4_PORT  &PORTD

void init_LEDs();
void LEDs_ON();
void LEDs_OFF();
void LED_ON(uint8_t LED);
void LED_OFF(uint8_t LED);

#endif /* LED_H */
