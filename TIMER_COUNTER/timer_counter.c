#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

#define CPU_CLOCK       16000000
#define TICKS_PER_SEC   1000

volatile unsigned int tic_time;

SIGNAL(SIG_OVERFLOW0)
{
    tic_time++;

    TCNT0 = 256 - (CPU_CLOCK / TICKS_PER_SEC / 64);
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

    TCCR0 = (1 << CS02) | (0 << CS01) | (0 << CS00);
    TCNT0 = 256 - (CPU_CLOCK / TICKS_PER_SEC / 64);

    TIMSK = (0 << OCIE0) | (1 << TOIE0);

    sei();

    while(1)
    {
        led_status = ~led_status;
        
        PORTC = led_status;

        delay_ms(1000);
    }

    return 1;
}
