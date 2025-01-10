/*
 * LCD.c
 *
 * Created: 2/23/2018 4:38:26 PM
 *  Author: Mohamed Zaghlol
 */ 
#include "LCD.h"
#include <util/delay.h>

void LCD_vInit(void)
{
	_delay_ms(200);
	#if defined eight_bits_mode
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN0,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN1,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN2,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN3,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN4,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN5,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN6,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTC_INDEX,GPIO_PIN7,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTD_INDEX,EN,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTD_INDEX,RW,GPIO_PIN_DIRECTION_OUTPUT);
	GPIO_PinDirection(PORTD_INDEX,RS,GPIO_PIN_DIRECTION_OUTPUT);
	//DIO_write('B',RW,0);
	LCD_vSend_cmd(EIGHT_BITS); //8 bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1); 
	
	#elif defined four_bits_mode
	DIO_vsetPINDir('A',4,1);
	DIO_vsetPINDir('A',5,1);
	DIO_vsetPINDir('A',6,1);
	DIO_vsetPINDir('A',7,1);
	DIO_vsetPINDir('B',EN,1);
	DIO_vsetPINDir('B',RW,1);
	DIO_vsetPINDir('B',RS,1);
   	DIO_write('B',RW,0);
	LCD_vSend_cmd(RETURN_HOME); //return home
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS); //4bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1);
	#endif
}


static void send_falling_edge(void)
{
	GPIO_PinWriteLogic(PORTD_INDEX,EN,1);
	_delay_ms(2);
	GPIO_PinWriteLogic(PORTD_INDEX,EN,0);
	_delay_ms(2);
}
void LCD_vSend_cmd(char cmd)
{
	#if defined eight_bits_mode
	GPIO_PORTWriteLogic(PORTC_INDEX,cmd);
	GPIO_PinWriteLogic(PORTD_INDEX,RS,0);
	send_falling_edge();
	
	#elif defined four_bits_mode
	write_high_nibble('A',cmd>>4);
	DIO_write('B',RS,0);
	send_falling_edge();
	write_high_nibble('A',cmd);
	DIO_write('B',RS,0);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void LCD_vSend_char(char data)
{
	#if defined eight_bits_mode
	GPIO_PORTWriteLogic(PORTC_INDEX,data);
	GPIO_PinWriteLogic(PORTD_INDEX,RS,1);
	send_falling_edge();
	
	#elif defined four_bits_mode
	write_high_nibble('A',data>>4);
	DIO_write('B',RS,1);
	send_falling_edge();
	write_high_nibble('A',data);
	DIO_write('B',RS,1);
	send_falling_edge();
	#endif
	_delay_ms(1);
}


void LCD_vSend_string(char *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		data++;
	}
}
void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_movecursor(char row,char coloumn)
{
	char data;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}

void LCD_Convert_uint8_to_string(uint8 value , uint8 *str)
{
    uint8 Temp_string[5] = {0};
    uint8 Counter = 0;
    if(NULL == str)
    {
    	/* Nothing */
    }
    else
    {
        memset(str , ' ' , 5);
        str[5] = '\0';
        sprintf((char *)Temp_string , "%i" , value);
        while(Temp_string[Counter] != '\0')
        {
        	str[Counter] = Temp_string[Counter];
            Counter++;
        }
    }
}
