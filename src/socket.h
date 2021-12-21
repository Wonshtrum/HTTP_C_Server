/**
 * \file socket.h
 * \brief header file to include when interacting with sockets or web config
 * \author Démolis Eloi
 */
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//web config
#define MAXPENDING 10
#define MAX_EXT 5
#define RCVBUFSIZE 1024

//naming convention
typedef int Socket;
typedef struct sockaddr_in SockAddrIn;
typedef struct sockaddr SockAddr;

#endif
