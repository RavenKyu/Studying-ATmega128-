#include <avr/io.h>

volatile unsigned delay(int iv);

int main(void)
{
    DDRC = 0xff;                /* 출력으로 설정 */
    PORTC = 0xff;               /* 포트 초기화 */

    DDRF = 0x00;                /* Port F를 입력으로 설정 */
    
    while(1)
    {
        PORTC = PINF;           /* 받은 키값을 바로 출력으로 내보낸다. */
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
