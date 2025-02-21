#include "TempANDmotor.h"
#include "DIO.h"
#include <avr/io.h>
#include <stdio.h>

#define TEMP_THRESHOLD 28  

void FlameSensor_init() {
    DIO_Set_PIN_DIR(&PORTC, 5, INPUT);  
}

uint8_t FlameSensor_Read() {
    uint8_t flameStatus = 0;  
    DIO_Read_PIN(&PORTC, 5, (char*)&flameStatus);  
    return flameStatus;  
}
