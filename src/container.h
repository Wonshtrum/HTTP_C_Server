/**
 * \file container.h
 * \brief Define strcutures to help holding data
 * \author Démolis Eloi
 */

#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "socket.h"

/**
 * \enum Mime
 * \brief List of the supported mime types
 */
typedef enum {
	plain,		/*!< plain text (default)*/
	html,		/*!< html document*/
	javascript,	/*!< javascript document*/
	css,		/*!< CSS stylesheet*/
	gif,		/*!< GIF image*/
	jpeg,		/*!< JPEG image*/
	png,		/*!< PNG image*/
	webm		/*!< Webm video*/
} Mime;

/**
 * \struct Ressource
 * \brief Contains all the data relevent to a Web ressource
 */
typedef struct {
	char* method; /*!< the http method>*/
	char* url;	/*!< the url*/
	char* urn;	/*!< the additional urn*/
	int code;	/*!< the status code*/
	Mime mime;	/*!< the mime type*/
	char* content;	/*!< the content (in bytes)*/
	int size;	/*!< and the size of the content*/
} Ressource;

/**
 * \struct Buffer
 * \brief Simple buffer structure to hold a string with a specitic size (when null characters can't be trusted)
 */
typedef struct {
	char* content;	/*!< the content*/
	int size;	/*!< the size of the content*/
} Buffer;

/**
 * \struct Tokens
 * \brief Simple token container
 */
typedef struct {
	char** list;	/*!< the list of tokens*/
	int n;		/*!< the number of tokens in the list*/
} Tokens;

/**
 * \struct Request
 * \brief Contains a request and the socket which emitted this request
 */
typedef struct Request {
	char* msg;	/*!< The request content*/
	Socket clnt;	/*!< The request author*/
} Request;


#endif
