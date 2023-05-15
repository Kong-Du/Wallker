#define  F_CPU  16000000UL
#define BLDC_INITIAL 1000
#define DC_INITIAL 20000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "pwm.h"
#include "timer.h"
#include "usart.h"
#include "typedef.h"


void DC_Stop();
void DC_Go();
void DC_Back();
void DC_TurnLeft();
void DC_TurnRight();
void BLDC_ON();
void BLDC_OFF();

int main()
{
	unsigned char *posi;
	
	DDRA = 0xff;	//ATMEGA LED
	DDRE=0x38;      //DC(PE3,OC3A), DC(PE4,OC3B), DC(PE5,OC3C) 속도제어
	DDRB=0xa0;      //BLDC(PB5,OC1A), DC(PB7,OC2) 속도제어
	DDRC=0xff;	//(DC모터 방향제어)

	uart_init(F_CPU,115200,USART0);
	uart_init(F_CPU,115200,USART1);
	timer_init(0,F_CPU,1000);
	
	pwm_init(PWM2,PRESCALE_8);
	pwm_init(PWM3A,PRESCALE_8);
	pwm_init(PWM3B,PRESCALE_8);
	pwm_init(PWM3C,PRESCALE_8);
	
	pwm_init(PWM1A,PRESCALE_8);
	ICR1 = DC_INITIAL;
	OCR1A = BLDC_INITIAL;
	
	tbi(PORTA,0);		//ATMEGA PORTA0 ON(ATMEGA128A 작동 유무 확인 용도)
	
	unsigned int speed=100;
	
	while(1)
	{
		if(usart1_getchar(posi))
		{
			printf("posi : %c",*posi);
		}
		if(*posi == 'w')
		{
			DC_Go();
		}
		else if(*posi == 'a')
		{
			DC_TurnLeft();
		}
		else if(*posi == 's')
		{
			DC_Back();
		}
		else if(*posi == 'd')
		{
			DC_TurnRight();
		}
		else if(*posi == 'p')
		{
			DC_Stop();
		}
		else if(*posi == 'z')
		{
			BLDC_ON();
		}
		else if(*posi == 'x')
		{
			BLDC_OFF();
		}
	}
	void BLDC_ON()
	{
		OCR1A = 1500;
	}
	void BLDC_OFF()
	{
		OCR1A = 1000;
	}
	void DC_Stop()
	{
		PORTC = 0x00;      //정지
		pwm_output(PWM2,0);
		pwm_output(PWM3A,0);
		pwm_output(PWM3B,0);
		pwm_output(PWM3C,0);
	}
	void DC_Go()
	{
		PORTC = 0x95;      //전진
		pwm_output(PWM2,speed);
		pwm_output(PWM3A,speed);
		pwm_output(PWM3B,speed);
		pwm_output(PWM3C,speed);
	}
	void DC_Back()
	{
		PORTC = 0x6a;      //후진
		pwm_output(PWM2,speed);
		pwm_output(PWM3A,speed);
		pwm_output(PWM3B,speed);
		pwm_output(PWM3C,speed);
	}
	void DC_TurnRight()
	{
		PORTC = 0x65;      //우회전
		pwm_output(PWM2,speed);
		pwm_output(PWM3A,speed);
		pwm_output(PWM3B,speed);
		pwm_output(PWM3C,speed);
	}
	void DC_TurnLeft()
	{
		PORTC = 0x9a;      //좌회전
		pwm_output(PWM2,speed);
		pwm_output(PWM3A,speed);
		pwm_output(PWM3B,speed);
		pwm_output(PWM3C,speed);
	}
	
}