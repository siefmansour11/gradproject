#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include "DIO.h"
#include "Bluetooth.h"
#include "EEPROM.h"
#include "LCD4.h"
#include "SERVO.h"
#include "TempANDmotor.h"
#include "buttons.h"
#include "buzzer.h"
#include "keypad.h"
#include "led.h"
#include "loginsystem.h"
#include "relay.h"
#include "mUART.h"
#include "fanrelay.h"
#include "motor.h"

#define CODE_LENGTH 4  

int motorState = 0; 
int failedAttempts = 0;
int buzzerActive = 0;
extern int isAdmin;  
int lastFlameStatus = 0; 

int main(void) {
    init_BTNS();
    init_LEDs();
    init_LCD4();
    Keypad_init();
    init_Relay();
    init_Buzzer();
    init_fanrelay();
    Servo_init();
    FlameSensor_init();
    Motor_Init();
    init_UART(9600); 
    
    System_Welcome(); 
    
   
    char key;
    char enteredCode[CODE_LENGTH + 1] = "";  
    uint8_t index = 0;  

    char msg_ready[] = "Keypad Ready";
    char msg_access[] = "Access Granted!";
    char msg_wrong[] = "Wrong Code!";
    char msg_enter[] = "Enter Code:";
    char msg_fan_on[] = "Fan ON";
    char msg_fan_off[] = "Fan OFF";
    char msg_servo_on[] = "Servo ON";
    char msg_servo_off[] = "Servo OFF";
    char msg_motor_on[] = "Motor ON";
    char msg_motor_off[] = "Motor OFF";
    char msg_only_admin[] = "Only Admin";
    char msg0[] = "LED0 ON";
    char msg1[] = "LED1 ON";
    char msg2[] = "LED2 ON";
    char msg3[] = "LED3 ON";
    char msg4[] = "LED4 ON";
    char msg_reset[] = "All Reset";
    char msg_fire_alarm[] = "fire alarm";
    
char msg_bt_ready[] = "BT Ready";
char msgbt_led0_on[] = "LED0 ON BT";
char msgbt_led0_off[] = "LED0 OFF BT";
char msgbt_led1_on[] = "LED1 ON BT";
char msgbt_led1_off[] = "LED1 OFF BT";
char msgbt_led2_on[] = "LED2 ON BT";
char msgbt_led2_off[] = "LED2 OFF BT";
char msgbt_led3_on[] = "LED3 ON BT";
char msgbt_led3_off[] = "LED3 OFF BT";
char msgbt_led4_on[] = "LED4 ON BT";
char msgbt_led4_off[] = "LED4 OFF BT";
char msgbt_motor_on[] = "Motor ON BT";
char msgbt_motor_off[] = "Motor OFF BT";
char msgbt_servo_on[] = "Servo ON BT";
char msgbt_servo_off[] = "Servo OFF BT";
char msgbt_relay_on[] = "Relay ON BT";
char msgbt_relay_off[] = "Relay OFF BT";
char msgbt_fan_on[] = "Fan ON BT";
char msgbt_fan_off[] = "Fan OFF BT";
char msg_invalid[] = "Invalid Cmd";

LCD4_clear();
    LCD4_str(msg_bt_ready);
    _delay_ms(1000);

    char command;

    LCD4_clear();
    LCD4_str(msg_ready);
    _delay_ms(1000);

    LEDs_OFF();
    LCD4_clear();
    LCD4_str(msg_enter);

    while (1) {
        if (UART_Available()) {  
    command = UART_receive();  
} else {
    command = '\0';  
}
if (command != '\0') {

        switch (command) {
              case '#':  
            LCD4_clear();  
            Display_Menu();
            break;
            case '0':
                LED_ON(LED0_ID);
                LCD4_clear();
                LCD4_str(msgbt_led0_on);
                break;
            case '1':
                LED_OFF(LED0_ID);
                LCD4_clear();
                LCD4_str(msgbt_led0_off);
                break;
            case '2':
                LED_ON(LED1_ID);
                LCD4_clear();
                LCD4_str(msgbt_led1_on);
                break;
            case '3':
                LED_OFF(LED1_ID);
                LCD4_clear();
                LCD4_str(msgbt_led1_off);
                break;
            case '4':
                LED_ON(LED2_ID);
                LCD4_clear();
                LCD4_str(msgbt_led2_on);
                break;
            case '5':
                LED_OFF(LED2_ID);
                LCD4_clear();
                LCD4_str(msgbt_led2_off);
                break;
            case '6':
                LED_ON(LED3_ID);
                LCD4_clear();
                LCD4_str(msgbt_led3_on);
                break;
            case '7':
                LED_OFF(LED3_ID);
                LCD4_clear();
                LCD4_str(msgbt_led3_off);
                break;
            case '8':
                LED_ON(LED4_ID);
                LCD4_clear();
                LCD4_str(msgbt_led4_on);
                break;
            case '9':
                LED_OFF(LED4_ID);
                LCD4_clear();
                LCD4_str(msgbt_led4_off);
                break;
            case 'M':
                Motor_On();
                LCD4_clear();
                LCD4_str(msgbt_motor_on);
                break;
            case 'm':
                Motor_Off();
                LCD4_clear();
                LCD4_str(msgbt_motor_off);
                break;
            case 'S':
                Servo_OpenDoor();
                LCD4_clear();
                LCD4_str(msgbt_servo_on);
                break;
            case 's':
                Servo_CloseDoor();
                LCD4_clear();
                LCD4_str(msgbt_servo_off);
                break;
            case 'R':
                Relay_ON();
                LCD4_clear();
                LCD4_str(msgbt_relay_on);
                break;
            case 'r':
                Relay_OFF();
                LCD4_clear();
                LCD4_str(msgbt_relay_off);
                break;
            case 'F':
                fanrelay_ON();
                LCD4_clear();
                LCD4_str(msgbt_fan_on);
                break;
            case 'f':
                fanrelay_OFF();
                LCD4_clear();
                LCD4_str(msgbt_fan_off);
                break;
            default:
                LCD4_clear();
                LCD4_str(msg_invalid);
                break;
        }
        _delay_ms(500);
}
        
        key = Keypad_GetKey();

        if (key) {
            if (index < CODE_LENGTH) {
        enteredCode[index] = key;  
        LCD4_write('*');  
        index++;  
    }

            if (index == CODE_LENGTH) {
                enteredCode[index] = '\0';  
                LCD4_clear();
                if (strncmp(enteredCode, "1111", CODE_LENGTH) == 0) {  
                    LCD4_str(msg_access);
                    Relay_ON();  
                    _delay_ms(2000);
                    Relay_OFF(); 
                    failedAttempts = 0;
                } else if (strncmp(enteredCode, "1973", CODE_LENGTH) == 0) {  
                    LCD4_str(msg_fan_on);
                    fanrelay_ON();  
                } else if (strncmp(enteredCode, "0000", CODE_LENGTH) == 0) {  
                    LCD4_str(msg_fan_off);
                    fanrelay_OFF();  
                } else if (strncmp(enteredCode, "1978", CODE_LENGTH) == 0) {  
                    if (isAdmin) {
                        LCD4_str(msg_servo_on);
                        Servo_OpenDoor();  
                    } else {
                        LCD4_str(msg_only_admin);
                    }
                } else if (strncmp(enteredCode, "1234", CODE_LENGTH) == 0) {  
                    if (isAdmin) {
                        LCD4_str(msg_servo_off);
                        Servo_CloseDoor();  
                    } else {
                        LCD4_str(msg_only_admin);
                    }
                } else if (strncmp(enteredCode, "2004", CODE_LENGTH) == 0) {  
                    motorState = 1;
                    LCD4_str(msg_motor_on);
                    Motor_On();
                } else if (strncmp(enteredCode, "2000", CODE_LENGTH) == 0) {  
                    motorState = 0;
                    LCD4_str(msg_motor_off);
                    Motor_Off();
                    _delay_ms(500); 
                } else if (strncmp(enteredCode, "2222", CODE_LENGTH) == 0) {  
                    buzzerActive = 0;
                    Buzzer_OFF();
                    LCD4_clear();
                    LCD4_str(msg_reset);
                    _delay_ms(2000);
                    LCD4_clear();
                    LCD4_str(msg_enter);
                    failedAttempts = 0;
                } else {
                    LCD4_str(msg_wrong);
                    _delay_ms(2000);
                    failedAttempts++;
                }
                
                if (failedAttempts >= 3 && buzzerActive == 0) {
                    buzzerActive = 1;
                }
                
                index = 0;  
                _delay_ms(1000);
                LCD4_clear();
                LCD4_str(msg_enter);
            }
            while (Keypad_GetKey() == key);  
        }
        
        if (buzzerActive) {
            Buzzer_PlayTone();
        }

        if (motorState) {
            Motor_On();
        } else {
            Motor_Off();
        }
int flameStatus = FlameSensor_Read();
    
    if (flameStatus && !lastFlameStatus) { 
        LCD4_clear();
        LCD4_str(msg_fire_alarm);
        Buzzer_PlayTone();
        fanrelay_ON();
        _delay_ms(6000);
        Buzzer_OFF();
        fanrelay_OFF();
        LCD4_clear();
        LCD4_str(msg_enter);
    }
    
    lastFlameStatus = flameStatus;
        

        if (BTNs_isPressed(BTN0)) {
            LED_ON(LED0_ID);
            LCD4_clear();
            LCD4_str(msg0);
        } else {
            LED_OFF(LED0_ID);
        }

        if (BTNs_isPressed(BTN1)) {
            LED_ON(LED1_ID);
            LCD4_clear();
            LCD4_str(msg1);
        } else {
            LED_OFF(LED1_ID);
        }

        if (BTNs_isPressed(BTN2)) {
            LED_ON(LED2_ID);
            LCD4_clear();
            LCD4_str(msg2);
        } else {
            LED_OFF(LED2_ID);
        }

        if (BTNs_isPressed(BTN3)) {
            LED_ON(LED3_ID);
            LCD4_clear();
            LCD4_str(msg3);
        } else {
            LED_OFF(LED3_ID);
        }

        if (BTNs_isPressed(BTN4)) {
            LED_ON(LED4_ID);
            LCD4_clear();
            LCD4_str(msg4);
        } else {
            LED_OFF(LED4_ID);
        }
    }

    return 0;
}
