/**
 * \file request.h
 * \brief Functions declaration for request handling
 * \author Démolis Eloi
 */
#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "socket.h"
#include "format.h"
#include "container.h"
#include "response.h"
#include "maracas.h"

/**
 * \fn Tokens parseRequest(char* request)
 * \brief Basic request parsing
 * \param[in,out] request the request content (this string is modifies by the function)
 * \return a token container witch each word of the first line of the request header
 */
Tokens parseRequest(char* request);

/**
 * \fn void* processRequest(void* args)
 * \brief Full processing of a request on a separate thread
 * \param[in] args the pointer to the request to process
 * \return NULL
 */
void* processRequest(void* args);

#endif
