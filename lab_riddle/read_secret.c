#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int pfd[2];
	if (pipe(pfd) < 0) exit(1);
	
	//Change pipe read to be stdin
	dup2(pfd[0], STDIN_FILENO);
	
	char buffer[5000] = {0};
	
	//Open secret_number on my own to keep file descriptor
	int fd = open("secret_number", O_RDWR|O_CREAT, 00700);
	
	if (fork() == 0) {
		char *new_argv[] = {NULL, NULL, NULL};
		char *new_env[] = {NULL, NULL, NULL};
		if (execve("./riddle", new_argv, new_env) == -1) {
			perror("Couldn't execve, better luck next time\n");
			exit(1);
		}
	}
	sleep(2);
	int count = read(fd, buffer, 5000);
	
	///Read the message and send it to ./riddle
	char *temp;
	char *address;
	temp = strtok (buffer, ":");
	temp = strtok(NULL, ":");
	if(temp == NULL ) exit(1);

	address = strtok(temp, " ");
	if(address == NULL) exit(1);
	
	write(pfd[1], address, strlen(address) + 1); 

	wait(NULL);
	close(pfd[0]);
	close(pfd[1]);
}


