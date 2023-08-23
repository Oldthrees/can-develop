/*
 * CANServe.c
 *
 *  Created on: 2022年3月4日
 *      Author: ly
 */

#include "CANServe.h"

uint32_t Message_Tim_Cnt[TX_MSG_NUM] = {0, 1 , 3 , 5 , 7};

uint8_t BusOff = 0;
uint8_t BusOffFilt = 0;
//上电禁止标志，等于0代表刚上电，禁止诊断，等于0x55后可以诊断
uint8_t PwrOnDis = 0;
eKoer CanBusErr;

sSysTim mSysTim;

void CANFilterConfig_IdMask_StandardIdOnly(void)
{
	//CAN_FilterConfTypeDef  sFilterConfig;
	CAN_FilterInitTypeDef sFilterConfig;
	uint16_t		mask,tmp,i;

	sFilterConfig.CAN_FilterMode = CAN_FilterMode_IdMask; 	//配置为掩码模式
	sFilterConfig.CAN_FilterScale = CAN_FilterScale_32bit;	//设置为32位宽
	sFilterConfig.CAN_FilterIdHigh =(mRMsgAttr[0].uID<<5);		//验证码可以设置为StdIdArray[]数组中任意一个，这里使用StdIdArray[0]作为验证码
	sFilterConfig.CAN_FilterIdLow =0;

	mask =0x7ff;						//下面开始计算屏蔽码
	for(i =0; i<RX_MSG_NUM; i++) 	//屏蔽码位StdIdArray[]数组中所有成员的同或结果
	{
	tmp =mRMsgAttr[i].uID ^ (~mRMsgAttr[0].uID);	//所有数组成员与第0个成员进行同或操作
	mask &=tmp;
	}
	sFilterConfig.CAN_FilterMaskIdHigh =(mask<<5);
	sFilterConfig.CAN_FilterMaskIdLow =0|0x02;		//只接收数据帧

	sFilterConfig.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;		//设置通过的数据帧进入到FIFO0中
	sFilterConfig.CAN_FilterActivation = ENABLE;						//激活过滤器
//	sFilterConfig.FilterBank = 0; 		 //过滤器0     0~13 数字越小，优先级越高

	CAN_FilterInit(&sFilterConfig);

	/*CAN通讯中断使能*/
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);

}

/*
 * 0: success, 1: fail
 */
uint8_t CAN_Send_Cyc(uint8_t index){
	uint8_t ret = 1;
	uint8_t mailbox;
	CanTxMsg can_msg_sed;

	can_msg_sed.IDE = CAN_ID_STD;
	can_msg_sed.RTR = CAN_RTR_DATA;

	switch(index){
	case eTxMsg1:
		can_msg_sed.StdId = mTMsgAttr[index].uID;
		can_msg_sed.DLC = mTMsgAttr[index].uLen;
		memcpy((void *)can_msg_sed.Data, (void *)&mTxDat1, 8);
		mailbox = CAN_Transmit(CANx, &can_msg_sed);
		break;
        case eTxMsg2:
		can_msg_sed.StdId = mTMsgAttr[index].uID;
		can_msg_sed.DLC = mTMsgAttr[index].uLen;
		memcpy((void *)can_msg_sed.Data, (void *)&mTxDat2, 8);
		mailbox = CAN_Transmit(CANx, &can_msg_sed);
		break;
	default:
		ret = 1;
		break;
	}

	//last time success?
	if(CANx->TSR | (0x02 << (mailbox * 8))){
		ret = 0;
	}else{
		ret = 1;
	}
	return ret;
}

void Msg_Miss_Monitor(uint8_t MsgIndex){
	MsgMissCnt[MsgIndex]++;
	if(MsgMissCnt[MsgIndex] >= MsgMissed[MsgIndex]){
		MsgMissCnt[MsgIndex] = MsgMissed[MsgIndex];
		mMsgMiss.dword |= 1 <<  MsgIndex;
	}else{
		mMsgMiss.dword &= ~(1 << MsgIndex);
	}
}

void Msg_Miss_Reset(uint8_t MsgIndex){
	MsgMissCnt[MsgIndex] = 0;
}

uint8_t MsgIsMiss(eRecMsg Msg){
	return((mMsgMiss.dword >> Msg) & 0x01);
}

/*
 * CAN 调度
 */
void CAN_Task_Sched(void){
	uint8_t i;
	static uint16_t su16Tim = 0;

	//上电禁止100ms
	if(PwrOnDis == DIAGEN){
		if(su16Tim != mSysTim.u16msTimer){
			su16Tim = mSysTim.u16msTimer;
			for(i=0;i<RX_MSG_NUM;i++){
				Msg_Miss_Monitor(i);
			}
		}
	}else{

	}


	for(i=0;i<TX_MSG_NUM;i++){
		if(mTMsgAttr[i].uEvent){
			//事件帧优先发送
			if(CAN_Send_Cyc(i) == 0){
				//发送成功清除标识
				mTMsgAttr[i].uEvent = 0;
				BusOff = 0;
			}else{
				//不成功等下个轮回继续尝试，直到成功为止
			}
		}else{
			//周期帧轮询查是否到时间，到了即发送
			if((int32_t)(mSysTim.u32msTimer - Message_Tim_Cnt[i]) >= mTMsgAttr[i].uCycle){
				if(CAN_Send_Cyc(i) == 0){
					//发送成功刷新时间
					Message_Tim_Cnt[i] = mSysTim.u32msTimer;
					BusOff = 0;
				}else{
					//不成功等下次尝试
				}
			}else{

			}
		}
	}
}


void CAN_IRQCallBack(void)
{
	CanRxMsg can_msg_rec;
	uint8_t i;

	//上电禁止100ms
	// if(PwrOnDis == DIAGEN){
	// 	//busoff
	// 	if (wpara & CAN_CTRL1_EIF_Msk){
	// 		BusOff = 1;
	// 	}
	// 	//总线错误
	// 	if(wpara & CAN_CTRL1_BEIF_Msk){
	// 		CanBusErr = lpara;
	// 	}
	// }else{

	// }

	BusOff = 0;
	CAN_Receive(CANx, CAN_FIFO0, &can_msg_rec);
	for(i=0;i<RX_MSG_NUM;i++){
		if(can_msg_rec.StdId == mRMsgAttr[i].uID){
			Msg_Miss_Reset(i);
			switch(i){
			case eRxMsg1:
				memcpy((void *)&mRxDat1,(void *)can_msg_rec.Data,8);
				break;
			case eRxMsg2:
				memcpy((void *)&mRxDat2,(void *)can_msg_rec.Data,8);
			default:
				break;
			}
		}else{

		}
	}
}

uint8_t BusOffFilter(uint8_t busoff){
	uint8_t ret;
	static uint16_t Tim;

	if(busoff){
		Tim++;
		if(Tim > BUSOFF_FILT_TIM){
			ret = 1;
		}
	}else{
		Tim = 0;
		ret = 0;
	}

	return ret;
}
