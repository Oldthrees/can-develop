#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_it.h" 

struct CONFIG config;

uint8_t addr = 0;//地址

uint8_t radar_state[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

uint8_t flag = 0;
CanTxMsg TxMessage;
CanRxMsg RxMessage;	

void main(void)
{
    delay_init();
//    GPIO_initialization();
    TIM3_Mode_Config();
    USART2_Configuration();
    
    CAN_Config();

    MAX485_RECV;
       
    while(1)
    {

        
        uart_recv();
        
//        CAN_SetMsg(&TxMessage);
//        CAN_Transmit(CANx, &TxMessage);
//        
//        for(uint8_t i=0;i<2;i++)
//        {
//            delay_ms(500);
//        }
        
        if(flag==1)
        {	
//            if(RxMessage.Data[0] == 0x11 && RxMessage.Data[1] == 0x22 && RxMessage.Data[2] == 0x33 && RxMessage.Data[3] == 0x44 && RxMessage.Data[4] == 0x55 && RxMessage.Data[5] == 0x66 && RxMessage.Data[6] == 0x77 && RxMessage.Data[7] == 0x88)
//            {
//                CAN_SetMsg(&TxMessage);
//                CAN_Transmit(CANx, &TxMessage);
//            }
              uint8_t ubCounter = 0;
            for (ubCounter = 0; ubCounter < 8; ubCounter++)
            {
              RxMessage.Data[ubCounter] = 0x00;
            }
            flag=0;
        }
    }
}
