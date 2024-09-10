#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (pid > 0)
    {
        /* Parent process */
        printf("\nIm the parent process.\n");
        printf("My PID is: %d\n", getpid());
    }
    else
    {
        /* Child process */
        sleep(2);

        printf("\nIm the child process.\n");
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
    }

    return 0;   
}