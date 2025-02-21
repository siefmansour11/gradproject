/* 
 * File:   buzzer.h
 * Author: safe
 *
 * Created on January 31, 2025, 5:38 PM
 */

#ifndef buzzer_H
#define	buzzer_H


#define buzzer PA3
#define buzzer_PORT &PORTA

void init_Buzzer();
void Buzzer_ON();
void Buzzer_OFF();
void Buzzer_Play();
void Buzzer_PlayTone();
#endif	/* buzzer_H */


