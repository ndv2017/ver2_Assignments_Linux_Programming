#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define     FIFO_FILE   "./fifo"
#define     BUFF_SIZE   100

int main(int argc, char const *argv[])
{
    int fd;
    char buff[BUFF_SIZE];

    if (mkfifo(FIFO_FILE, 0777) == -1)
    {
        // perror("mkfifo failed");
        // exit(1);
        puts("file exits");
    }

    while (1)
    {
        /* Producer write message */
        printf("Message to the consumer: ");
        fgets(buff, BUFF_SIZE, stdin);

        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) + 1); 
        
        close(fd);

        // /* Producer read message */
        // fd = open(FIFO_FILE, O_RDONLY);

        // read(fd, buff, BUFF_SIZE);
        // printf("Consumer respone: %s", buff);

        // close(fd);
    }

    return 0;
}