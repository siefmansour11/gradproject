#include "DIO.h"
#include "SERVO.h"
#include <avr/io.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "LCD4.h"

void Servo_init() {
    DIO_Set_PIN_DIR( servo_PORT  , servo , OUTPUT);
    
    TCCR1A = (1 << WGM11) | (1 << COM1A1); 
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11); 
    ICR1 = 19999; 
      OCR1A = 1500;
}

void Servo_OpenDoor() {
    LCD4_clear();
    char msg[] = "Servo ON";  
    LCD4_str(msg);            
    _delay_ms(1000);
    OCR1A = 1800;
}

void Servo_CloseDoor() {
    LCD4_clear();
    char msg[] = "Servo OFF";  
    LCD4_str(msg);
    _delay_ms(1000);
    OCR1A = 1200;
}
