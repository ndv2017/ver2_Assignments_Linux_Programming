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

    /* Create shared memory object, cause after opening the size of object is 0 */
    shm_fd = shm_open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        printf("shm_open failed, %s.\n", strerror(errno));
        exit(1);
    }

    /* Set size for shared memory object 
     *
     */
    if (ftruncate(shm_fd, SHARE_MEM_SIZE) == -1) 
    {
        perror("ftruncate failed");
        exit(1);
    }

    /* Map shared memory object into memory */
    // /* Using MAP_SHARED */
    // data = mmap(0, SHARE_MEM_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0); // Using MAP_SHARED
    // if (data == MAP_FAILED)
    // {
    //     perror("mmap failed");
    //     exit(1);
    // }

    // strcpy(data, "hello Viet, Im MMAP message (using MAP_SHARED)!");
    // printf("%s: Message sent: %s\n", __FILE__, data);

    /* Using MAP_PRIVATE */
    data = mmap(0, SHARE_MEM_SIZE, PROT_WRITE, MAP_PRIVATE, shm_fd, 0);
    if (data == MAP_FAILED) 
    {
        perror("mmap failed");
        exit(1);
    }

    strcpy(data, "hello Viet, Im MMAP message (using MAP_PRIVATE)!");
    printf("%s: Message sent: %s\n", __FILE__, data);

    /* Unmap shared memory object */
    if (munmap(data, SHARE_MEM_SIZE) == -1)
    {
        perror("munmap failed");
        exit(1);
    }
    
    close(shm_fd);

    return 0; 
}