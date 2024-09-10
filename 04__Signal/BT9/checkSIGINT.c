#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <bits/types/sigset_t.h>

int main(void)
{
    sigset_t set, oldset;
    unsigned char u8CheckSignal;

    if (sigprocmask(0, NULL, &oldset) == -1)
    {
        perror("sigprocmask failed");
        exit(1);
    }

    if ((u8CheckSignal = sigismember(&oldset, SIGINT)) == -1)
    {
        perror("sigismember failed");
        exit(1);
    }
    else
    {
        printf((u8CheckSignal) ? "SIGINT is blocked.\n" : "SIGINT is not blocked.\n");
    }
    
    return 0;
}