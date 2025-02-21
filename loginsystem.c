#include "loginsystem.h"
#include "LCD4.h"
#include "keypad.h"
#include "EEPROM.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define EEPROM_START_ADDR 0x00

int isAdmin = 0;

void System_Welcome(void) {
    char key;
    char msg1[] = "Enter 1 or 0:";
    char msg_admin[] = "Hello Admin";
    char msg_user[] = "Welcome User";
    char msg_invalid[] = "Invalid Input";

    while (1) {
        LCD4_clear();
        LCD4_str(msg1);

        key = '\0';
        while (key == '\0') {
            key = Keypad_GetKey();
        }

        LCD4_clear();

        if (key == '1') {
            isAdmin = 1;
            LCD4_str(msg_admin);
            _delay_ms(2000);
            break;
        } else if (key == '0') {
            isAdmin = 0;
            LCD4_str(msg_user);
            _delay_ms(2000);
            break;
        } else {
            LCD4_str(msg_invalid);
            _delay_ms(2000);
        }
    }
}

void Display_Menu(void) {
    LCD4_clear();
    char menu1[] = "1:Add 2:Delete";
    char menu2[] = "3:Show Users 4:Exit";
    LCD4_str(menu1);
    LCD4_newline();
    LCD4_str(menu2);
}

void Display_Users(void) {
    char userID;
    char buffer[3];
    uint8_t foundUsers = 0;
    char msg_users[] = "Users:";
    char msg_no_users[] = "No Users Found";
    char msg_total[] = "Total: ";
    char total_buffer[3];
    uint8_t total_users = 0;

    LCD4_clear();
    LCD4_str(msg_users);
    LCD4_newline();
    _delay_ms(500);

    for (uint8_t i = 0; i < MAX_USERS; i++) {
        userID = EEPROM_read(EEPROM_START_ADDR + (i * 2));
        if (userID != 0xFF) {
            itoa(userID, buffer, 10);
            LCD4_str(buffer);
            LCD4_newline();
            _delay_ms(500);
            foundUsers = 1;
            total_users++;
        }
    }

    if (!foundUsers) {
        LCD4_str(msg_no_users);
    } else {
        LCD4_str(msg_total);
        itoa(total_users, total_buffer, 10);
        LCD4_str(total_buffer);
    }
    _delay_ms(2000);
}

void Add_User_From_Keypad(void) {
    char userID, password;
    char buffer[3];
    uint8_t userCount = 0;
    char msg_max_users[] = "Max Users Reached";
    char msg_enter_id[] = "Enter User ID:";
    char msg_user_exists[] = "User Exists!";
    char msg_enter_pass[] = "Enter Password:";

    for (uint8_t i = 0; i < MAX_USERS; i++) {
        if (EEPROM_read(EEPROM_START_ADDR + (i * 2)) != 0xFF) {
            userCount++;
        }
    }

    if (userCount >= MAX_USERS) {
        LCD4_clear();
        LCD4_str(msg_max_users);
        _delay_ms(2000);
        return;
    }

    LCD4_clear();
    LCD4_str(msg_enter_id);
    while ((userID = Keypad_GetKey()) < '0' || userID > '9');
    itoa(userID - '0', buffer, 10);
    LCD4_str(buffer);
    _delay_ms(500);

    for (uint8_t i = 0; i < MAX_USERS; i++) {
        if (EEPROM_read(EEPROM_START_ADDR + (i * 2)) == (userID - '0')) {
            LCD4_clear();
            LCD4_str(msg_user_exists);
            _delay_ms(2000);
            return;
        }
    }

    LCD4_clear();
    LCD4_str(msg_enter_pass);
    while ((password = Keypad_GetKey()) < '0' || password > '9');
    itoa(password - '0', buffer, 10);
    LCD4_str(buffer);
    _delay_ms(500);

    Add_User(userID - '0', password - '0');
    Display_Menu();
}

void Delete_User_From_Keypad(void) {
    char userID;
    char buffer[3];
    char msg_only_admin[] = "Only Admin";
    char msg_enter_id[] = "Enter User ID:";
    char msg_deleted[] = "User Deleted";

    if (!isAdmin) {
        LCD4_clear();
        LCD4_str(msg_only_admin);
        _delay_ms(2000);
        return;
    }

    LCD4_clear();
    LCD4_str(msg_enter_id);
    while ((userID = Keypad_GetKey()) < '0' || userID > '9');
    itoa(userID - '0', buffer, 10);
    LCD4_str(buffer);
    _delay_ms(500);

    Delete_User(userID - '0');
    LCD4_clear();
    LCD4_str(msg_deleted);
    _delay_ms(2000);
    Display_Menu();
}

void Add_User(int userID, char password) {
    if (userID >= MAX_USERS) {
        return;
    }
    EEPROM_write(EEPROM_START_ADDR + (userID * 2), userID);
    EEPROM_write(EEPROM_START_ADDR + (userID * 2) + 1, password);
}

void Delete_User(int userID) {
    EEPROM_write(EEPROM_START_ADDR + (userID * 2), 0xFF);
    EEPROM_write(EEPROM_START_ADDR + (userID * 2) + 1, 0xFF);
}
