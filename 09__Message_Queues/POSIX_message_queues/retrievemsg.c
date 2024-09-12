#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* Defines O_* constants */
#include <sys/stat.h> /* Defines mode constants */
#include <mqueue.h>
#include <assert.h>

#define FILE_NAME   "/msgqueue"
#define MAX_LEN     100

typedef struct
{
    char name[MAX_LEN];
    int age;
    char hometown[MAX_LEN];
    char contact[MAX_LEN];
} Student;

typedef struct
{
    unsigned int student_ID;
    Student student_inf;
} Message;

int main(int argc, char const *argv[])
{
    struct mq_attr attr;
    unsigned int student_ID = 0;

    /* Open the queue for reading */
    mqd_t mqd = mq_open(FILE_NAME, O_RDONLY | O_NONBLOCK);
    if (mqd == (mqd_t) -1)
    {
        perror("mq_open failed");
        exit(1);
    }

    mq_getattr(mqd, &attr);

    char *buffer = (char *)calloc(attr.mq_msgsize, 1);

    /* Retrieve message from the queue and get its priority (student_ID) level */
    if ((mq_receive(mqd, buffer, attr.mq_msgsize, &student_ID)) == -1)
    {
        printf("Failed to receive message\n");
        perror("mq_receive");
    }
    else
    {
        Message *p_msg = (Message *)buffer;
        
        printf("Student's ID (priority): %u\n", p_msg->student_ID);
        printf("\tName: %s\n", p_msg->student_inf.name);
        printf("\tAge: %i\n", p_msg->student_inf.age);
        printf("\tHometown: %s\n", p_msg->student_inf.hometown);
        printf("\tContact: %s\n\n", p_msg->student_inf.contact);
    }

    /* Clean up the allocated memory and message queue */
    free(buffer);
    buffer = NULL;
    mq_close(mqd);
    mq_unlink(FILE_NAME);
    
    return 0;
}