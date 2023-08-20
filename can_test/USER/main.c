#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_it.h" 

struct CONFIG config;

uint8_t addr = 0;//地址

uint8_t input_state_command[11] = {0x03,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

uint8_t flag = 0;
CanTxMsg TxMessage;
CanRxMsg RxMessage;	

void main(void)
{
    delay_init();
//    GPIO_initialization();
    TIM3_Mode_Config();
//    USART2_Configuration();
    
    CAN_Config();
    
    /*环回*/
    //CANx->BTR |= 0x40000000;

    config.state = 0;//地址尚未配置
      
    IO_OUT_LOW;
    
    LED_STATE_LOW;
      
    delay_ms(100);//等待初始化完成
    
    config.send_flag = 0;//初始化，防止干扰
    MAX485_RECV;
    
    uint32_t Address = 0;
    Address = COMMUNICATION_ADDR_ADDR;
    for(uint8_t j=0;j<1;j++)//读取1个uint8_t类型的数据
    {
        config.addr = (*(__IO uint32_t*) Address);
        Address++;
    }
    
    config.addr = 5;//test by sjq
    
    if(config.addr == 0 || config.addr == 0xff)
    {
        config.state = 0;
    }
    else
    {
        config.state = 1;
    }
       
    while(1)
    {
        if(IO_IN_READ == 1 && config.addr == 0 && config.send_flag == 0)
        {
            config.send_flag = 1;
            uint8_t data[4] = {0x01,0x04,TYPE,0x05+TYPE};
            
            MAX485_SEND;
            delay_ms(5);//确保状态切换完毕
            
            data_send(USART2,data,4);
            
            delay_ms(2);//确保发送完毕
            MAX485_RECV;
        }
        
//        uart_recv();
        
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
        
//        if(config.state == 1 && IO_IN_READ == 1)//地址配置完成发送IO口状态
//        {
//            input[0] = INPUT_1_READ;
//            input[1] = INPUT_2_READ;
//            input[2] = INPUT_3_READ;
//            input[3] = INPUT_4_READ;
//            input[4] = INPUT_5_READ;
//            input[5] = INPUT_6_READ; 
//    
//            if(input[0] != input_old[0] || input[1] != input_old[1] || input[2] != input_old[2] || input[3] != input_old[3] || input[4] != input_old[4] || input[5] != input_old[5])
//            {
//                input_state_command[2] = TYPE;
//                input_state_command[3] = config.addr;
//                input_state_command[4] = input[0];
//                input_state_command[5] = input[1];
//                input_state_command[6] = input[2];
//                input_state_command[7] = input[3];
//                input_state_command[8] = input[4];
//                input_state_command[9] = input[5];
//                input_state_command[10] = sum(input_state_command,10);
//                
//                MAX485_SEND;
//                delay_ms(1);//确保状态切换完毕
//                
//                data_send(USART2,input_state_command,11);
//                
//                delay_ms(2);//确保发送完毕
//                MAX485_RECV;
//            }
//            
//            input_old[0] = input[0];
//            input_old[1] = input[1];
//            input_old[2] = input[2];
//            input_old[3] = input[3];
//            input_old[4] = input[4];
//            input_old[5] = input[5]; 
//            
//            IO_OUT_HIGH;
//            delay_us(60);
//            IO_OUT_LOW;
//            
//        }
//        
//        for(uint8_t i=0;i<6;i++)
//        {
//            input[0] = INPUT_1_READ;
//            input[1] = INPUT_2_READ;
//            input[2] = INPUT_3_READ;
//            input[3] = INPUT_4_READ;
//            input[4] = INPUT_5_READ;
//            input[5] = INPUT_6_READ; 
//            
//            if(input[i] == 0)
//            {
//                port_set(i+1,0);
//            }
//            else
//            {
//                port_set(i+1,1);
//            }
//        }
    }
}
