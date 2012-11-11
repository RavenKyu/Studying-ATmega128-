#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

#define CPU_CLOCK       16000000
#define TICKS_PER_SEC   1000

volatile unsigned int tic_time;
volatile char interrupt_flag;

SIGNAL(SIG_OUTPUT_COMPARE0)
{
    tic_time++;
}

/* INT4의 외부 인터럽트 함수 설정 */
SIGNAL(SIG_INTERRUPT4)
{
    interrupt_flag = 1;
}

void delay_ms(unsigned int msec)
{
    tic_time = 0;

    while(msec > tic_time);        
}

int main(void)
{
    unsigned char led_status = 0xff;

    DDRC = 0xff;                /* LED 초기화 */
    PORTC = 0xff;

    TCCR0 = (1 << CS02) | (0 << CS01) | (0 << CS00) | (0 << WGM00) | (1 << WGM01); /* 비교 인터럽트 */
    OCR0 = 250;                 /* OCR을 초기화 6을 따로 줄 필요가 없다. */

    EICRB = (0 << ISC41) | (0 << ISC40); /* INT4를 상승엣지 인터럽트 설정 */
    EIMSK = (1 << INT4);                 /* INT4를 활성화 */

    TIMSK = (1 << OCIE0) | (0 << TOIE0);

    sei();

    while(1)
    {
        if(interrupt_flag == 1) /* 인터럽트가 들어왔을 경우. */
        {
            led_status = ~led_status;
        
            PORTC = led_status;

            delay_ms(1000);
            interrupt_flag = 0;
        }
    }

    return 1;
}
