// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <semaphore.h>
// #include <time.h>
// #include <bits/time.h>

// #define     POSIX_SEM_NAMED             "/named_app"
// #define     R_W_PERM                    0666
// #define     SEM_WAITING_TIMEOUT         10000
// #define     MSECS_IN_SEC                1000

// int main(int argc, char *argv[])
// {   
//     char c;
//     int ret = -1;
//     int current_value;
//     sem_t *sem;
//     struct timespec timeout;

//     sem = sem_open(POSIX_SEM_NAMED, O_CREAT | O_EXCL, R_W_PERM, 1);
//     if (sem == SEM_FAILED) {
//         if (errno != EEXIST) {
//             printf("Failed to open semaphore error: %s\n", strerror(errno));
//             return -1;
//         }

//         printf("%s, Reading available semaphore.\n", argv[0] );
//         sem = sem_open(POSIX_SEM_NAMED, 0);
//         if (sem == SEM_FAILED) {
//             printf("Failed to open semaphore error: %s\n", strerror(errno));
//             return -1;
//         }
//     }

//     /* Get current semaphore */
//     sem_getvalue(sem, &current_value);
//     printf("Current semaphore value =%d.\n", current_value);

//     /* Locking with timeout */
//     if (clock_gettime(0, &timeout) == -1)  // 0 = CLOCK_REALTIME
//     {
//         printf("Failed to get current time error: %s\n", strerror(errno));
//         return -1;
//     }
    
//     timeout.tv_sec += SEM_WAITING_TIMEOUT / MSECS_IN_SEC;
//     ret = sem_timedwait(sem, &timeout);
//     if (ret == -1)
//     {
//         printf("Failed to wait semaphore error: %s\n", strerror(errno));
//         return -1;
//     }

//     /* Get any character to go next */
//     printf("%s, Please type any character: ", argv[0]);
//     c = getchar();

//     ret = sem_post(sem);
//     if (ret == -1)
//     {
//         printf("Failed to release semaphore error: %s\n", strerror(errno));
//         return -1;
//     }

//     /* Enter to exit */
//     printf("\n%s, Please type any character to exit ...\n", argv[0]);
//     getchar();

//     ret = sem_close(sem);
//     if (ret == -1)
//     {
//         printf("%s, Failed to close semaphore error: %s\n", argv[0], strerror(errno));
//         return -1;
//     }

//     sem_unlink(POSIX_SEM_NAMED);

//     return ret;
// }

#include <semaphore.h>
#include <pthread.h>

#define GN_GT_0 02 /* Value must be > 0 */

static int glob = 0;
static sem_t sem;
/* Loop 'arg' times incrementing 'glob' */
static void *threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j;
    for (j = 0; j < loops; j++) {
        if (sem_wait(&sem) == -1)
            errExit("sem_wait");
        loc = glob;
        loc++;
        glob = loc;
        if (sem_post(&sem) == -1)
            errExit("sem_post");
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;
    /* Initialize a thread-shared mutex with the value 1 */
    if (sem_init(&sem, 0, 1) == -1)
    errExit("sem_init");
    /* Create two threads that increment 'glob' */
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
    errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
    errExitEN(s, "pthread_create");
    /* Wait for threads to terminate */
    s = pthread_join(t1, NULL);
    if (s != 0)
    errExitEN(s, "pthread_join");
    s = pthread_join(t2, NULL);
    if (s != 0)
    errExitEN(s, "pthread_join");
    printf("glob = %d\n", glob);
    exit(0);
}