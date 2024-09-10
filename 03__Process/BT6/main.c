#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0)
    {
        /* Parent process */
        printf("\nIm the parent process.\n");
        printf("My PID is: %d\n", getpid());

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid failed");
            exit(1);
        }

        if (WIFEXITED(status))
        {
            printf("child exited, status = %d\n", WEXITSTATUS(status));
        }
        else
        {
            fprintf(stderr, "Child did not exit normally\n");
            exit(1);
        }
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