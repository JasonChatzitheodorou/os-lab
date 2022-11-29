#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	int fd = open(".hello_there", O_RDWR);
	
	int filesize = 32768;
	ftruncate(fd, filesize);
	
}

	
