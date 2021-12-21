/**
 * \file main.c
 * \brief Main file of the C Web Server
 * \author Démolis Eloi
 */
#include <signal.h>
#include <pthread.h>
#include "config.h"
#include "socket.h"
#include "request.h"
#include "maracas.h"

int servPort = DEFAULT_PORT;
Socket servSock;

/**
 * \fn void endServer()
 * \brief Kill properly the server and its socket when sigint is received
 */
void endServer() {
	MRC_CRITIC("Killing server\n");
	shutdown(servSock, SHUT_RDWR);
	close(servSock);
	exit(-1);
}

/**
 * \fn int main(int argc, char** argv)
 * \brief Entry point of the program
 * \param[in] argc argument count
 * \param[in] argv argument list
 * \return 0 if there is no error, a non-zero integer else
 */
int main(int argc, char** argv) {
	//Maracas Logger
	MRC_TRACE("MARACAS ACTIVE\n");
	_MRC_TRACE("DEBUG_MOD ACTIVE\n");

	//if the program is called with a parameter
	if (argc > 1) {
		//replace the default serverPort with the specified one
		servPort = atoi(argv[1]);
	}

	//initialise the server socket
	Socket servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	MRC_ASSERT_NOT(servSock < 0,
		"Error creating a socket\n");
	int enable = 1;
	MRC_ASSERT_NOT(setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0,
		"Error setsockopt\n");

	//if sigint is received, kill the socket before killing the server
	signal(SIGINT, endServer);

	//bind the socket properties to the server socket
	MRC_INFO("port: %d, addr: %d\n", servPort, INADDR_ANY);
	SockAddrIn servSockIn = {0};
	servSockIn.sin_family = AF_INET;
	servSockIn.sin_addr.s_addr = htonl(INADDR_ANY);
	servSockIn.sin_port = htons(servPort);
	MRC_ASSERT_NOT(bind(servSock, (SockAddr*)&servSockIn, sizeof(servSockIn)) < 0,
		"Error binding socket\n");
	MRC_ASSERT_NOT(listen(servSock, MAXPENDING) < 0,
		"Error listening for connections\n");

	//create a client socket
	SockAddrIn clntSockIn = {0};
	Socket clntSock;
	//initialisation for data receiving
	unsigned int clntLen = sizeof(SockAddrIn);
	int rcvMsgSize;
	char msgBuffer[RCVBUFSIZE];
	pthread_t parallelRequestProcessing;
	//server loop
	while (1) {
		//accept a client request
		clntSock = accept(servSock, (SockAddr*)&clntSockIn, &clntLen);
		MRC_ASSERT_NOT(clntSock < 0,
			"Error accepting client %d\n", clntSock);
		MRC_INFO("connection with %s\n", inet_ntoa(clntSockIn.sin_addr));
		_MRC_WARN("sock: %d\n", clntSock);

		//read the client request
		rcvMsgSize = recv(clntSock, msgBuffer, RCVBUFSIZE, 0);
		MRC_ASSERT_NOT(rcvMsgSize < 0,
			"Error receving message\n");
		_MRC_DEBUG("%d < %d\n", rcvMsgSize, RCVBUFSIZE);
		msgBuffer[rcvMsgSize] = '\0';

		//create a request object on the heap to process it on a separate thread
		Request* request = malloc(sizeof(Request));
		request->msg = malloc((rcvMsgSize+1)*sizeof(char));
		strcpy(request->msg, msgBuffer);
		request->clnt = clntSock;
		if (pthread_create(&parallelRequestProcessing, NULL, processRequest, request) == 0) {
			if (pthread_detach(parallelRequestProcessing) == 0) {
				_MRC_INFO("separate thread created\n");
			} else {
				MRC_ERROR("Error detaching a thread\n");
			}
		} else {
			MRC_ERROR("Error creating a thread\n");
		}
	}
	return 0;
}
