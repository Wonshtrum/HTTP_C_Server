/**
 * \file marimba.h
 * \brief Function delcaration for the Marimba engine
 * \author Démolis Eloi
 */
#ifndef __MARIMBA_H__
#define __MARIMBA_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "format.h"
#include "container.h"
#include "maracas.h"

#define MAX_CHUNK 1024

/**
 * \fn renderFromMrm(Ressource* ressource)
 * \brief Takes a web ressource, passes its content to the Marimba python engine and puts back in the ressource the rendered html file
 * \param[in,out] ressource the Web Ressource to render
 * \param[in] request the original request
 */
void renderFromMrm(Ressource* ressource, char* request);

#endif
