/* signal-count.c */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static int no_sigusr1;
static int no_sigusr2;

/* user signal handler */
static void sig_usr(int signo) {
	if(signo == SIGUSR1) {
		no_sigusr1++;
		printf("%d of SIGUSR1 msgs received from its child\n", no_sigusr1);
	}
	else if(signo == SIGUSR2) {
		no_sigusr2++;
		printf("%d of SIGUSR2 msgs received from its child\n", no_sigusr2);
	}
}

int main(void)
{

	if(!fork()) {
		int ppid;
		int i;

		ppid = getppid();

		for(i = 0; i < 5; i++) {
			kill(ppid, SIGUSR1);
			kill(ppid, SIGUSR2);

			sleep(3);
		}

		printf("child exiting\n");

		exit(0);
	}
	else {

		/* signal handler registration */
		if(signal(SIGUSR1, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR1\n");
		if(signal(SIGUSR2, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR2\n");


		wait(NULL);

		printf("parent exiting\n");

	}
	return 0;
}

