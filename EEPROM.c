#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h> 
#include <stdlib.h>      
#include "LCD4.h"
#include "keypad.h"
#include"EEPROM.h"

#define EEPROM_START_ADDR 0x00
#define MAX_USERS 5

char EEPROM_read(int address) { 
    while (EECR & (1 << EEWE));  
    EEARL = (char)address;
    EEARH = (char)(address >> 8);
    EECR |= (1 << EERE);  
    return EEDR;
}

void EEPROM_write(int address, char data) {
    if (EEPROM_read(address) != data) {  
        while (EECR & (1 << EEWE));  
        EEARL = (char)address;
        EEARH = (char)(address >> 8);
        EEDR = data;
        EECR = (1 << EEMWE);
        EECR |= (1 << EEWE);
    }
}

void Store_User(int index, char userID, char password) {
    if (Keypad_GetKey() == '5') return;  // ???? ??? ??? ???????? 5 ????? ???????
    
    int addr = EEPROM_START_ADDR + (index * 2);
    EEPROM_write(addr, userID);
    EEPROM_write(addr + 1, password);
}

void Retrieve_Users(void) {
    char buffer[3];
    char msg_users[] = "Users:";
    
    LCD4_clear();
    LCD4_str(msg_users);
    LCD4_newline();
    
    for (uint8_t i = 0; i < MAX_USERS; i++) {
        if (Keypad_GetKey() == '5') return;  // ???? ??? ??? ???????? 5
        
        char userID = EEPROM_read(EEPROM_START_ADDR + (i * 2));
        if (userID != 0xFF) {  
            itoa(userID, buffer, 10);
            LCD4_str(buffer);
            LCD4_newline();
        }
    }
    _delay_ms(2000);
}
