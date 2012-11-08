#include <avr/io.h>

volatile unsigned delay(int iv);

int main(void)
{
    unsigned int val = 0;
    
    DDRC = 0xff;                /* 출력으로 설정 */
    PORTC = 0xff;               /* 포트 초기화 */
    
    while(1)
    {
        PORTC = ~(1 << val);    /* shift 연산: 1을 val 만큼 옮기면서 간다. */
        val = val + 1;
        
        delay(5);

        if(val > 4)             /* LED 끝까지 왔을 경우 */
        {
            val = 0;            /* 다시 처음으로 돌아간다. */
        }
        
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
