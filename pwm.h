enum PRESCALE {PRESCALE_0, PRESCALE_1, PRESCALE_8, PRESCALE_64, PRESCALE_256, PRESCALE_1024};
enum PWM {PWM0, PWM1A, PWM1B, PWM2, PWM3A, PWM3B, PWM3C};

void pwm_init(int timer,int prescale);
void pwm_output(int timer, int duty);
