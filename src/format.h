/**
 * \file format.h
 * \brief Functions declaration for string formating
 * \author Démolis Eloi
 */
#ifndef __FORMAT_H__
#define __FORMAT_H__

#include <string.h>
#include <time.h>
#include "container.h"
#include "maracas.h"

/**
 * \fn int countTokens(char* str, const char delim)
 * \brief Count the number of tokens delimited by a character and contained in a string
 * \param[in] str the string
 * \param[in] delim the token delimiter
 * \return the number of tokens in the str and delimited by delim
 */
int countTokens(char* str, const char delim);

/**
 * \fn Tokens split(char* str, const char delim)
 * \brief Split a string into a list of tokens delimited by a character
 * \param[in,out] str the string to split (this argument is modified by the function)
 * \param[in] delim the token delimiter
 * \param[in] maxCount the maximum number of tokens
 * \return a token container
 */
Tokens split(char* str, const char delim, int maxCount);

/**
 * \fn void formatDate(char* buffer, int bufferSize, time_t rawTime)
 * \brief Write a date at the righ format
 * \param[in,out] buffer the string to write the result in
 * \param[in] buffersize the size of the passed buffer
 * \param[in] rawTime the date to format
 */
void formatDate(char* buffer, int bufferSize, time_t rawTime);

#endif
