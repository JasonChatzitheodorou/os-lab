#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Writes character to given file at specified offset
// arv[1] is path, argv[2] is offset, argv[3] is character
int main(int argc, char **argv)
{
    // Read path, offset and character
    int offset = atoi(argv[2]);
   
    // Write to file
    FILE *fp = fopen(argv[1], "w+");

    // Move file pointer to offset
    fseek(fp, offset, SEEK_SET);

    // Write character
    fputs(argv[3], fp);

    fseek(fp, 4096, SEEK_SET);
}
