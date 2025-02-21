/* 
 * File:   loginsystem.h
 * Author: safe
 *
 * Created on February 3, 2025, 5:43 PM
 */
#ifndef LOGINSYSTEM_H
#define	LOGINSYSTEM_H

#include <stdint.h>
#include <avr/eeprom.h>

#define EEPROM_START_ADDR 0x00
#define MAX_USERS 5

void System_Welcome(void);
void Display_Users(void);
void Add_User(int userID, char password);
void Delete_User(int userID);
void Add_User_From_Keypad(void);
void Delete_User_From_Keypad(void);
void Display_Menu(void);

#endif /* LOGINSYSTEM_H */
