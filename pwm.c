
#include <avr/io.h>
#include "usart.h"
#include "pwm.h"
#include "typedef.h"

void pwm_init(int timer,int prescale)
{
	if(timer == 1)
	{
		TCCR1A = (1<<COM1A1) | (1<<WGM11);
		TCCR1B = (1<<WGM13) | prescale;
		TCCR1C = 0;
		TCNT1 = 0;
		OCR1A = 0;
	}
	else if(timer == 2)		
	{
		
	}
	else if(timer == 3)		
	{
		TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) |prescale;
		TCNT2 = 0;
		OCR2 = 0;
	}
	else if(timer == 4)		
	{
		TCCR3A = (1<<COM3A1) | (1<<WGM30);
		TCCR3B = (1<<WGM32) | prescale;
		TCCR3C = 0;
		TCNT3 = 0;
		OCR3C = 0;
	}
	else if(timer == 5)		
	{
		TCCR3A = (1<<COM3B1) | (1<<WGM30);
		TCCR3B = (1<<WGM32) | prescale;
		TCCR3C = 0;
		TCNT3 = 0;
		OCR3C = 0;
	}
	else if(timer == 6)		
	{
		TCCR3A = (1<<COM3C1) | (1<<WGM30);
		TCCR3B = (1<<WGM32) | prescale;
		TCCR3C = 0;
		TCNT3 = 0;
		OCR3C = 0;
	}
}

void pwm_output(int timer, int duty)
{
	int number = 0;
	number = (256*duty)/100;
	
	if(number > 255)
	{
		number = 255;
	}
	
	if(timer == 1)
	{
		/*if(number == 0)
		{
			TCCR1A = TCCR1A & ~(0xc0); // duty가 0 일때 pwm차단
		}
		else
		{
			TCCR1A = TCCR1A | 0x80;
			OCR1A = number;
		}*/
	}
	else if(timer == 2)
	{
		/*if(number == 0)
		{
			TCCR1A = TCCR1A & ~(0x30); // duty가 0 일때 pwm차단
		}
		else
		{
			TCCR1A = TCCR1A | 0x20;
			OCR1B = number;
		}*/
	}
	else if(timer == 3)
	{
		if(number == 0)
		{
			TCCR2 = TCCR2 & ~(0x30); // duty가 0 일때 pwm차단
		}
		else
		{
			TCCR2 = TCCR2 | 0x20;
			OCR2 = number;
		}
	}
	else if(timer == 4)
	{
		if(number == 0)
		{
			TCCR3A = TCCR3A & ~(0xc0); // duty가 0 일때 pwm차단
		}
		else
		{
			TCCR3A = TCCR3A | 0x80;
			OCR3A = number;
		}
	}
	else if(timer == 5)
	{
		if(number == 0)
		{
			TCCR3A = TCCR3A & ~(0x30); // duty가 0 일때 pwm차단
		}
		else
		{
			TCCR3A = TCCR3A | 0x20;
			OCR3B = number;
		}
	}
	else if(timer == 6)
	{
		if(number == 0)
		{
			TCCR3A = TCCR3A & ~(0x0c); // duty가 0 일때 pwm차단
		}
		else
		{
			TCCR3A = TCCR3A | 0x08;
			OCR3C = number;
		}
	}
	
}