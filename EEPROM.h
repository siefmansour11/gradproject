/* 
 * File:   EEPROM.h
 * Author: safe
 *
 * Created on February 1, 2025, 6:08 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H


void EEPROM_write(int address, char data);
char EEPROM_read(int address);
void Store_User(int index, char userID, char password);
void Retrieve_Users(void);
#endif	/* EEPROM_H */

