/*
 * File:   main.c
 * Author: win 10-11
 *
 * Created on 24 ??????, 2024, 02:23 ?
 */

#include "main.h"


volatile uint8 PWM_counter_1 = 1;
volatile uint8 cruise_control_flag = 0;
uint16 Front_Ultrasonic_Value = 0;
uint16 Back_Ultrasonic_Value = 0;
uint8 Back_Ultrasonic_Value_1 ,Back_Ultrasonic_Value_2;
uint8 dute_cycle = 0;

ISR(INT0_vect)
{
    if(PWM_counter_1 < 10)
	{
		PWM_counter_1++;
	}
}

ISR(INT1_vect)
{
    /* cruise control */
    cruise_control_flag = 1;
    /* Close the interrupt that responsible for increasing the speed */
    CLEAR_BIT(GICR , INT0);   
}

ISR(INT2_vect)
{
    if(1 == cruise_control_flag)
    {
        /* close the cruise control */
        SET_BIT(GICR , INT0);
        cruise_control_flag = 0;
    }
    
    if(PWM_counter_1 >= 1)
	{
		PWM_counter_1--;
	}
}

void main(void) {
    
    Application_Init();
    Application_Interrupt_Init();
    
    while(1)
    {
        if(BIT_IS_SET(PINB , GPIO_PIN1))
        {
            GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
            SPI_ui8TransmitRecive('W');
            GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
            _delay_ms(500);
            GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
            Back_Ultrasonic_Value_1 = SPI_ui8TransmitRecive(0xFF);
            Back_Ultrasonic_Value_2 = SPI_ui8TransmitRecive(0xFF);
            GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
            
            dute_cycle = (uint8)(PWM_counter_1 * 10);
            Back_Ultrasonic_Value = (uint16)((Back_Ultrasonic_Value_1 << 8) + Back_Ultrasonic_Value_2);
            switch(received_value)
            {
                case 'F':
                {
                    DC_Motor_Rotate(MOTORS_PORT , FRONT_LEFT_MOTOR_PIN1,FRONT_LEFT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , BACK_LEFT_MOTOR_PIN1,BACK_LEFT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , FRONT_RIGHT_MOTOR_PIN1,FRONT_RIGHT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , BACK_RIGHT_MOTOR_PIN1,BACK_RIGHT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    PWM_Timer2_Start(dute_cycle);
                    PWM_Timer0_Start(dute_cycle);
                    /* Send Data to the LCD */
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive('F');
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive(dute_cycle);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    
                }
                break;
                
                case 'R':
                {
                    
                    /* TO MOVE right left motors on and right motors off */
                    DC_Motor_Rotate(MOTORS_PORT , FRONT_LEFT_MOTOR_PIN1,FRONT_LEFT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , BACK_LEFT_MOTOR_PIN1,BACK_LEFT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    PWM_Timer2_Start(dute_cycle);
                    
                    PWM_Timer0_Stop();
                    
                    /* Send Data to the LCD */
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive('R');
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive(dute_cycle);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(LEDS_PORT, RIGHT_YELLOW_LED , GPIO_LOGIC_HIGH);
                    _delay_ms(100);
                    GPIO_PinWriteLogic(LEDS_PORT, RIGHT_YELLOW_LED , GPIO_LOGIC_LOW);
                }
                break;
                
                case 'L':
                {
                    
                    /* TO MOVE left right motors on and left motors off */
                    DC_Motor_Rotate(MOTORS_PORT , FRONT_RIGHT_MOTOR_PIN1,FRONT_RIGHT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , BACK_RIGHT_MOTOR_PIN1,BACK_RIGHT_MOTOR_PIN2,DC_MOTOR_ROTATE_CLOCKWISE);
                    PWM_Timer0_Start(dute_cycle);
                    
                    PWM_Timer2_Stop();
                    /* Send Data to the LCD */
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive('L');
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive(dute_cycle);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(LEDS_PORT, LEFT_YELLOW_LED , GPIO_LOGIC_HIGH);
                    _delay_ms(100);
                    GPIO_PinWriteLogic(LEDS_PORT, LEFT_YELLOW_LED , GPIO_LOGIC_LOW);
                }
                break;
                
                case 'B':
                {
                    DC_Motor_Rotate(MOTORS_PORT , FRONT_LEFT_MOTOR_PIN1,FRONT_LEFT_MOTOR_PIN2,DC_MOTOR_ROTATE_ANTICLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , BACK_LEFT_MOTOR_PIN1,BACK_LEFT_MOTOR_PIN2,DC_MOTOR_ROTATE_ANTICLOCKWISE);
                    DC_Motor_Rotate(MOTORS_PORT , FRONT_RIGHT_MOTOR_PIN1,FRONT_RIGHT_MOTOR_PIN2,DC_MOTOR_ROTATE_ANTICLOCKWISE);
                    PWM_Timer2_Start(dute_cycle);
                    DC_Motor_Rotate(MOTORS_PORT , BACK_RIGHT_MOTOR_PIN1,BACK_RIGHT_MOTOR_PIN2,DC_MOTOR_ROTATE_ANTICLOCKWISE);
                    PWM_Timer0_Start(dute_cycle);
                    
                    /* Send Data to the LCD */
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive('B');
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive(dute_cycle);
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    
                    GPIO_PinWriteLogic(LEDS_PORT, LEFT_RED_LED , GPIO_LOGIC_HIGH);
                    GPIO_PinWriteLogic(LEDS_PORT, RIGHT_RED_LED , GPIO_LOGIC_HIGH);
                    _delay_ms(100);
                    GPIO_PinWriteLogic(LEDS_PORT, RIGHT_RED_LED , GPIO_LOGIC_LOW);
                    GPIO_PinWriteLogic(LEDS_PORT, LEFT_RED_LED , GPIO_LOGIC_LOW);
                }
                break; 
            }
            
            if(BIT_IS_SET(PINA , GPIO_PIN4))
            {
                /* send data as there is an object in the left of the car (blind spot) */
                GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                SPI_ui8TransmitRecive('A');
                GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);  
            }
            
            if(BIT_IS_SET(PINA , GPIO_PIN5))
            {
                /* send data as there is an object in the right of the car (blind spot) */
                GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                SPI_ui8TransmitRecive('C');
                GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);  
            }
            
            _delay_ms(300);
            Front_Ultrasonic_Value = ULTRASONIC_GeTValue();
            
            /* if the distance of the car and any object 10cm fire an alarm to warm the user */
            if(Front_Ultrasonic_Value <= 10 || Back_Ultrasonic_Value <= 10)
            {
                GPIO_PinWriteLogic(BUZZER_PORT , BUZZER_PIN ,GPIO_LOGIC_HIGH);
            }
            else
            {
                GPIO_PinWriteLogic(BUZZER_PORT , BUZZER_PIN ,GPIO_LOGIC_LOW);
            }
            
            /* check if adaptive cruise control or not */
            if(BIT_IS_SET(PINA , GPIO_PIN7))
            {
                if(Front_Ultrasonic_Value <= 30 && Front_Ultrasonic_Value > 10)
                {
                    /* warming the user using dash board */
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive('X');
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                    /* Decrease Speed */
                    if(PWM_counter_1 > 5)
                    {
                        PWM_counter_1--;
                    }
                }
                
                if(Front_Ultrasonic_Value <= 10)
                {
                    /* Stop the Car */
                    PWM_counter_1 = 0;
                    /* inform the user */
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
                    SPI_ui8TransmitRecive('Z');
                    GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
                }
            }
                             
        }
        else
        {
            /* Contact switch hasn't been pressed */
            /* Stop every thing */
            DC_Motor_Rotate(MOTORS_PORT , FRONT_LEFT_MOTOR_PIN1,FRONT_LEFT_MOTOR_PIN2,DC_MOTOR_STOP);
            DC_Motor_Rotate(MOTORS_PORT , BACK_LEFT_MOTOR_PIN1,BACK_LEFT_MOTOR_PIN2,DC_MOTOR_STOP);
            DC_Motor_Rotate(MOTORS_PORT , FRONT_RIGHT_MOTOR_PIN1,FRONT_RIGHT_MOTOR_PIN2,DC_MOTOR_STOP);
            DC_Motor_Rotate(MOTORS_PORT , BACK_RIGHT_MOTOR_PIN1,BACK_RIGHT_MOTOR_PIN2,DC_MOTOR_STOP);
            
            PWM_Timer0_Stop();
            PWM_Timer2_Stop();
            
            /* Send data to another microcontroller to stop any thing */
            GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_LOW);
            SPI_ui8TransmitRecive('O');
            GPIO_PinWriteLogic(PORTB_INDEX, SPI_SS , GPIO_LOGIC_HIGH);
        }
        
    }
}
void Application_Init(void)
{
    /* UART Initialization */
    UART_Init();
    /* SPI Initialization */
    SPI_vInitMaster();
    /* Motor Initialization */
    DC_Motor_Init(MOTORS_PORT , FRONT_LEFT_MOTOR_PIN1,FRONT_LEFT_MOTOR_PIN2);
    DC_Motor_Init(MOTORS_PORT , BACK_LEFT_MOTOR_PIN1,BACK_LEFT_MOTOR_PIN2);
    DC_Motor_Init(MOTORS_PORT , FRONT_RIGHT_MOTOR_PIN1,FRONT_RIGHT_MOTOR_PIN2);
    DC_Motor_Init(MOTORS_PORT , BACK_RIGHT_MOTOR_PIN1,BACK_RIGHT_MOTOR_PIN2);
    /* LED Initialization */
    GPIO_PinDirection(LEDS_PORT , LEFT_RED_LED , GPIO_PIN_DIRECTION_OUTPUT);
    GPIO_PinDirection(LEDS_PORT , LEFT_YELLOW_LED , GPIO_PIN_DIRECTION_OUTPUT);
    GPIO_PinDirection(LEDS_PORT , RIGHT_YELLOW_LED , GPIO_PIN_DIRECTION_OUTPUT);
    GPIO_PinDirection(LEDS_PORT , RIGHT_RED_LED , GPIO_PIN_DIRECTION_OUTPUT);
    /* PIR SENSOR Initialization*/
    GPIO_PinDirection(PIR_SENSOR_PORT , LEFT_PIR_SENSOR_PIN , GPIO_PIN_DIRECTION_INPUT);
    GPIO_PinDirection(PIR_SENSOR_PORT , RIGHT_PIR_SENSOR_PIN , GPIO_PIN_DIRECTION_INPUT);
    /* BUZZER Initialization */
    GPIO_PinDirection(BUZZER_PORT , BUZZER_PIN , GPIO_PIN_DIRECTION_OUTPUT);
    /* BUTTON Initialization */
    GPIO_PinDirection(CONTACT_BUTTON_PORT , CONTACT_BUTTON_PIN , GPIO_PIN_DIRECTION_INPUT);
    GPIO_PinDirection(ADAPTIVE_CRUISE_CONTROL_BUTTON_PORT , ADAPTIVE_CRUISE_CONTROL_BUTTON_PIN , GPIO_PIN_DIRECTION_INPUT);
    GPIO_PinDirection(CRUISE_CONTROL_BUTTON_PORT , CRUISE_CONTROL_BUTTON_PIN , GPIO_PIN_DIRECTION_INPUT);
    GPIO_PinDirection(SPEED_BUTTON_PORT , SPEED_BUTTON_PIN , GPIO_PIN_DIRECTION_INPUT);
    /* Ultrasonic Sensor Initialization */
    ULTRASONIC_Init();
}

void Application_Interrupt_Init(void)
{
    SREG |= (1<<7); // enable global interrupt (SREG |= (1<<7))
    GICR |= (1 << INT1) | (1 << INT0) | (1 << INT2);  // Enable External Interrupt
    MCUCR |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11); // Interrupt on rising edge on INT0 , INT1
    MCUCSR |= (1 << ISC2);// Interrupt on rising edge ON INT2
}