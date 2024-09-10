#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

u_int8_t u8Count = 1;

/* Print random message when press Ctrl + C, i.e. raise SIGINT */
void SIGINT_handler(int signalNum)
{
    printf("\nIm in the SIGINT_handler. Signal number is: %d\n", signalNum);
    printf("\nRandom message...\nCount check: %d\n\n", u8Count++);
}

void SIGUSR1_handler(int signalNum)
{
    printf("Caught SIGUSR1 signal. Signal number is: %d\n", signalNum);
}

void SIGUSR2_handler(int signalNum)
{
    printf("Caught SIGUSR2 signal. Signal number is: %d\n", signalNum);
}

int main(void)
{
    pid_t pid;

    pid = fork();

    if (0 == pid)
    {
        /* Child process */

        sleep(2);

        printf("\nIm the child process\n");
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
        /* Parent process */

        printf("\nIm the parent process\n");
        printf("My PID is: %d\n", getpid());

        signal(SIGINT, SIGINT_handler);
        signal(SIGUSR1, SIGUSR1_handler);
        signal(SIGUSR2, SIGUSR2_handler);

        while (1)
        {
            /* Parent do something */
        }
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    return 0;
}