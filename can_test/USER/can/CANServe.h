/*
 * CANServe.h
 *
 *  Created on: 2022年3月4日
 *      Author: ly
 */

#ifndef _CANSERVE_H_
#define _CANSERVE_H_

#include "stm32f10x.h"
#include <stdio.h>
#include <can.h>
#include "CANMsg_cfg.h"
#include "Signal_cfg.h"

#define DIAGDIS			0
#define DIAGEN			0x55
#define BUSOFF_FILT_TIM		500

//can总线错误类型
typedef enum{
	NoErr = 0,		//没错误
	BitErr,			//位错误
	FormErr,		//形式错误
	StuffErr,		//填充错误
	AckErr,			//应答错误
	CrcErr,			//CRC错误
	OthErr,			//其它错误
}eKoer;

typedef struct{
    uint16_t u16msTimer;
    uint16_t res;
    uint32_t u32msTimer;
}sSysTim;

extern sSysTim mSysTim;

extern eKoer CanBusErr;
extern uint8_t BusOff;
extern uint8_t BusOffFilt;
extern uint8_t PwrOnDis;

uint8_t MsgIsMiss(eRecMsg node);
void CAN_Task_Sched(void);
void CAN_IRQCallBack(void);
uint8_t BusOffFilter(uint8_t busoff);

#endif /* USER_CANSERVE_H_ */
