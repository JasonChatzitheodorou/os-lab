#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp){
	int pipefd_1[2];
	int pipefd_2[2];

	if (pipe(pipefd_1) != 0) exit(1);
	pipefd_1[0] = dup2(pipefd_1[0], 33);
	pipefd_1[1] = dup2(pipefd_1[1], 34);

	if (pipe(pipefd_2) != 0) exit(1);
	pipefd_2[0] = dup2(pipefd_2[0], 53);
	pipefd_2[1] = dup2(pipefd_2[1], 54);
	
	char *new_argv[] = {NULL,NULL,NULL};
	char *new_envp[] = {NULL,NULL,NULL};
	if(execve("./riddle", new_argv, new_envp) == -1) exit(1);
}

