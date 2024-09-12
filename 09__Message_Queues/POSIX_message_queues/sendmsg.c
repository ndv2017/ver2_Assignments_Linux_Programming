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
        0,
        {
            "Vo Hoai Trang",
            19,
            "Nha Trang",
            "0981474090"
        }
    };

    Message student_inf_msg1;
    student_inf_msg1.student_ID = 1;
    strcpy(student_inf_msg1.student_inf.name, "Nguyen Duc Viet");
    student_inf_msg1.student_inf.age = 21;
    strcpy(student_inf_msg1.student_inf.hometown, "Da Nang");
    strcpy(student_inf_msg1.student_inf.contact, "0365676274");

    /* Open the queue to send messages only */
    /* File's location: /dev/mqueue/msgqueue */
    mqd_t mqd = mq_open(FILE_NAME, O_CREAT | O_EXCL | O_WRONLY,  0600, NULL);
    if (mqd == (mqd_t) -1)
    {
        perror("mq_open failed");
        exit(1);
    }

    mq_send(mqd, (const char *)&student_inf_msg, sizeof(Message), student_inf_msg.student_ID);
    mq_send(mqd, (const char *)&student_inf_msg1, sizeof(Message), student_inf_msg1.student_ID);
    mq_close(mqd);

    return 0;
}