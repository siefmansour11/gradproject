
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "mUART.h"

#define F_CPU 16000000UL

void init_UART(int BaudRate){
    
    
    
    UCSRB |= (1<<TXEN)|(1<<RXEN);
    
    // set Baudrate
//    short UBRR = (F_CPU/16.0/BaudRate)-1 ;
//    UBRRL = (char)UBRR;
//    UBRRH = UBRR >> 8;
    UBRRL = 103;
    
    
    
}

void UART_INT_Enable(char UART_INT){
    UCSRB |= (1<<UART_INT);
}

void UART_send(char cData){
    while(!(UCSRA & (1<<UDRE)));
    UDR = cData;
}
void UART_send_str(char* pData){
    
    for(int i = 0 ; pData[i]!= '\0'; i++){
         UART_send(pData[i]);
    }
    
}
void UART_send_num(int num){
    
    char str[11];
    itoa(num, str, 10);
    UART_send_str(str);
}

char UART_receive(){
    while(!(UCSRA & (1<<RXC)));
    return UDR;
}


uint8_t UART_Available(void) {
    return (UCSRA & (1 << RXC));  
}
