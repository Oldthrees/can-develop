#ifndef __CAN_H_
#define __CAN_H_

#include "stm32f10x.h"


#define CANx                       	CAN1
#define CAN_CLK                    RCC_APB1Periph_CAN1
#define CAN_RX_IRQ									USB_LP_CAN1_RX0_IRQn
#define CAN_RX_IRQHandler					USB_LP_CAN1_RX0_IRQHandler

#define CAN_RX_PIN                 GPIO_Pin_8
#define CAN_TX_PIN                 GPIO_Pin_9
#define CAN_TX_GPIO_PORT          GPIOB
#define CAN_RX_GPIO_PORT          GPIOB
#define CAN_TX_GPIO_CLK           (RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB)
#define CAN_RX_GPIO_CLK           RCC_APB2Periph_GPIOB






/*debug*/

#define CAN_DEBUG_ON            1
#define CAN_DEBUG_ARRAY_ON      1
#define CAN_DEBUG_FUNC_ON       1



static void CAN_GPIO_Config(void);
static void CAN_NVIC_Config(void);
static void CAN_Mode_Config(void);
static void CAN_Filter_Config(void);
void CAN_Config(void);
void CAN_SetMsg(CanTxMsg *TxMessage);
void Init_RxMes(CanRxMsg *RxMessage);

#endif







