#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

volatile char interrupt_flag;

/* INT4의 외부 인터럽트 함수 설정 */
SIGNAL(SIG_INTERRUPT4)
{
    interrupt_flag = 1;
}

int main(void)
{
    unsigned char led_status = 0xff;

    DDRC = 0xff;                /* LED 초기화 */
    PORTC = 0xff;

    EICRB = (0 << ISC41) | (0 << ISC40); /* INT4를 상승엣지 인터럽트 설정 */
    EIMSK = (1 << INT4);                 /* INT4를 활성화 */
    SREG = (1 << 7);                     /* 글로벌 인터럽트 활성화 sei() 대신 사용하였다. */

    while(1)
    {
        if(interrupt_flag == 1) /* 인터럽트가 들어왔을 경우. */
        {
            led_status = ~led_status;
        
            PORTC = led_status;

            interrupt_flag = 0;
        }
    }

    return 1;
}
