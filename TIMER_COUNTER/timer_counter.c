#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

#define CPU_CLOCK       16000000
#define TICKS_PER_SEC   1000

volatile unsigned int tic_time;

SIGNAL(SIG_OUTPUT_COMPARE0)
{
    tic_time++;
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

    TIMSK = (1 << OCIE0) | (0 << TOIE0);

    sei();

    while(1)
    {
        led_status = ~led_status;
        
        PORTC = led_status;

        delay_ms(1000);
    }

    return 1;
}
