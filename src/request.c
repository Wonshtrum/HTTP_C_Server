/**
 * \file request.c
 * \brief Functions implementation for request handling
 * \author Démolis Eloi
 */
#include "request.h"

Tokens parseRequest(char* request) {
	//split the request by lines
	Tokens requestLines = split(request, '\n', 1);

	//if the request is empty, simply return
	if (requestLines.n == 0) {
		return requestLines;
	}

	char* header = requestLines.list[0]+strlen(requestLines.list[0])+1;
	//split the first line by spaces
	Tokens requestHeader = split(requestLines.list[0], ' ', 0);
	requestHeader.list[2] = header;
	//free the line token list
	free(requestLines.list);
	//return the first line (header) of the request properly split
	return requestHeader;
}

void* processRequest(void* args) {
	//recover request from the passed pointer
	Request* request = (Request*)args;
	//get the requestHeader
	Tokens requestHeader = parseRequest(request->msg);
	if (requestHeader.n == 0) {
		_MRC_WARN("Empty request\n");
	} else {
		//get the url (ignores the first /)
		char* url = requestHeader.list[1]+1;
		//get the urn (starting after the first ?)
		char* urn = url;
		while (*urn != '?' && *urn != '\0') {
			urn++;
		}
		if (*urn == '?') {
			*urn = '\0';
			urn++;
		}
		MRC_WARN("Type: %s Path: \"%s\" - \"%s\"\n", requestHeader.list[0], url, urn);

		//get the matching ressource
		Ressource ressource = readFile(requestHeader.list[0], url, urn, requestHeader.list[2]);
		//builds the complete response (header and body)
		Buffer body = response(ressource);
		//send the complete response to the client socket
		sendTo(request->clnt, body);
		free(body.content);
		free(ressource.content);
	}
	//close the connexion with the client
	_MRC_WARN("close sock: %d\n", request->clnt);
	shutdown(request->clnt, SHUT_RDWR);
	close(request->clnt);
	free(requestHeader.list);
	free(request->msg);
	free(request);
	//exit thread
	return NULL;
}
