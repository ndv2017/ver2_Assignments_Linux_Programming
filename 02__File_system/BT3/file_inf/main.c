#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    const char *filename = "text.txt";
    const char *file_content = "Hello everyone, this is a random content!\n";
    char str_input[25];
    struct stat filestat;
    
    FILE *fd = fopen(filename, "w+");
    if (fd == NULL)
    {
        perror("fopen failed\n");
        exit(1);
    }

    puts("Writing file's content...");

    if (fprintf(fd, "%s", file_content) < 0)
    {
        perror("fprintf failed\n");
        fclose(fd);
        exit(1);
    }

    if (fgets(str_input, sizeof(str_input), stdin) == NULL)
    {
	perror("fgets failed\n");
        fclose(fd);
	exit(1);
    }
    puts("Done writing!");

    if (fprintf(fd, "%s", str_input) < 0)
    {
        perror("fprintf failed\n");
        fclose(fd);
        exit(1);
    }


    if (fclose(fd) != 0)
    {
        perror("fclose failed\n");
        exit(1);
    }

    /* Retrieve file information using stat */
    if (stat(filename, &filestat) == -1)
    {
        perror("stat failed\n");
        exit(1);
    }

    puts("\nFile's information:");
    printf("\tType of file: %s\n", S_ISREG(filestat.st_mode) ? "Regular file" : "Directory");
    printf("\tFile name: %s\n", filename);
    printf("\tLast file modification: %s", ctime(&filestat.st_mtime));
    printf("\tSize of file: %ld bytes\n", filestat.st_size);

    return 0;
}

