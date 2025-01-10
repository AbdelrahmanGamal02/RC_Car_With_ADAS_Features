/* 
 * File:   main.h
 * Author: win 10-11
 *
 * Created on 24 ??????, 2024, 02:24 ?
 */

#ifndef MAIN_H
#define	MAIN_H

/*********** Includes ******************/
#include "ECUAL_Layer/DC_Motor/DC_Motor.h"
#include "ECUAL_Layer/Ultarsonic_Sensor/Ultarsonic_Sensor.h"
#include "MC_Abstraction_Layer/UART/UART.h"
#include "MC_Abstraction_Layer/SPI/SPI.h"
/************************************************/
/********************** Macros ********************/
// MOTORs PORT , PINS
#define MOTORS_PORT                 PORTC_INDEX

#define FRONT_LEFT_MOTOR_PIN1       GPIO_PIN0
#define FRONT_LEFT_MOTOR_PIN2       GPIO_PIN1

#define BACK_LEFT_MOTOR_PIN1        GPIO_PIN2
#define BACK_LEFT_MOTOR_PIN2        GPIO_PIN3

#define FRONT_RIGHT_MOTOR_PIN1      GPIO_PIN4
#define FRONT_RIGHT_MOTOR_PIN2      GPIO_PIN5

#define BACK_RIGHT_MOTOR_PIN1       GPIO_PIN6
#define BACK_RIGHT_MOTOR_PIN2       GPIO_PIN7

#define STOP_MOTOR                  0x00

// LEDs PORT , PINS
#define LEDS_PORT                 PORTA_INDEX

#define LEFT_RED_LED                GPIO_PIN0
#define LEFT_YELLOW_LED             GPIO_PIN1

#define RIGHT_YELLOW_LED            GPIO_PIN2
#define RIGHT_RED_LED               GPIO_PIN3

// PIR SENSOR PORT , PINS
#define PIR_SENSOR_PORT             PORTA_INDEX

#define LEFT_PIR_SENSOR_PIN         GPIO_PIN4
#define RIGHT_PIR_SENSOR_PIN        GPIO_PIN5

// BUZZER PORT , PINS
#define BUZZER_PORT                 PORTB_INDEX
#define BUZZER_PIN                  GPIO_PIN0

// BUTTONs PORT , PINS
#define CONTACT_BUTTON_PORT                 PORTB_INDEX
#define ADAPTIVE_CRUISE_CONTROL_BUTTON_PORT PORTB_INDEX

#define CRUISE_CONTROL_BUTTON_PORT          PORTD_INDEX
#define SPEED_BUTTON_PORT                   PORTD_INDEX

#define CONTACT_BUTTON_PIN                 GPIO_PIN1
#define ADAPTIVE_CRUISE_CONTROL_BUTTON_PIN GPIO_PIN2

#define CRUISE_CONTROL_BUTTON_PIN          GPIO_PIN3
#define SPEED_BUTTON_PIN                   GPIO_PIN2
/************************************************/
/********************** APIs ********************/
void Application_Init(void);
void Application_Interrupt_Init(void);
/************************************************/
#endif	/* MAIN_H */

