
#include <avr/io.h>
#include "buzzer.h"

#include "DIO.h"
#define F_CPU 16000000UL
#include <util/delay.h>


void init_Buzzer(){
    DIO_Set_PIN_DIR(buzzer_PORT, buzzer, OUTPUT);
  
}
void Buzzer_ON(){
    DIO_Set_PIN_VALUE(buzzer_PORT, buzzer, HIGH);
}
void Buzzer_OFF(){
    DIO_Set_PIN_VALUE(buzzer_PORT, buzzer, LOW);
}
void Buzzer_Play(){
    Buzzer_ON();
    _delay_ms(200);
    Buzzer_OFF();
    _delay_ms(100);
    Buzzer_ON();
    _delay_ms(300);
    Buzzer_OFF();
    _delay_ms(200);
    Buzzer_ON();
    _delay_ms(100);
    Buzzer_OFF();
    _delay_ms(200);
}
void Buzzer_PlayTone(){
    
    for(int i = 10; i<100; i+=5){
        Buzzer_ON();
        for(int n =0; n<i;n++){
            _delay_ms(1);
        }
        
        Buzzer_OFF();
        for(int n =0; n<(100-i);n++){
            _delay_ms(1);
        }
        
    }
}
