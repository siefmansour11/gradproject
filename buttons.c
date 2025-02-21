#include <avr/io.h>
#include "DIO.h"
#include "buttons.h"

void init_BTNS(){
    DIO_Set_PIN_DIR(BTN0_PORT, BTN0, INPUT);
    DIO_Set_PIN_DIR(BTN1_PORT, BTN1, INPUT);
    DIO_Set_PIN_DIR(BTN2_PORT, BTN2, INPUT);
    DIO_Set_PIN_DIR(BTN3_PORT, BTN3, INPUT);
    DIO_Set_PIN_DIR(BTN4_PORT, BTN4, INPUT);
}

char BTNs_isPressed(char BTN){
    char PIN_Data = 0;
    switch(BTN){
        case BTN0:
            DIO_Read_PIN(BTN0_PORT, BTN0, &PIN_Data);
            break;
        case BTN1:
            DIO_Read_PIN(BTN1_PORT, BTN1, &PIN_Data);
            break;
        case BTN2:
            DIO_Read_PIN(BTN2_PORT, BTN2, &PIN_Data);
            break;
        case BTN3:
            DIO_Read_PIN(BTN3_PORT, BTN3, &PIN_Data);
            break;   
        case BTN4:
            DIO_Read_PIN(BTN4_PORT, BTN4, &PIN_Data);
            break;  
    }
    return PIN_Data;
}
