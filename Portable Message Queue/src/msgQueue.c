/**
* @file IPC_dmSock.c
* @brief This File has the definition of Portable Message
*	 	 Queue function
*
* @author Sunil Kumar
*
* @date 11/2/2021
*
*/

/*Inclusion of Headers*/
#include "../inc/msgQueue.h"

/*Static variables definitions*/
STATIC IPCP_msgQ RxMsgQBuffer[MAX_NUM_RX_PKT];
STATIC IPCP_msgQ MsgQBuffer[MAX_NUM_RX_PKT];

/*Public Functions Definition*/

/**
* @brief  This function is responsile for sending the data 
*		  to message queue
* @author Sunil Kumar
* @param  TxBuf: pointer to transmit buffer
* @param  size: length of the data in  bytes
* @param  key: message queue key ID
* @return return number of bytes sent or negative integer in case of failure
* @date   11/2/2021
*/
int32_t msgQSnd(uint8_t *TxBuf, uint32_t size, NumOfMsgQ key)
{
	uint8_t i = 0;
	int32_t retval = -1;
	if(TxBuf != NULL)
	{
		switch(key)
		{
		case MSGQ_1:
			for(i=0;i<MAX_NUM_Q;i++)
			{
				if(RxMsgQBuffer[i].dataAvailable == 0)
				{
					memcpy(&RxMsgQBuffer[i].MsgQBuffer, &TxBuf[0], size);
					RxMsgQBuffer[i].MsgQBufLen = size;
					RxMsgQBuffer[i].dataAvailable = 1;
					retval = 0;
					break;
				}
			}
			break;
		case MSGQ_2:
			for(i=0;i<MAX_NUM_Q;i++)
			{
				if(RxMsgQBuffer[i].dataAvailable == 0)
				{
					memcpy(&MsgQBuffer[i].MsgQBuffer, &TxBuf[0], size);
					MsgQBuffer[i].MsgQBufLen = size;
					MsgQBuffer[i].dataAvailable = 1;
					retval = 0;
					break;
				}
			}
			break;
		default:
			break;
		}
		if(i == 5)
		{
			retval = 0;
		}
	}
	return retval;
}
/**
* @brief  This function is responsile for retrieving the
*         number of messages in particular message queue
* @author Sunil Kumar
* @param  key: message queue key ID
* @return return number of messages in the message queue
*		  or zero incase of failure 
* @date   11/2/2021
*/
uint32_t msgQCount(NumOfMsgQ key)
{
	uint32_t i = 0;
	uint32_t num = 0;
	switch(key)
	{
	case MSGQ_1:
		for(i=0;i<MAX_NUM_Q;i++)
		{
			if(RxMsgQBuffer[i].dataAvailable == 1)
			{
				num++;
			}
		}
		break;
	case MSGQ_2:
		for(i=0;i<MAX_NUM_Q;i++)
		{
			if(MsgQBuffer[i].dataAvailable == 1)
			{
				num++;
			}
		}
		break;
	default:
		break;
	}
	return num;
}
/**
* @brief  This function is responsile for receiving the data 
*		  to message queue
* @author Sunil Kumar
* @param  RxBuf: pointer to Receive buffer
* @param  len: length of the data in  bytes
* @param  key: message queue key ID
* @return return number of bytes received or negative integer 
*		  in case of failure
* @date   11/2/2021
*/
int32_t msgQRecv(uint8_t *RxBuf, uint32_t *len, NumOfMsgQ key)
{
	uint32_t i = 0;
	int32_t retval = -1;
	if(RxBuf != NULL)
	{
		switch(key)
		{
		case MSGQ_1 :
			for(i=0; i<MAX_NUM_Q; i++)
			{
				if(RxMsgQBuffer[i].dataAvailable == 1)
				{
					memcpy(RxBuf, RxMsgQBuffer[i].MsgQBuffer, RxMsgQBuffer[i].MsgQBufLen);
					*len = RxMsgQBuffer[i].MsgQBufLen;
					memset((char *)&RxMsgQBuffer[i], 0, sizeof(RxMsgQBuffer[i]));
					retval = *len;
					break;
				}
			}
			break;
		case MSGQ_2:
			for(i=0; i<MAX_NUM_Q; i++)
			{
				if(MsgQBuffer[i].dataAvailable == 1)
				{
					memcpy(RxBuf, MsgQBuffer[i].MsgQBuffer, MsgQBuffer[i].MsgQBufLen);
					*len = MsgQBuffer[i].MsgQBufLen;
					memset((char *)&MsgQBuffer[i], 0, sizeof(MsgQBuffer[i]));
					retval = *len;
					break;
				}
			}
			break;
		default:
			break;
		}
		if(i == 5)
		{
			retval = 0;
		}
	}
	return retval;
}
/**
* @brief  This function is responsile for clearing all the messages
*		  in the message queue
* @author Sunil Kumar
* @param  key: message queue key ID
* @return none
* @date   11/2/2021
*/
void msgQflush(NumOfMsgQ key)
{
	switch(key)
	{
	case MSGQ_1:
		memset(&RxMsgQBuffer, 0, sizeof(RxMsgQBuffer[MAX_NUM_RX_PKT]));
		break;
	case MSGQ_2:
		memset(&MsgQBuffer, 0, sizeof(MsgQBuffer[MAX_NUM_RX_PKT]));
		break;
	default:
		break;
	}
}
/**
* @brief  This function prints the status and the messages
*		  in the message queue
* @author Sunil Kumar
* @param  key: message queue key ID
* @return none
* @date   11/2/2021
*/
void msgQprint(NumOfMsgQ key)
{
	uint32_t i = 0;
	switch(key)
	{
	case MSGQ_1:
		for(i=0;i<MAX_NUM_Q;i++)
		{
			printf("%d:%d:%s\n",i, RxMsgQBuffer[i].dataAvailable, RxMsgQBuffer[i].MsgQBuffer);
		}
		break;
	case MSGQ_2:
		for(i=0;i<MAX_NUM_Q;i++)
		{
			printf("%d:%d:%s\n",i, MsgQBuffer[i].dataAvailable, MsgQBuffer[i].MsgQBuffer);
		}
		break;
	default:
		break;
	}
}
