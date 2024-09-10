#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_NAME   "StudentInf.txt"
#define MAX_LEN     100
#define NUMBER_OF_STUDENTS      2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

typedef struct 
{
    char name[MAX_LEN];
    char dob[MAX_LEN];
    char hometown[MAX_LEN];
} Student;

Student student;        // shared resource stores student's informations
int check = 1;          // check condition to continue run thread 2 & 3

/* Input student's data to shared resource */
void* thread1(void* arg)
{
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++)
    {
        pthread_mutex_lock(&mutex);

        if (i == 1)
            check = 0;

        printf("Nhap thong tin sinh vien:\n");
        printf("Ho ten: ");
        fgets(student.name, MAX_LEN, stdin);
        student.name[strcspn(student.name, "\n")] = 0;

        printf("Ngay sinh (dd/mm/yyyy): ");
        fgets(student.dob, MAX_LEN, stdin);
        student.dob[strcspn(student.dob, "\n")] = 0;

        printf("Que quan: ");
        fgets(student.hometown, MAX_LEN, stdin);
        student.hometown[strcspn(student.hometown, "\n")] = 0;

        printf("\n--- Typing information done! ---\n");

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond1);

        sleep(0.2);     // wait for thread 2 & 3 to done it's work
    }

    puts("Done thread1\n");
}

/* Write student's data in shared resource to file */
void* thread2(void* arg) 
{
    pthread_mutex_lock(&mutex);

    while (check)
    {
        pthread_cond_wait(&cond1, &mutex);

        FILE* file;

        file = fopen(FILE_NAME, "a");
        if (file == NULL)
        {
            perror("fopen failed");
            exit(1);
        }

        fprintf(file, "%s; %s; %s.\n", student.name, student.dob, student.hometown);
        
        fclose(file);
        
        printf("\n--- Write to %s done! ---\n", FILE_NAME);
        
        pthread_cond_signal(&cond2);
    }

    pthread_mutex_unlock(&mutex);

    puts("Done thread2\n");
}

/* Read data in file and output to screen */
void* thread3(void* arg) 
{
    pthread_mutex_lock(&mutex);

    while (check)
    {
        pthread_cond_wait(&cond2, &mutex);

        char line[MAX_LEN];
        FILE* file;

        file = fopen("StudentInf.txt", "r");
        if (file == NULL) 
        {
            perror("fopen failed");
            exit(1);
        }

        printf("\n--- Read %s done! ---\n\n", FILE_NAME);

        printf("\nNoi dung file StudentInf.txt:\n");
        while (fgets(line, sizeof(line), file)) 
        {
            printf("%s", line);
        }

        fclose(file);
    }

    pthread_mutex_unlock(&mutex);

    puts("Done thread3\n");
}

int main(void) 
{
    pthread_t tid[3];
    int fd;

    fd = open(FILE_NAME, O_CREAT | O_RDWR , 0666);

    for (int j = 2; j >= 0; j--)
    {
        if (j == 2)
        {
            if (pthread_create(&tid[j], NULL, thread3, NULL) != 0) 
            {
                perror("Failed to create thread 3\n");
            }
        }
        else if (j == 1)
        {
            if (pthread_create(&tid[j], NULL, thread2, NULL) != 0) 
            {
                perror("Failed to create thread 2\n");
            }
        }
        else
        {
            if (pthread_create(&tid[j], NULL, thread1, NULL) != 0) 
            {
                perror("Failed to create thread 1\n");
            }
        }
    }

    for (int j = 2; j >= 0; j--)
    {
        if (pthread_join(tid[j], NULL) != 0) 
        {
            perror("Failed to join thread");
        }
    }

    return 0;
}