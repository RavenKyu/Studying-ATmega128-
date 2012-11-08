#include <avr/io.h>

volatile unsigned delay(int iv);

int main(void)
{
    DDRC = 0xff;                /* 출력으로 설정 */
    PORTC = 0xff;               /* 포트 초기화 */
    
    while(1)
    {
        PORTC = ~PORTC;         /* 단순한 LED 껏다 켰다를 반복 */
        delay(5);
    }
    
    return 1;
}

volatile unsigned delay(int iv) /* 딜레이 함수 */
{
    volatile unsigned int i;
    volatile unsigned int i2;
    
    for(i = 0;i <= 65000;i++)
    {
        for(i2 = 0;i2 <= iv;i2++);
    }
}
