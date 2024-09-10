#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#define MSG_SIZE 100

char *msg1 = "Hello";
char *msg2 = "I just wanna say that...";
char *msg3 = "Good luck mate!";
int pipefd[2];

int main(int argc, char const *argv[])
{
    pid_t child_pid;
    char in_buff[MSG_SIZE];
    int num_read = 0;

    if (pipe(pipefd) == -1)
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();
    if (child_pid == 0)
    {
        /* Child process perform reading */
        printf("\nIm the child process\n");
        
        close(pipefd[1]);       // write end is unused

        while (1)
        {
            num_read = read(pipefd[0], in_buff, MSG_SIZE);

            if (num_read == - 1)
            {
                perror("read failed");
                exit(EXIT_FAILURE);
            }
            else if (num_read == 0)
            {
                puts("pipe end_of_pipe");
                break;
            }
            else
                printf("message: %s\n", in_buff);
        }
    }
    else if (child_pid > 0)
    {
        /* Parent process perform writing */
        printf("\nIm the parent process\n");

        if (close(pipefd[0]) == -1)       // read end is unused
        {
            perror("close pipefd[0] failed");
            exit(EXIT_FAILURE);
        }

        write(pipefd[1], msg1, MSG_SIZE);
        write(pipefd[1], msg2, MSG_SIZE);
        write(pipefd[1], msg3, MSG_SIZE);

        if (close(pipefd[1]) == -1)       // will see end-of-pipe
        {
            perror("close pipefd[1] failed");
            exit(EXIT_FAILURE);
        }

        while (1);
    }
    else
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    return 0;   
}