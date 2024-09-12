#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* Defines O_* constants */
#include <sys/stat.h> /* Defines mode constants */
#include <mqueue.h>
#include <assert.h>
#include <string.h>

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
    Message student_inf_msg = 
    {
        1,
        {
            "Vo Hoai Trang",
            19,
            "Nha Trang",
            "0981474090"
        }
    };

    Message student_inf_msg1;
    student_inf_msg1.student_ID = 0;
    strcpy(student_inf_msg1.student_inf.name, "Nguyen Duc Viet");
    student_inf_msg1.student_inf.age = 21;
    strcpy(student_inf_msg1.student_inf.hometown, "Da Nang");
    strcpy(student_inf_msg1.student_inf.contact, "0365676274");

    /* Open the queue to send messages only */
    /* File's location: /dev/mqueue/msgqueue */
    mqd_t mqd = mq_open(FILE_NAME, O_CREAT | O_EXCL | O_RDWR,  0600, NULL);
    if (mqd == (mqd_t) -1)
    {
        perror("mq_open failed");
        exit(1);
    }

    mq_send(mqd, (const char *)&student_inf_msg, sizeof(Message), student_inf_msg.student_ID);
    mq_send(mqd, (const char *)&student_inf_msg1, sizeof(Message), student_inf_msg1.student_ID);

    struct mq_attr attr;
    mq_getattr(mqd, &attr);

    /* Buffer to receive messages */
    char *buffer = (char *)malloc(attr.mq_msgsize);
    unsigned int priority = 0;
    ssize_t bytes_received;

    // /* Print the received message */
    // if ((mq_receive(mqd, buffer, attr.mq_msgsize, &priority)) == -1)
    // {
    //     printf("Failed to receive message\n");
    //     perror("mq_receive");
    // }
    // else
    // {
    //     Message *p_msg = (Message *)buffer;

    //     printf("Received Message 1 (Priority: %u)\n", priority);
    //     printf("Student's ID (priority): %u\n", p_msg->student_ID);
    //     printf("\tName: %s\n", p_msg->student_inf.name);
    //     printf("\tAge: %i\n", p_msg->student_inf.age);
    //     printf("\tHometown: %s\n", p_msg->student_inf.hometown);
    //     printf("\tContact: %s\n\n", p_msg->student_inf.contact);
    // }

    // if ((mq_receive(mqd, buffer, attr.mq_msgsize, &priority)) == -1)
    // {
    //     printf("Failed to receive message\n");
    //     perror("mq_receive");
    // }
    // else
    // {
    //     Message *p_msg = (Message *)buffer;

    //     printf("Received Message 1 (Priority: %u)\n", priority);
    //     printf("Student's ID (priority): %u\n", p_msg->student_ID);
    //     printf("\tName: %s\n", p_msg->student_inf.name);
    //     printf("\tAge: %i\n", p_msg->student_inf.age);
    //     printf("\tHometown: %s\n", p_msg->student_inf.hometown);
    //     printf("\tContact: %s\n\n", p_msg->student_inf.contact);
    // }

    // free(buffer);
    // mq_close(mqd);
    // mq_unlink(FILE_NAME);

    return 0;
}