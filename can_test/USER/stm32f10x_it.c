/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_can.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

uint16_t timer = 0;

void  TIM1_UP_IRQHandler (void)
{
    if ( TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET ) 
    {	
        TIM_ClearITPendingBit(TIM1 , TIM_FLAG_Update); 
        
        timer++;
    }		 	
}

uint8_t Usart1_RecvBuffer[100];
int Usart1_RecvPointer = 0;
uint8_t Usart1_recv_state = FREE;

//串口1中断服务程序  
void USART1_IRQHandler(void)  
{        
    //接收中断  
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
    {     
        //清空串口接收标记  
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);  
          
        //获取缓冲区数据       
        Usart1_RecvBuffer[Usart1_RecvPointer++] = USART_ReceiveData(USART1);  

        Usart1_recv_state=RECEVING;
    }  
    else if(USART_GetFlagStatus(USART1, USART_FLAG_IDLE) != RESET)
    {
        USART1->SR;
        USART1->DR;

        Usart1_recv_state=FINISH;
    }
}

uint8_t Usart2_RecvBuffer[100];
int Usart2_RecvPointer = 0;
uint8_t Usart2_recv_state = FREE;

//串口2中断服务程序  
void USART2_IRQHandler(void)  
{        
    //接收中断  
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
    {     
        //清空串口接收标记  
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);  
          
        //获取缓冲区数据       
        Usart2_RecvBuffer[Usart2_RecvPointer++] = USART_ReceiveData(USART2);  

        Usart2_recv_state = RECEVING;
    }  
    else if(USART_GetFlagStatus(USART2, USART_FLAG_IDLE) != RESET)
    {
        USART2->SR;
        USART2->DR;

        Usart2_recv_state = FINISH;
    }
}

extern uint8_t flag ;
extern CanRxMsg RxMessage;
extern CanTxMsg TxMessage;

uint32_t TX=0;
uint32_t RX=0;

void CAN_RX_IRQHandler(void)
{
	/*´ÓÓÊÏäÖÐ¶Á³ö±¨ÎÄ*/
	CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
        RX++;

	/* ±È½ÏIDÊÇ·ñÎª0x1314 */ 
	if((RxMessage.StdId==0x111) && (RxMessage.IDE==CAN_ID_STD) && (RxMessage.DLC==8) )
	{
	flag = 1; 					       //½ÓÊÕ³É¹¦  
                        CAN_SetMsg(&TxMessage);
                CAN_Transmit(CANx, &TxMessage);
                
                TX++;
	}
	else
	{
	flag = 0; 					   //½ÓÊÕÊ§°Ü
	}
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */



/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
