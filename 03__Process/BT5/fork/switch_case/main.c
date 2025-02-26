#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void main(void) {
	pid_t pid;
	pid = fork();

	switch (pid) {
		case -1:
			perror("folk()\n");
			exit(1);
		case 0:
			sleep(1);
			printf("I'm child process, my pid: %d\n", getpid());
			printf("My parent process's pid: %d\n", getppid());
		default:
			printf("I'm parent process, my pid: %d\n", getppid());
	}

	return;
}
