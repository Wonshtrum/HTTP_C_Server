/**
 * \file response.c
 * \brief Functions implementation for response handling
 * \author Démolis Eloi
 */
#include "response.h"

time_t now() {
	time_t date;
	//get the current time
	time(&date);
	return date;
}

Buffer response(Ressource res) {
	//initialise a buffer and populates it
	Buffer buffer;
	buffer.content = malloc((1024+res.size)*sizeof(char));
	//response template
	char* template =
	"HTTP/1.1 %d %s\r\n"
	"Date: %s\r\n"
	"Server: Maracas/0.2 (Linux)\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: %d\r\n"
	"Content-type: %s\r\n"
	"Connection: close\r\n"
	"\r\n";

	//status message matching status code
	char* status;
	if (res.code == 200) {
		status = "OK";
	} else if (res.code == 404) {
		status = "Not Found";
	}

	//formats the date
	int dateSize = 80;
	char date[dateSize];
	formatDate(date, dateSize, now());

	//convert the mime type to its string representation
	char* mime;
	switch (res.mime) {
		case plain:
			mime = "text/plain";
			break;
		case html:
			mime = "text/html";
			break;
		case javascript:
			mime = "text/javascript";
			break;
		case css:
			mime = "text/css";
			break;
		case gif:
			mime = "image/gif";
			break;
		case jpeg:
			mime = "image/jpeg";
			break;
		case png:
			mime = "image/png";
			break;
		case webm:
			mime = "video/webm";
			break;
		default:
			//again plain text is default
			mime = "text/plain";
			break;
	}

	//construct the complete response from the template
	sprintf(buffer.content, template, res.code, status, date, res.size, mime);
	int headerSize = strlen(buffer.content);
	memcpy(buffer.content+headerSize, res.content, res.size+1);

	//the response content can contains nul characters (especially images) so the size is carefully kept appart
	buffer.size = headerSize+res.size;
	return buffer;
}

void sendTo(Socket sock, Buffer buffer) {
	//sends the full buffer to the client
	_MRC_WARN("send sock: %d\n", sock);
	int bytesSent = send(sock, buffer.content, buffer.size, 0);
	//_MRC_TRACE("PACKET: %.*s\n", buffer.size, buffer.content);
	if (bytesSent != buffer.size) {
		MRC_ERROR("Error sending response: %d != %d\n", bytesSent, buffer.size);
		MRC_ERROR("errno: %d\n", errno);
	}
}
