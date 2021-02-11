/**
* @file msgQueue.h
* @brief This File is header file for msgQueue.c
*
* @author Sunil Kumar
*
* @date 11/2/2021
*/
#ifndef MSGQUEUE_H_
#define MSGQUEUE_H_

/*Inclusion of Headers*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*Definition of Macros*/
#define MAX_NUM_Q 5u
#define MAX_MQ_BUF_SIZE 1500u

/*Typedefinitions*/
typedef enum
{
	MSGQ_1,
	MSGQ_2
}NumOfMsgQ;

/*Message Queue Data structure*/
typedef struct
{
	uint8_t dataAvailable:1;
	uint8_t MsgQBuffer[MAX_MQ_BUF_SIZE];
	uint32_t MsgQBufLen;
}IPCP_msgQ;

/*Public function declarations*/
s32_t msgQSnd(uint8_t *TxBuf, uint32_t size, NumOfMsgQ key);
s32_t msgQRecv(uint8_t *RxBuf, uint32_t *len, NumOfMsgQ key);
uint32_t msgQCount(NumOfMsgQ key);
void msgQprint(NumOfMsgQ key);

#endif /* MSGQUEUE_H_ */
