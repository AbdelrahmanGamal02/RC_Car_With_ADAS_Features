/* 
 * File:   Ultarsonic_Sensor.c
 * Author: win 10-11
 *
 * Created on 24 ??????, 2024, 08:06 ?
 */

#include "Ultarsonic_Sensor.h"

void ULTRASONIC_Init(void)
{
    GPIO_PinDirection(ULTRASONIC_TRIGGER_PORT , ULTRASONIC_TRIGGER_PIN , GPIO_PIN_DIRECTION_OUTPUT);
}

uint16 ULTRASONIC_GeTValue(void)
{
    uint16 a,b,high,distance;
    TCCR1A = 0;
	TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag)  */
    GPIO_PinWriteLogic(ULTRASONIC_TRIGGER_PORT ,ULTRASONIC_TRIGGER_PIN, GPIO_LOGIC_HIGH); 
	_delay_us(50);
    GPIO_PinWriteLogic(ULTRASONIC_TRIGGER_PORT ,ULTRASONIC_TRIGGER_PIN, GPIO_LOGIC_LOW);
	
	TCCR1B = 0xc1;  	/* Rising edge, no pre-scaler , noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	a = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	TCCR1B = 0x81;  	/* Falling edge, no pre-scaler ,noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	b = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
    TCNT1=0;
	TCCR1B = 0;  		/* Stop the timer */
    high=b-a;
	distance=((high*34600)/(F_CPU*2));
        
    return distance;
}