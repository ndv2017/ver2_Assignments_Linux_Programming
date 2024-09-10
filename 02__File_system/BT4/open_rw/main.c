#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    const char *filename = "test.txt";
    char buf1[20] = "12345";
    char buf2[20] = "6789";

    int fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666);
    if (fd == -1)
    {
        perror("open failed.");
        close(fd);
        exit(1);
    }

    /* Write the content of buf1 to the file */
    if (write(fd, buf1, strlen(buf1)) ==  -1)
    {
        perror("write failed.");
        close(fd);
        exit(1);
    }

    /* Try to move the file pointer to the beginning of the file. */
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("lseek failed.");
        close(fd);
        exit(1);
    }

    /* Attempt to write the content of buf2 to the file. */
    if (write(fd, buf2, strlen(buf2)) ==  -1)
    {
        perror("write failed.");
        close(fd);
        exit(1);
    }

    /* 
     * However, since the file was opened in O_APPEND mode, this 
     * will not affect the location where the data is written. 
     * Data will still be appended to the end of the file.
     */
    
    close(fd);
    
    return 0;
}
