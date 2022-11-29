#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	const char* filename[10] = {"bf00", "bf01", "bf02", "bf03", "bf04", "bf05", "bf06", "bf07", "bf08", "bf09"};

	int fd[10];
	for (i = 0; i < 10; i++) {
		fd[i] = open(filename[i], O_RDWR|O_CREAT, S_IRWXU);
		if (fd[i] == -1) {
			perror("File didn't open");
			exit(1);
		}
		ftruncate(fd[i], 1073741824);
		int j;
		ssize_t bytes_written;
		lseek(fd[i], 1073741824, SEEK_CUR);
		bytes_written = write(fd[i], "BEEP", 4);
		if (bytes_written != 4)	{
			perror("Couldn't write");
			close(fd[i]);
			exit(1);
		}
		close(fd[i]);
	}
	printf("DONE\n");
}


		
