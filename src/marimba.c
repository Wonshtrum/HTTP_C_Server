/**
 * \file marimba.c
 * \brief Function implementation for the Marimba engine
 * \author Démolis Eloi
 */
#include "marimba.h"

void renderFromMrm(Ressource* ressource, char* request) {
	_MRC_WARN("rendering \"%s\" with \"%s\"\n", ressource->url, ressource->urn);
	//default Marimba rendered page
	char* content = "Sorry, Marimba failed to render this page!";
	char* output = malloc(sizeof(char));
	char* tmp;
	output[0] = '\0';
	//client to parent pipe and parent to client pipe
	int c2p[2];
	int p2c[2];

	if (pipe(c2p) == 0 && pipe(p2c) == 0) {
		_MRC_DEBUG("%d <-------> %d\n", c2p[0], c2p[1]);
		_MRC_DEBUG("%d <-------> %d\n", p2c[0], p2c[1]);
		int pid = fork();
		int status;
		int exitCode;
		char line[MAX_CHUNK+1];
		int totalSize = 1;
		int size;
		switch(pid) {
			case -1:
				MRC_ERROR("Marimba couldn't create a child process\n");
				//close all ends of pipes
				close(c2p[0]);
				close(c2p[1]);
				close(p2c[0]);
				close(p2c[1]);
				break;
			case 0:
				//the child process listens on p2c and writes on c2p
				dup2(c2p[1], 1);
				close(c2p[0]);
				close(c2p[1]);
				dup2(p2c[0], 0);
				close(p2c[0]);
				close(p2c[1]);
				execlp("python3", "python3", "marimba.py", NULL);
				exit(0);
			default:
				//the parent process listens on c2p and writes in p2c
				close(c2p[1]);
				close(p2c[0]);

				//passes the method, url and urn to Marimba
				size = strlen(ressource->method);
				ressource->method[size] = '\n';
				write(p2c[1], ressource->method, size+1);
				size = strlen(ressource->url);
				ressource->url[size] = '\n';
				write(p2c[1], ressource->url, size+1);
				size = strlen(ressource->urn);
				ressource->urn[size] = '\n';
				write(p2c[1], ressource->urn, size+1);
				//passes the request header and body to Marimba
				write(p2c[1], request, strlen(request)+1);
				//passes the file content to Marimba
				write(p2c[1], ressource->content, ressource->size);
				close(p2c[1]);

				_MRC_DEBUG("DATA WRITTEN %d\n", pid);

				//wait the file to render
				waitpid(pid, &status, WCONTINUED);
				_MRC_DEBUG("END WAIT\n");
				//if Marimba failed during execution
				if (WIFEXITED(status)) {
					exitCode = WEXITSTATUS(status);
					if (exitCode != 0) {
						MRC_ERROR("Marimba exited with: %d\n", exitCode);
						break;
					}
				} else {
					MRC_ERROR("Marimba was signaled\n");
					break;
				}

				while ((size = read(c2p[0], line, MAX_CHUNK)) > 0) {
					//the pipe c2p is emptied and stored in output
					line[size] = '\0';
					totalSize += size;
					tmp = malloc(totalSize*sizeof(char));
					strcpy(tmp, output);
					strcat(tmp, line);
					free(output);
					output = tmp;
				}
				close(c2p[0]);
				_MRC_DEBUG("SIZE = %d\n", totalSize);
				//replace dummy content by the rendered output
				content = output;
				break;
		}
	} else {
		MRC_ERROR("Marimba couldn't create a pipe\n");
	}

	//the old content is freed and replace by the new one
	free(ressource->content);
	ressource->content = malloc(strlen(content)*sizeof(char));
	strcpy(ressource->content, content);
	ressource->size = strlen(content);
}
