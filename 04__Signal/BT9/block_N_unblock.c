#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <bits/types/sigset_t.h>
#include <unistd.h>

/* Values for the HOW argument to `sigprocmask'.  */
#define	SIG_BLOCK     0		 /* Block signals.  */
#define	SIG_UNBLOCK   1		 /* Unblock signals.  */
#define	SIG_SETMASK   2		 /* Set the set of blocked signals.  */

void SIGINT_handler(int signum)
{
    printf("\nI'm SIGINT signal.\n");
}

int main(void)
{
    sigset_t set, oldset;

    signal(SIGINT, SIGINT_handler);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    if (sigprocmask(SIG_BLOCK, &set, &oldset) == -1)
    {
        perror("sigprocmask failed");
        exit(1);
    }

    printf("SIGINT is being blocked.\n");

    /* Try Ctrl + C (i.e. sending SIGINT signal) during sleep */
    sleep(5);

    if (sigprocmask(SIG_UNBLOCK, &set, &oldset) == -1)
    {
        perror("sigprocmask failed");
        exit(1);
    }
    printf("Now SIGINT is being unblocked.\n");

    while (1);

    return 0;
}