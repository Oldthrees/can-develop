#ifndef __USART_H_
#define __USART_H_

#include "stm32f10x.h"

extern uint8_t sum(uint8_t *array, uint8_t n);//������a��ǰn��Ԫ����ͣ������غ�ֵ
extern void USART2_Configuration(void);

extern void data_send(USART_TypeDef* USARTx,uint8_t *array,uint16_t num);
extern void uart_recv(void);


#endif