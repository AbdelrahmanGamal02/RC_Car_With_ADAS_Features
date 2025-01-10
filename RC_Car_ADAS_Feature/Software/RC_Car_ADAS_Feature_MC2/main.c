/*
 * File:   main.c
 * Author: win 10-11
 *
 * Created on 30 ??????, 2024, 01:37 ?
 */


#include <xc.h>
#include "main.h"

uint8 past_spi_received_value = 0;
uint8 spi_received_value = 0;
uint8 Motor_Speed = 0;
uint8 Ultrasonic_Value = 0;
uint8 Temp_string_1[6] = {0};
uint8 Temp_string_2[6] = {0};
uint8 Temp_string_3[6] = {0};
uint8 Temp_string_4[6] = {0};

void main(void) 
{
    /* Initialize application component */
    Application_Init();

    while(1)
    {
        spi_received_value = SPI_ui8TransmitRecive(DUMY_DATA);
        switch(spi_received_value)
        {
            case 'F':
            {
                Motor_Speed = SPI_ui8TransmitRecive(DUMY_DATA);
                LCD_clearscreen();
                LCD_Convert_uint8_to_string(Motor_Speed , Temp_string_1);
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("CAR Direction: Front");
                
                LCD_movecursor(2 ,1); 
                LCD_vSend_string("Motor Speed:");
                LCD_movecursor(2 ,15); 
                LCD_vSend_string(Temp_string_1);
                
            }
            break;
            
            case 'R':
            {
                Motor_Speed = SPI_ui8TransmitRecive(DUMY_DATA);
                LCD_clearscreen();
                LCD_Convert_uint8_to_string(Motor_Speed , Temp_string_2);
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("CAR Direction: Right");
                LCD_movecursor(2 ,1); 
                LCD_vSend_string("Motor Speed:");
                LCD_movecursor(2 ,15); 
                LCD_vSend_string(Temp_string_2);
            }
            break;
            
            case 'L':
            {
                Motor_Speed = SPI_ui8TransmitRecive(DUMY_DATA);
                LCD_clearscreen();
                LCD_Convert_uint8_to_string(Motor_Speed , Temp_string_3);
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("CAR Direction: Left"); 
                LCD_movecursor(2 ,1); 
                LCD_vSend_string("Motor Speed:");
                LCD_movecursor(2 ,15); 
                LCD_vSend_string(Temp_string_3);
            }
            break;
            
            case 'B':
            {
                Motor_Speed = SPI_ui8TransmitRecive(DUMY_DATA);
                LCD_clearscreen();
                LCD_Convert_uint8_to_string(Motor_Speed , Temp_string_4);
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("CAR Direction: Back");
                LCD_movecursor(2 ,1); 
                LCD_vSend_string("Motor Speed:");
                LCD_movecursor(2 ,15); 
                LCD_vSend_string(Temp_string_4);
            }
            break;
            
            case 'A':
            {
                LCD_clearscreen();
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("Warming,there's Car");
                LCD_movecursor(2 ,1);
                LCD_vSend_string("in left blind side"); 
            }
            break;
            
            case 'C':
            {
                LCD_clearscreen();
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("Warming,there's Car");
                LCD_movecursor(2 ,1);
                LCD_vSend_string("in Right blind side");
            }
            break;
            
            case 'X':
            {
                LCD_clearscreen();
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("Warming,there's Car");
                LCD_movecursor(2 ,1);
                LCD_vSend_string("dist. less than 30cm");
            }
            break;
            
            case 'Z':
            {
                LCD_clearscreen();
                LCD_movecursor(1 ,1); 
                LCD_vSend_string("Car Stopped");
                LCD_movecursor(2 ,1);
                LCD_vSend_string("dist. less than 10cm");
            }
            break;
            
            case 'W':
            {
                /* transmit the value of back ultrasonic */
                _delay_ms(300);        
                Ultrasonic_Value = ULTRASONIC_GeTValue();
                
                SPI_ui8TransmitRecive(Ultrasonic_Value>>8);
                SPI_ui8TransmitRecive(Ultrasonic_Value);
            }
            break;
            
            case 'O':
            {
                LCD_clearscreen();        
            }
            break;
        }

    }
}

void Application_Init(void)
{
    /* initialize LCD */
    LCD_vInit();
    /* initialize Ultrasonic sensor */
    ULTRASONIC_Init();
    /* SPI initialization */
    SPI_vInitSlave();
}
