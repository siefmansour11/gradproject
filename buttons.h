/* 
 * File:   buttons.h
 * Author: safe
 *
 * Created on January 31, 2025, 5:45 PM
 */
#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>

#define BTN0  0
#define BTN1  1
#define BTN2  2
#define BTN3  3
#define BTN4  4

#define BTN0_PORT    &PORTB
#define BTN1_PORT    &PORTD
#define BTN2_PORT    &PORTD
#define BTN3_PORT    &PORTD
#define BTN4_PORT    &PORTC

#define BTN0_PIN    PB0
#define BTN1_PIN    PD6
#define BTN2_PIN    PD2
#define BTN3_PIN    PD0
#define BTN4_PIN    PC6

void init_BTNS();
char BTNs_isPressed(char BTN);

#endif
