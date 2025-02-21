/* 
 * File:   keypad.h
 * Author: safe
 *
 * Created on January 31, 2025, 6:24 PM
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

#define KEYPAD_ROW1    PB4
#define KEYPAD_ROW2    PB5
#define KEYPAD_ROW3    PB6
#define KEYPAD_ROW4    PB7

#define KEYPAD_COL1    PC0
#define KEYPAD_COL2    PA1
#define KEYPAD_COL3    PA0
#define KEYPAD_COL4    PC1
void Keypad_init(void);
char Keypad_GetKey(void);

#endif /* KEYPAD_H */




