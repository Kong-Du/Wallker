#include <stdio.h>
#include <avr/io.h>
#include "usart.h"
#include <avr/interrupt.h>
#include "typedef.h"

static int uart_putchar(char c, FILE *stream);									//printf함수를 사용가능하게 해준다
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);	//printf함수를 사용가능하게 해준다

int a_1;
unsigned char *getdata_1;

ISR(USART1_RX_vect)
{
	a_1 = 1;
	getdata_1 = UDR1;
}

void uart0_transmit(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));				//UDRE0 = 5
	UDR0 = data;
}
void uart1_transmit(unsigned char data)
{
	while(!(UCSR1A & (1<<UDRE1)));				//UDRE0 = 5
	UDR1 = data;
}

unsigned char uart0_receive()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
unsigned char uart1_receive()
{
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

char usart1_getchar(char *get_1) // 수신 RX
{
	if (a_1 == 0)
	{
		return 0;
	}
	else
	{
		a_1 = 0;
		*get_1 = getdata_1;
		return 1;
	}
}

void uart0_putstring(unsigned char *str)
{
	while(NULL != *str)
	{
		if(*str == '\n')
		{
			uart0_transmit('\r');	// CR (carriage return) 제일 앞줄로
		}
		uart0_transmit(*str);
		str++;
	}
}
void uart1_putstring(unsigned char *str)
{
	while(NULL != *str)
	{
		if(*str == '\n')
		{
			uart1_transmit('\r');	// CR (carriage return) 제일 앞줄로
		}
		uart1_transmit(*str);
		str++;
	}
}

void uart0_getstring(unsigned char *str)
{
	while((*str = uart0_receive()) != 13)
	{
		str++;
	}
	*str = 0;
}
void uart1_getstring(unsigned char *str)
{
	while((*str = uart1_receive()) != 13)
	{
		str++;
	}
	*str = 0;
}

static int uart_putchar(char c, FILE *stream)	//printf함수를 사용가능하게 해준다.
{
	if (c == '\n')
	{
		uart_putchar('\r', stream);
	}
	while(!(UCSR0A & (1<<UDRE0)));				//UCSR0A의 비트5의 값이 1이면 while문 벗어난다. UDRE0 == 5 이고 상태플랙이다.
	UDR0 = c;
	return 0;
}

void uart_init(long f_cpu,long baud,int uart)	// mcu주파수,보레이트, 유아트 0,1 선택
{
	unsigned short ubrr = (f_cpu/(8*baud))-1;
	if(uart == USART0)
	{
		UBRR0H = (unsigned char)(ubrr>>8);		// set baud rate
		UBRR0L = (unsigned char)ubrr;
	
		UCSR0A = (1<<U2X0);						// 비동기모드 2배속 모드
		UCSR0B = (1<<RXEN0) | (1<<TXEN0);		// 송수신 허용
		UCSR0C = (3<<UCSZ00);					// 전송데이터 8bit, 1 stop bit
	}
	else if(uart == USART1)
	{
		UBRR1H = (unsigned char)(ubrr>>8);		// set baud rate
		UBRR1L = (unsigned char)ubrr;
		
		UCSR1A = (1<<U2X1);						// 비동기모드 2배속 모드
		UCSR1B = (1<<RXEN1) | (1<<TXEN1)| (1<<RXCIE1);		// 송수신 허용
		UCSR1C = (3<<UCSZ10);					// 전송데이터 8bit, 1 stop bit
	}
	stdout = &mystdout;
}