#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME   "test.txt"
#define COUNT_CHARS   100000

void *thread_handler(void *args)
{
    int fd;

    fd = open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        perror("open failed");
        pthread_exit(NULL);
    }

    for (int i = 0; i < COUNT_CHARS; i++)
        write(fd, "V", sizeof("V"));

    close(fd);
}

int main(int argc, char const *argv[])
{
    int ret;
    pthread_t thread_id;

    if (ret = pthread_create(&thread_id, NULL, thread_handler, NULL))
    {
        perror("Error creating thread");
        exit(1);
    }

    pthread_join(thread_id, NULL);

    return 0;
}