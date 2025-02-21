
#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h> 
#define  servo   PD5
#define  servo_PORT  &PORTD
 
void Servo_init();
void Servo_OpenDoor();
void Servo_CloseDoor();

#endif

