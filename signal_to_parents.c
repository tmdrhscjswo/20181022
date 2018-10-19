#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

/* user signal handler */
static void sig_usr(int signo) {
	if(signo == SIGUSR1)
		printf("SIGUSR1 received from its child\n");
	else if(signo == SIGUSR2)
		printf("SIGUSR2 received from its child\n");
	/*
	   else if(signo == SIGINT)
	   printf("SIGINT received from its child\n");
	 */
}

int main(void)
{
	/* i?i?i?¸i?¤ */
	if(!fork()) {
		int ppid;

		ppid = getppid();
		kill(ppid, SIGUSR1);
		kill(ppid, SIGUSR2);
		kill(ppid, SIGINT);

		exit(0);
	}

	/* e¶eª¨ i?e¡i?¸i?¤ */
	else {

		/* signal handler registration */
		if(signal(SIGUSR1, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR1\n");
		if(signal(SIGUSR2, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR2\n");
		/*
		   if(signal(SIGINT, sig_usr) == SIG_ERR)
		   perror("cannot catch SIGINT\n");
		 */

		/* i?i?i?¸i?¤i i.e.e.¼ e¸°e?¤e|.e¸° */
		wait(NULL);

	}
	return 0;
}

