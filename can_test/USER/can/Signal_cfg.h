/*
 * Signal_cfg.h
 *
 *  Created on: 2022年3月4日
 *      Author: ly
 */

#ifndef _SIGNAL_CFG_H_
#define _SIGNAL_CFG_H_

#include "stm32f10x.h"
//#include "typedefs.h"
//#include "config.h"

typedef union{
	struct{
		uint8_t bit0	:1;
		uint8_t bit1	:1;
		uint8_t bit2	:1;
		uint8_t bit3	:1;
		uint8_t bit4	:1;
		uint8_t bit5	:1;
		uint8_t bit6	:1;
		uint8_t bit7	:1;
		uint8_t bytes[7];
	}bits;
	uint8_t byte[8];
}sTxDat;

typedef union{
	struct{
		uint8_t bytes[7];
		uint8_t bit0	:1;
		uint8_t bit1	:1;
		uint8_t bit2	:1;
		uint8_t bit3	:1;
		uint8_t bit4	:1;
		uint8_t bit5	:1;
		uint8_t bit6	:1;
		uint8_t bit7	:1;		
	}bits;
	uint8_t byte[8];
}sRxDat;

extern sTxDat mTxDat1;
extern sTxDat mTxDat2;
extern sTxDat mTxDat3;
extern sTxDat mTxDat4;
extern sTxDat mTxDat5;

//RX
extern sRxDat mRxDat1;
extern sRxDat mRxDat2;
#endif /* USER_SIGNAL_CFG_H_ */
