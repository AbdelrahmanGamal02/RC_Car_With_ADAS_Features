/*
 * DC_Motor.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#ifndef ECUAL_LAYER_DC_MOTOR_DC_MOTOR_H_
#define ECUAL_LAYER_DC_MOTOR_DC_MOTOR_H_

/**************** Includes ********************/
#include "../../MC_Abstraction_Layer/GPIO/GPIO.h"
#include "../../MC_Abstraction_Layer/PWM_Timer0/PWM_Timer0.h"
/********************************************/
/*************** Macros ******************/
/********************************************/
/**************** Data Types ****************/
typedef enum
{
	DC_MOTOR_STOP = 0,
	DC_MOTOR_ROTATE_CLOCKWISE,
	DC_MOTOR_ROTATE_ANTICLOCKWISE
}DCMotor_State;

/********************************************/

/***************** APIs **********************/
void DC_Motor_Init(uint8 DC_MOTOR_PORT , uint8 DC_MOTOR_PIN1 , uint8 DC_MOTOR_PIN2);

void DC_Motor_Rotate(uint8 DC_MOTOR_PORT , uint8 DC_MOTOR_PIN1 , uint8 DC_MOTOR_PIN2, DCMotor_State State);
/********************************************/
#endif /* ECUAL_LAYER_DC_MOTOR_DC_MOTOR_H_ */
