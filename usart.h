#define USART0		0
#define USART1		1

void uart_init(long f_cpu,long baud,int uart);	// mcu���ļ�,������Ʈ, ����Ʈ 0,1 ����
void uart0_transmit(unsigned char data);
unsigned char uart0_receive();
void uart0_putstring(unsigned char *str);
void uart0_getstring(unsigned char *str);

void uart1_transmit(unsigned char data);
unsigned char uart1_receive();
void uart1_putstring(unsigned char *str);
void uart1_getstring(unsigned char *str);

char usart1_getchar(char *get_1);