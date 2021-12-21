/**
 * \file file.c
 * \brief Function implementation for file interaction
 * \author Démolis Eloi
 */
#include "file.h"

char* get404() {
	//the page template (this could be changed or even read from a specific file)
	char* template = "<b>404 Error<b>";
	//heap allocation for persistent data
	char* body = malloc((strlen(template)+1)*sizeof(char));
	strcpy(body, template);
	return body;
}

Ressource readFile(char* method, char* url, char* urn, char* request) {
	//a web ressource is initialised and populated with the url and urn
	Ressource ressource;
	ressource.method = method;
	ressource.url = url;
	ressource.urn = urn;
	ressource.content = NULL;

	//first the true path to the ressource is built
	int urlSize = strlen(url);
	if (urlSize == 0) {
		//if the url is simply / the root file is automatically sent
		url = DEFAULT_PAGE;
		urlSize = strlen(url);
	}
	char* baseDir = ROOT_DIR;
	int pathSize = strlen(baseDir)+urlSize;
	char* path = malloc((pathSize+1)*sizeof(char));
	strcpy(path, baseDir);
	strcat(path, url);

	//the file extension is copied in its own string
	char extension[MAX_EXT];
	int dotPos;
	for(dotPos = 0 ; dotPos < MAX_EXT ; dotPos++) {
		if(path[pathSize-1-dotPos] == '.') break;
	}
	extension[dotPos] = '\0';
	for (int i = 0 ; i < dotPos ; i++) {
		extension[i] = path[pathSize-dotPos+i];
	}

	MRC_TRACE("Opening \"%s\" of type \"%s\"\n", path, extension);

	//the matching file is opened in binary to account for all formats
	FILE* f = fopen(path, "rb");
	if (f == NULL) {
		//the file doesn't exit or couldn't be opened
		MRC_ERROR("Error can't open \"%s\"\n", path);
		free(path);
		//the status code is set to 404 and the default 404 error page is sent instead
		ressource.code = 404;
		ressource.mime = html;
		ressource.content = get404();
		ressource.size = strlen(ressource.content);
		return ressource;
	}
	
	_MRC_INFO("--%s--%d+%ld=%d--\n", path, urlSize, strlen(baseDir), pathSize);
	free(path);
	//I get the size of the file by positioning the cursor at the and and getting its position
	fseek(f, 0L, SEEK_END);
	int fileSize = ftell(f);
	//note: sometimes it will also stop here
	fseek(f, 0L, SEEK_SET);
	//the content of the file is stored in the ressource
	ressource.content = malloc((fileSize+1)*sizeof(char));
	fread(ressource.content, fileSize, 1, f);
	ressource.content[fileSize] = '\0';
	ressource.size = fileSize;
	//and file is finally closed
	fclose(f);

	//the mime type is infered from the extension
	if (strcmp(extension, "html") == 0) {
		ressource.mime = html;
	} else if (strcmp(extension, "mrm") == 0) {
		//mrm for Marimba is a script file to render with the Marimba python engine
		//note: the output is an html file
		ressource.mime = html;
		renderFromMrm(&ressource, request);
	} else if (strcmp(extension, "js") == 0) {
		ressource.mime = javascript;
	} else if (strcmp(extension, "css") == 0) {
		ressource.mime = css;
	} else if (strcmp(extension, "gif") == 0) {
		ressource.mime = gif;
	} else if (strcmp(extension, "jpeg") == 0) {
		ressource.mime = jpeg;
	} else if (strcmp(extension, "png") == 0) {
		ressource.mime = png;
	} else if (strcmp(extension, "webm") == 0) {
		ressource.mime = webm;
	} else {
		//if extension is not recognize, plain text is the default type
		ressource.mime = plain;
	}

	//the ressource gathering was successful
	ressource.code = 200;
	return ressource;
}
