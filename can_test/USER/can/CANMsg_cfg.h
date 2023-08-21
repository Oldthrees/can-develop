/*
 * CANMsg_cfg.h
 *
 *  Created on: 2022年3月4日
 *      Author: ly
 */

#ifndef USER_CANMSG_CFG_H_
#define USER_CANMSG_CFG_H_

#include <stdio.h>

#define RX_MSG_NUM		2
#define TX_MSG_NUM		5

typedef enum{
	eTxMsg1 = 0,
	eTxMsg2,
	eTxMsg3,
	eTxMsg4,
	eTxMsg5,
}eTxMsg;

typedef enum{
	eRxMsg1 = 0,
	eRxMsg2,
}eRecMsg;

//can报文属性结构体
typedef struct{
	uint32_t uID;
	uint32_t uLen;
	uint16_t uCycle;
	uint8_t  uEvent;
	uint8_t  res;
	uint32_t mask;
}sCANMsg_attribute;

typedef union{
	struct{
		uint32_t eRxMsg1		:1;
		uint32_t eRxMsg2		:1;
		uint32_t res			:30;
	}bits;
	uint32_t dword;
}sMsgMiss;

extern uint16_t MsgMissCnt[RX_MSG_NUM];
extern const uint16_t MsgMissed[RX_MSG_NUM];

extern sCANMsg_attribute mTMsgAttr[TX_MSG_NUM];
extern sCANMsg_attribute mRMsgAttr[RX_MSG_NUM];
extern sMsgMiss mMsgMiss;

#endif /* USER_CANMSG_CFG_H_ */
