#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t thread1_id, thread2_id;

typedef struct
{
    short thread_ID;
    char name[30];
    short year_of_birth;
    char tele_num[13];
    char hometown[30];
} human;

void *thread_handler(void *args)
{
    human *data = (human *)args;
    pthread_t thread_ID_check = pthread_self();
    
    if (thread_ID_check == thread1_id)
    {
        printf("Arbitrary message from thread1_id\n\n");
    }
    else if (thread_ID_check == thread2_id)
    {
        printf("Name: %s\n", data->name);
        printf("Year of birth: %d\n", data->year_of_birth);
        printf("Telephone number: %s\n", data->tele_num);
        printf("Hometown: %s\n", data->hometown);        
    }
}

int main(int argc, char const *argv[])
{
    int ret;
    human data;

    /* Initialize struct human data */
    strcpy(data.name, "Nguyen Duc Viet");
    data.year_of_birth = 2003;
    strcpy(data.tele_num, "+84123456789");
    strcpy(data.hometown, "Da Nang, Viet Nam");

    if (ret = pthread_create(&thread1_id, NULL, thread_handler, NULL))
    {
        printf("pthread_create() error number = %d\n", ret);
        exit(1);
    }

    sleep(1);

    if (ret = pthread_create(&thread2_id, NULL, thread_handler, &data))
    {
        printf("pthread_create() error number = %d\n", ret);
        exit(1);
    }

    sleep(4);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    return 0;
}