/**
* @file IPC_dmSock.c
* @brief This File has the definition of Unix Domain socket APIs
*
* @author Sunil Kumar
*
* @date 04/2/2021
*
*/
/*Inclusion of Headers*/
#include "../inc/IPC_dmSock.h"

/*Public Functions*/

/**
* @brief This function Create a Server or Client Unix Domain Socket
*		for creating client connection, both server and client parameters
*		shall be passed
*		for creating server connection, only server parameters shall be
*		passed keeping client has NULL
* @author Sunil Kumar
* @param client: pointer to unix domain socket structure
* @param server: pointer to unix domain socket structure
* @return socket filedescriptor 
* @date 04/2/2021
*/
int32_t IPC_dmSockCreate(SOCK_DOMAIN_t *client, SOCK_DOMAIN_t *server)
{
	int32_t sockfd;
	int32_t retval = IPC_OK;
	int32_t opt = 1;
	if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		retval = ERR_SOCK_FAILURE;
	}
	else
	{
		/*If both client and server parameters are provided then,
		create client connection and connect to server with
		provided information*/
		if((client != NULL) && (server != NULL))
		{
			client->sun_family = AF_UNIX;
			server->sun_family = AF_UNIX;

			if(bind(sockfd, (SOCKADDR_t *)client, sizeof(client)) < 0)
			{
				perror("bind");
				retval = ERR_BIND_FAILURE;
			}
			else
			{
				if(connect(sockfd, (SOCKADDR_t *)server, sizeof(server)) < 0)
				{
					perror("connect");
					retval = ERR_CONNECT_FAILURE;
				}
				else
				{
					/*return the socket filedescriptor*/
					retval = sockfd;
				}
			}
		}
		else
		{
			/*Create Server connection in case only Server parameters are passed*/
			unlink(server->sun_path);
			server->sun_family = AF_UNIX;
			if(bind(sockfd, (SOCKADDR_t *)server, sizeof(server)) < 0)
			{
				perror("bind");
				retval = ERR_BIND_FAILURE;
			}
			else
			{
				/*set sock file as reusable inorder to avoid biniding issues
				return the socket filedescriptor*/
				(void)setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
				perror("setsockopt");
				retval = sockfd;
			}
		}
	}
	return retval;
}

/**
* @brief This function Receives the data and stores in to databuffer passed
* @author Sunil Kumar
* @param saddr: pointer to Domain Socket configuration structure
* @param databuf: pointer to data buffer
* @param datalen:length of the data buffer 
* @return Error code incase of failure else number of bytes received
* @date 04/2/2021
*/
int32_t IPC_DomainSock_Recv(const IPC_SockDomainCfg_t *saddr, void *databuf, size_t datalen)
{
	int32_t retval = IPC_OK;
	retval = recvfrom(saddr->sockfd, databuf, datalen, 0, (SOCKADDR_t *)&(saddr->addr), (socklen_t *)&saddr->slen);
	if(retval < 0)
	{
		perror("recvfrom");
		retval  = ERR_RECVFROM_FAILURE;
	}
	return retval;
}

/**
* @brief This function Send the data and provided in databuffer
* @author Sunil Kumar
* @param saddr: pointer to Domain Socket configuration structure
* @param databuf: pointer to data buffer
* @param datalen:length of the data to be sent
* @return Error code incase of failure else number of bytes sent
* @date 04/2/2021
*/
int32_t IPC_DomainSock_Send(const IPC_SockDomainCfg_t *saddr, void *databuf, size_t datalen)
{
	int32_t retval = IPC_OK;
	retval = sendto(saddr->sockfd, databuf, datalen, 0, (SOCKADDR_t *)&(saddr->addr), saddr->slen);
	if(retval < 0)
	{
		perror("sendto");
		retval  = ERR_SENDTO_FAILURE;
	}
	return retval;
}
/**
* @brief This function closes the sock file created
* @author Sunil Kumar
* @param sockfd: socket filedescriptor
* @return Error code incase of failure else number of bytes sent
* @date 04/2/2021
*/
void IPC_DomainSock_Close(const int32_t sockfd)
{
	close(sockfd);
}
