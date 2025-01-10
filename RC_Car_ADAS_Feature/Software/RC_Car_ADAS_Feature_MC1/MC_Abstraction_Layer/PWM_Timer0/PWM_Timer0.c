/*
 * PWM_Timer0.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: win 10-11
 */

#include "PWM_Timer0.h"

void PWM_Timer0_Start(uint8 Set_duty_cycle)
{
	TCNT0 = 0;

	OCR0 = (uint8)((Set_duty_cycle * 255) / 100);

	GPIO_PinDirection(PORTB_INDEX , GPIO_PIN3 , GPIO_PIN_DIRECTION_OUTPUT);

	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}

void PWM_Timer0_Stop(void)
{
	/* write 0 on WGM00 and WGM01 to return to normal mode */
	CLEAR_BIT(TCCR0 , 6);
	CLEAR_BIT(TCCR0 , 3);
}

void PWM_Timer1_Start(uint8 Set_duty_cycle_OC1A , uint8 Set_duty_cycle_OC1B)
{
    TCNT1 = 0;

	OCR1A = (uint8)((Set_duty_cycle_OC1A * 255) / 100);
    OCR1B = (uint8)((Set_duty_cycle_OC1B * 255) / 100);

	GPIO_PinDirection(PORTD_INDEX , GPIO_PIN5 , GPIO_PIN_DIRECTION_OUTPUT);
    GPIO_PinDirection(PORTD_INDEX , GPIO_PIN4 , GPIO_PIN_DIRECTION_OUTPUT);

    /* non inverting , 8bit fast PWM mode with pre-scaler  F_CPU / 8 */
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << WGM12)  | (1 << CS11);
    
}

void PWM_Timer1_Stop(void)
{
    /* write 0 on WGM10 and WGM12 to return to normal mode */
	CLEAR_BIT(TCCR1A , WGM10);
	CLEAR_BIT(TCCR1B , WGM12);
}

void PWM_Timer2_Start(uint8 Set_duty_cycle)
{
	TCNT2 = 0;

	OCR2 = (uint8)((Set_duty_cycle * 255) / 100);

	GPIO_PinDirection(PORTD_INDEX , GPIO_PIN7 , GPIO_PIN_DIRECTION_OUTPUT);

	TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS21);    
}

void PWM_Timer2_Stop(void)
{
    /* write 0 on WGM20 and WGM21 to return to normal mode */
    CLEAR_BIT(TCCR2 , 6);
	CLEAR_BIT(TCCR2 , 3);
}