#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void SIGCHLD_handler(int u32SignNumber)
{
    printf("\nIm in the signal handler, signum: %d\n", u32SignNumber);
    wait(NULL);
}

int main(void)
{
    pid_t pid;

    pid = fork();

    if (0 == pid)
    {
        /* Child process */
        sleep(10);

        printf("\nIm the child process\n");
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
        /* Parent process */

        signal(SIGCHLD, SIGCHLD_handler);

        printf("\nIm the parent process\n");
        printf("My PID is: %d\n", getpid());

        /* Do something */
        while (1);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }

    return 0;
}