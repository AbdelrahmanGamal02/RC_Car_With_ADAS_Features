/* 
 * File:   Ultarsonic_Sensor.h
 * Author: win 10-11
 *
 * Created on 24 ??????, 2024, 08:06 ?
 */

#ifndef ULTARSONIC_SENSOR_H
#define	ULTARSONIC_SENSOR_H

/*********** Includes ******************/
#include <util/delay.h>
#include "../../MC_Abstraction_Layer/GPIO/GPIO.h"
/***************************************/
/************* Macros ******************/
#define ULTRASONIC_TRIGGER_PORT     PORTD_INDEX
#define ULTRASONIC_TRIGGER_PIN      GPIO_PIN2
/***************************************/
/************** APIs *****************/
void ULTRASONIC_Init(void);
uint16 ULTRASONIC_GeTValue(void);
/***************************************/

#endif	/* ULTARSONIC_SENSOR_H */

