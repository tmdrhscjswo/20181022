#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int i;

int main(void)
{
	int pfd[2];
	char buf[100];

	if(pipe(pfd) == -1) {
		perror("pipe error");
		exit(1);
	}

	if(!fork()) {
		printf("CHILD(PID: %d): Writing to the pipe\n", getpid());


		for(i = 0; i < 10; i++) {
			write(pfd[1], "pipe!", 5);
		}

		exit(0);
	}
	else {
		//      read(pfd[0], buf, 5 * i);
		read(pfd[0], buf, 5 * 10);
		printf("PARENT(PID: %d): %s\n", getpid(), buf);

		wait(NULL);
	}
	return 0;
