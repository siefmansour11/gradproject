/* 
 * File:   fanrelay.h
 * Author: safe
 *
 * Created on February 14, 2025, 2:47 PM
 */

#ifndef FANRELAY_H
#define	FANRELAY_H


#define fanrelay PD7
#define fanrelay_PORT &PORTD

void init_fanrelay();
void fanrelay_ON();
void fanrelay_OFF();

#endif	/* FANRELAY_H */

