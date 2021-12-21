/**
 * \file format.c
 * \brief Functions implementation for string manipulation
 * \author Démolis Eloi
 */
#include "format.h"

int countTokens(char* str, const char delim) {
	//initialisation
	char current;
	int n = 0;
	int newToken = 1;
	do {
		//for each character in str
		current = *str;
		str++;
		if (current == delim) {
			//if it is a delimiter the next non delimiter character is the start of a new token
			newToken = 1;
		} else if (current != '\0') {
			//if the last character was a delimiter and the current one is not nul, increment the number of tokens
			n += newToken;
			newToken = 0;
		}
	} while (current != '\0');
	return n;
}

Tokens split(char* str, const char delim, int maxCount) {
	//initialisation of a token container
	Tokens tokens;
	tokens.n = countTokens(str, delim);
	if (maxCount > 0 && tokens.n > maxCount) {
		tokens.n = maxCount;
	}
	tokens.list = malloc(tokens.n*sizeof(char*));
	if (tokens.n == 0) {
		return tokens;
	}

	//each token is stored in the token list
	tokens.list[0] = strtok(str, &delim);
	for (int i = 1 ; i < tokens.n ; i++) {
		tokens.list[i] = strtok(NULL, &delim);
	}

	//waring: tokens.list is a new allocation, but each member of the list a reference to the original str
	//if str is freed, tokens.list is no longer meaningfull
	return tokens;
}

void formatDate(char* buffer, int bufferSize, time_t rawTime) {
	//format the date
	struct tm* info = localtime(&rawTime);
	strftime(buffer, bufferSize, "%a, %d %b %Y %X GMT", info);
}
