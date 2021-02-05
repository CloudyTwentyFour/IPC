/**
* @file IPC_dmSock.h
* @brief This File is header file for IPC_dmSock.c
*
* @author Sunil Kumar
*
* @date 25/1/2021
*/

#ifndef IPC_DMSOCK_H_
#define IPC_DMSOCK_H_
/*Inclusion of Headers*/
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

/*Definition of Macros*/
#define IPC_OK 0
#define ERR_SOCK_FAILURE -1
#define ERR_BIND_FAILURE -2
#define ERR_CONNECT_FAILURE -3
#define ERR_RECVFROM_FAILURE -4
#define ERR_SENDTO_FAILURE -5


/*Typedefinitions*/

typedef struct sockaddr_un SOCK_DOMAIN_t;
typedef struct sockaddr SOCKADDR_t;
typedef struct
{
	SOCK_DOMAIN_t addr;
	int32_t sockfd;
	int32_t slen;
}IPC_SockDomainCfg_t;

/*Public function declarations*/
extern int32_t IPC_DomainSockCreate(SOCK_DOMAIN_t *client, SOCK_DOMAIN_t *server);
extern int32_t IPC_DomainSock_Recv(const IPC_SockDomainCfg_t *saddr, void *databuf, size_t datalen);
extern int32_t IPC_DomainSock_Send(const IPC_SockDomainCfg_t *saddr, void *databuf, size_t datalen);
extern void IPC_DomainSock_Close(const int32_t sockfd);

#endif /* IPC_DOMAINSOCK_H_ */
