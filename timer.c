#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

static unsigned short tcnt0;

static int timer_2ms_cnt;
static int timer_10ms_cnt;
static int timer_30ms_cnt;
static int timer_40ms_cnt;
static int timer_50ms_cnt;
static int timer_100ms_cnt;
static int timer_300ms_cnt;
static int timer_1s_cnt;

static int timer_2ms_flag;
static int timer_10ms_flag;
static int timer_30ms_flag;
static int timer_40ms_flag;
static int timer_50ms_flag;
static int timer_100ms_flag;
static int timer_300ms_flag;
static int timer_1s_flag;


ISR(TIMER0_OVF_vect)
{
	if(++timer_2ms_cnt == 2)
	{
		timer_2ms_flag = 1;
		timer_2ms_cnt = 0;
	}
	if(++timer_10ms_cnt == 10)
	{
		timer_10ms_flag = 1;
		timer_10ms_cnt = 0;
	}
	if(++timer_30ms_cnt == 30)
	{
		timer_30ms_flag = 1;
		timer_30ms_cnt = 0;
	}
	if(++timer_40ms_cnt == 40)
	{
		timer_40ms_flag = 1;
		timer_40ms_cnt = 0;
	}
	if(++timer_50ms_cnt == 50)
	{
		timer_50ms_flag = 1;
		timer_50ms_cnt = 0;
	}
	if(++timer_100ms_cnt == 100)
	{
		timer_100ms_flag = 1;
		timer_100ms_cnt = 0;
	}
	if(++timer_300ms_cnt == 300)
	{
		timer_300ms_flag = 1;
		timer_300ms_cnt = 0;
	}
	if(++timer_1s_cnt == 1000)
	{
		timer_1s_flag = 1;
		timer_1s_cnt = 0;
	}
	TCNT0 = 6;
}


void timer_init(int timer,long f_cpu,long freq)
{
	tcnt0 = 256 - ((f_cpu/64)/freq);
	
	if(timer == 0)
	{
		TCCR0 = (1<<CS02);			// 일반모드, 분주비 64
		TIMSK = TIMSK | (1<<TOIE0);			// overflow 인터럽트 발생
		TCNT0 = tcnt0;
	}
	else if(timer == 2)
	{
		TCCR2 = (1<<CS21);		//일반모드 분주비 8, 58us만들기 위해서
		TCNT2 = 58;
		TIMSK = TIMSK | (1<<TOIE2);
	}
	/*else if(timer == 3)
	{
		TCCR3A = (1<<COM3A1) | (1<<WGM31);			// 일반모드 16bit (max 값 65535  0xffff)
		TCCR3B = (1<<WGM33) | (1<<CS31);					// 분주비 64
		TCCR3C = 0;
		TCNT3 = 0;
	}*/
	if(timer == 3)
	{
		TCCR3A = 0;
		TCCR3B = (1<<CS30);
		TCCR3C = 0;
		TCNT3H = 0xff;
		TCNT3L = 0xf0;
		ETIMSK = 0b00000100;
	}
	
	sei();
}

int timer_flag(int time)
{
	if(time == TIMER_2MS)
	{
		if(timer_2ms_flag == 1)
		{
			timer_2ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_10MS)
	{
		if(timer_10ms_flag == 1)
		{
			timer_10ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_30MS)
	{
		if(timer_30ms_flag == 1)
		{
			timer_30ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_40MS)
	{
		if(timer_40ms_flag == 1)
		{
			timer_40ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_50MS)
	{
		if(timer_50ms_flag == 1)
		{
			timer_50ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_100MS)
	{
		if(timer_100ms_flag == 1)
		{
			timer_100ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_300MS)
	{
		if(timer_300ms_flag == 1)
		{
			timer_300ms_flag = 0;
			return 1;
		}
	}
	if(time == TIMER_1S)
	{
		if(timer_1s_flag == 1)
		{
			timer_1s_flag = 0;
			return 1;
		}
	}
	return 0;
}