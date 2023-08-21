/*
 * CANMsg_cfg.c
 *
 *  Created on: 2022年3月4日
 *      Author: ly
 */

#include "CANMsg_cfg.h"

uint16_t MsgMissCnt[RX_MSG_NUM];

//信号丢失时间，持续Xms之后认为丢失
const uint16_t MsgMissed[RX_MSG_NUM] = {500,500};

sCANMsg_attribute mTMsgAttr[TX_MSG_NUM] = {
		[eTxMsg1]
		 {
			.uID = 0x111,
			.uLen = 8,
			.uCycle = 10,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
		 [eTxMsg2]
		 {
			.uID = 0x222,
			.uLen = 8,
			.uCycle = 20,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
		 [eTxMsg3]
		 {
			.uID = 0x333,
			.uLen = 8,
			.uCycle = 50,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
		 [eTxMsg4]
		 {
			.uID = 0x444,
			.uLen = 8,
			.uCycle = 100,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
		 [eTxMsg5]
		 {
			.uID = 0x555,
			.uLen = 8,
			.uCycle = 500,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
};

sCANMsg_attribute mRMsgAttr[RX_MSG_NUM] = {
		[eRxMsg1]
		 {
			.uID = 0x131,
			.uLen = 8,
			.uCycle = 20,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
		 [eRxMsg2]
		 {
			.uID = 0x141,
			.uLen = 8,
			.uCycle = 20,
			.uEvent = 0,
			.mask = 0x00000000,
		 },
};

sMsgMiss mMsgMiss;

