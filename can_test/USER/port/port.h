#ifndef __PORT_H_
#define __PORT_H_

#include "stm32f10x.h"

#define MAX485_EN_CLOCK         (RCC_APB2Periph_GPIOB)
#define MAX485_EN_PORT          (GPIOB)
#define MAX485_EN_PINS          (GPIO_Pin_9)
#define MAX485_SEND             GPIO_SetBits(MAX485_EN_PORT,MAX485_EN_PINS)
#define MAX485_RECV             GPIO_ResetBits(MAX485_EN_PORT,MAX485_EN_PINS)

#define OUTPUT_CLOCK         (RCC_APB2Periph_GPIOB)
#define OUTPUT_PORT          (GPIOB)
#define OUTPUT_PINS          (GPIO_Pin_6)
#define OUTPUT_HIGH          GPIO_SetBits(OUTPUT_PORT,OUTPUT_PINS)
#define OUTPUT_LOW           GPIO_ResetBits(OUTPUT_PORT,OUTPUT_PINS)

extern void GPIO_initialization(void);

#endif