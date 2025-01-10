/*
 * DC_Motor.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
*/

#include "DC_Motor.h"

void DC_Motor_Init(uint8 DC_MOTOR_PORT , uint8 DC_MOTOR_PIN1 , uint8 DC_MOTOR_PIN2)
{
	GPIO_PinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_PIN_DIRECTION_OUTPUT);

	GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_LOW);
	GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_LOW);
}

void DC_Motor_Rotate(uint8 DC_MOTOR_PORT , uint8 DC_MOTOR_PIN1 , uint8 DC_MOTOR_PIN2, DCMotor_State State)
{
	if(DC_MOTOR_ROTATE_CLOCKWISE == State)
	{
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_HIGH);
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_LOW);

	}
	else if(DC_MOTOR_ROTATE_ANTICLOCKWISE == State)
	{
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_LOW);
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_HIGH);

	}
	else if(DC_MOTOR_STOP == State)
	{
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN1 , GPIO_LOGIC_LOW);
		GPIO_PinWriteLogic(DC_MOTOR_PORT , DC_MOTOR_PIN2 , GPIO_LOGIC_LOW);

	}
	else { /* Nothing */ }

}
