
#include "DIO.h"
#include "Bluetooth.h"
#include <avr/io.h>

void Bluetooth_init() {
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (3 << UCSZ0);
    UBRRL = 51; 
    //9600
}

char Bluetooth_Receive() {
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}
