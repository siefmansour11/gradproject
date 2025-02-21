

#include <avr/io.h>
#include "fanrelay.h"
#include "DIO.h"



void init_fanrelay(){
    DIO_Set_PIN_DIR(fanrelay_PORT, fanrelay, OUTPUT);
}
void fanrelay_ON(){
    DIO_Set_PIN_VALUE(fanrelay_PORT, fanrelay, HIGH);
}
void fanrelay_OFF(){
    DIO_Set_PIN_VALUE(fanrelay_PORT, fanrelay, LOW);
}
