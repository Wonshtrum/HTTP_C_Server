/**
 * \file response.h
 * \brief Functions delcaration for response handling
 * \author Démolis Eloi
 */
#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <errno.h>
#include <time.h>
#include "socket.h"
#include "file.h"
#include "format.h"
#include "maracas.h"

/**
 * \fn time_t now()
 * \brief Get the current time
 * \return the current time
 */
time_t now();

/**
 * \fn Buffer response(Ressource res)
 * \brief Builds a complete response from a Web Ressource
 * \param[in] res the Web Ressource
 * \return a buffer with a content and a size
 */
Buffer response(Ressource res);

/**
 * \fn void sendTo(Socket sock, Buffer buffer)
 * \brief Sends a complete response to a client socket
 * \param[in] sock the client socket
 * \param[in] buffer the complete response to sent
 */
void sendTo(Socket sock, Buffer buffer);

#endif
