#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	if (argc != 1) {
		printf("You had one job!\n");
		exit(1);
	}
	
	// This file contains the pid of the last process
	// The next process will have this pid plus one
	int fd = open("/proc/sys/kernel/ns_last_pid", O_RDWR | O_CREAT, 0644);

	if (fd < 0) 
		exit(1);
	
	// Set pid to the previous of what i want to have
	// and write it in a string
	//int pid = atoi(argv[1]) - 1;
	char buffer[] = "32766";
	//snprintf(buffer, strlen(buffer), "%d", pid);

	// Write it to the file
	int wrote = write(fd, buffer, strlen(buffer)+1);
	printf("Wrote %d stuff", wrote);

	close(fd);

	// Time to fork 
	int child = fork();
	
	if (child == -1)
		exit(1);

	// Parent
	if (child != 0) {
		wait(NULL);
		printf("%d\n", child);
		close(fd);
		return 0;
	}
	
	// Child it will have the right pid
	if (child == 0) {
		printf("%d\n", getpid());
		char *new_argv[] = {NULL, NULL, NULL};
		char *new_env[] = {NULL, NULL, NULL};
		execve("./riddle", new_argv, new_env);
	}
}



