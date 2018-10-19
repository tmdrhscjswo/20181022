#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define MAX_SEND_SIGNUM 1000000

int main(int argc, char *argv[])
{
	int i;
	int sig;
	pid_t pid;

	puts("insert PID");
	scanf("%ud", &pid);
	getchar(); // fflush(stdin);

	puts("insert signal");
	scanf("%ud", &sig);
	getchar(); // fflush(stdin);


	printf("%s: sending signal %d to process %ld %d times\n", argv[0], sig, (long)pid, M    AX_SEND_SIGNUM);

	for(i = 0; i < MAX_SEND_SIGNUM; i++)
		if(kill(pid, sig) == -1)
			fprintf(stderr, "kill error [%s]\n", strerror(errno));

	printf("%s: exiting\n", argv[0]);

	return 0;
}

