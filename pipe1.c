#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(void) {
	int pfd[2]; 
	char buf[30] = {'\0',};

	if(pipe(pfd) == -1) {
		perror("pipe error");
		exit(1);
	}

	printf("Writing to the file descriptor #%d\n", pfd[1]);
	write(pfd[1], "pipe!!!!!!!!!!!!", 5);

	printf("Reading from the file descriptor #%d\n", pfd[0]);
	read(pfd[0], buf, 2);
	printf("%s\n", buf);

	read(pfd[0], buf, 2);
	printf("%s\n", buf);

	read(pfd[0], buf, 2);
	printf("%s\n", buf);

	return 0;
}

