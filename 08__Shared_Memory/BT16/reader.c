#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SHARE_MEM_SIZE      4096
#define FILE_NAME           "viet_mmap"

int main(void)
{
    int shm_fd;
    char *data;

    /* Open shared memory object */
    shm_fd = shm_open(FILE_NAME, O_RDWR, 0);
    if (shm_fd == -1)
    {
        printf("shm_open failed, %s.\n", strerror(errno));
        exit(1);
    }

    /* Map shared memory object into memory */
    data = mmap(0, SHARE_MEM_SIZE, PROT_WRITE , MAP_PRIVATE, shm_fd, 0);
    if (data == MAP_FAILED)
    {
        perror("mmap failed");
        exit(1);
    }

    printf("%s: Message received: %s\n", __FILE__, data); 

    /* Unmap shared memory object */
    if (munmap(data, SHARE_MEM_SIZE) == -1)
    {
        perror("munmap failed");
        exit(1);
    }

    close(shm_fd);

    /* Remove shared memory object in i.e. /dev/shm/viet_mmap */
    if (shm_unlink(FILE_NAME) == -1)
    {
        perror("shm_unlink failed");
        exit(1);
    }

    return 0;
}