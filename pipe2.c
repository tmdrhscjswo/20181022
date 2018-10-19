#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int pfd[2];
	char buf[30];

	if(pipe(pfd) == -1) {
		perror("pipe error");
		exit(1);
	}

	if(!fork()) {
		printf("CHILD(PID: %d): Writing to the pipe\n", getpid());

		write(pfd[1], "pipe!", 5);

		sleep(10);

		exit(0);
	}
	else {
		printf("P°iENT(PID: %d): Reading from the pipe\n", getpid());
		wait(NULL);

		read(pfd[0], buf, 5);
		printf("PARENT(PID: %d): %s\n", getpid(), buf);

	}
	return 0;
}

