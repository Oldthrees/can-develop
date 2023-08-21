#include <port.h>
#include <usart.h>

void GPIO_initialization(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;

    RCC_APB2PeriphClockCmd(MAX485_EN_CLOCK,ENABLE);
    GPIO_Initstructure.GPIO_Pin = MAX485_EN_PINS;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MAX485_EN_PORT,&GPIO_Initstructure);

    RCC_APB2PeriphClockCmd(OUTPUT_CLOCK,ENABLE);
    GPIO_Initstructure.GPIO_Pin = OUTPUT_PINS;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OUTPUT_PORT,&GPIO_Initstructure);
}

