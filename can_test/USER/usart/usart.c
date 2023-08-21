#include <usart.h>
#include "stm32f10x_it.h" 
#include "stm32f10x_usart.h"

uint8_t sum(uint8_t *array, uint8_t n)//对数组a的前n个元素求和，并返回和值
{
    uint8_t add = 0;
    for(uint8_t i=0;i<n;++i)
        add+=array[i];
    return add;
}

void data_send(USART_TypeDef* USARTx,uint8_t *array,uint16_t num)
{
    for(int j=0;j<num;j++) 
    {
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);  
        USART_SendData(USARTx,array[j]);  
    }
}

void USART1_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    //USART1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//开启串口帧中断
    
    USART_Cmd(USART1, ENABLE);                    //使能串口
    
    USART_ClearFlag(USART1,USART_FLAG_TC);
}

void USART2_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    
    NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    //USART2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口
    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//开启串口帧中断
    
    USART_Cmd(USART2, ENABLE);                    //使能串口
    
    USART_ClearFlag(USART2,USART_FLAG_TC);
}

void uart_recv(void)
{ 
    if(Usart2_recv_state == FINISH)
    {
        if(Usart2_RecvPointer == 18)
        {
            radar_state[0] = Usart2_RecvBuffer[7] - 0x30;
            radar_state[1] = (Usart2_RecvBuffer[13] - 0x30)*10 + (Usart2_RecvBuffer[14] - 0x30);
        }
        else if(Usart2_RecvPointer == 17)
        {
            radar_state[0] = Usart2_RecvBuffer[7] - 0x30;
            radar_state[1] = Usart2_RecvBuffer[13] - 0x30;
        }
        
        
//        memset(Usart2_RecvBuffer,0,100);
        Usart2_RecvPointer = 0;
        Usart2_recv_state=FREE;
    }
}




