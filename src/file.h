/**
 * \file file.h
 * \brief Function declaration for file interaction
 * \author Démolis Eloi
 */
#ifndef __FILE_H__
#define __FILE_H__

#include "config.h"
#include "container.h"
#include "marimba.h"
#include "maracas.h"

/**
 * \fn char* get404()
 * \brief Return the body for a 404 not found ressource
 * \return an heap allocated string
 */
char* get404();

/**
 * \fn Ressource readFile(char* url, char* urn)
 * \brief Get a file on disk following url and urn
 * \param[in] method the http method used
 * \param[in] url the url passed to get it
 * \param[in] urn the additional data to use if the file uses Marimba evaluation
 * \param[in] request the original request (containing POST info) to use if the file uses Marimba evaluation
 * \return a Web Ressource containing all the data concerning the file content, its size, type, success...
 */
Ressource readFile(char* method, char* url, char* urn, char* request);

#endif
