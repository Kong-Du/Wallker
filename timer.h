
#define TIMER_2MS		2
#define TIMER_10MS		10
#define TIMER_30MS		30
#define TIMER_40MS		40
#define TIMER_50MS		50
#define TIMER_100MS		100
#define TIMER_300MS		300
#define TIMER_1S		1000

void timer_init(int timer,long f_cpu,long freq);
int timer_flag(int time);

extern unsigned int time_value;