#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define MAX_SLEEP_TIME 30

static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;

void printSigSet(FILE *of, const char *prefix, const sigset_t *sigset)
{
	int sig, cnt;

	cnt = 0;

	for(sig = 1; sig < NSIG /*32*/; sig++)
	{
		if(sigismember(sigset, sig))
		{
			cnt++;

			fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
		}
	}

	if(cnt == 0)
		fprintf(of, "%s<empty signal set >\n", prefix);
}

void signal_handler(int sig)
{
	if(sig == SIGINT)
		gotSigint = 1;
	else
		sigCnt[sig]++;

}

int main(int argc, char *argv[])
{
	int n;
	sigset_t pendingMask, blockingMask, emptyMask;
	printf("%s: PID is %ld\n", argv[0], (long)getpid());

	for(n = 1; n < NSIG; n++)
		(void) signal(n, signal_handler);

	sigfillset(&blockingMask);
	if(sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
		fprintf(stderr, "sigprocmask\n");

	printf("%s : sleeping for %d seconds\n", argv[0], MAX_SLEEP_TIME);
	sleep(MAX_SLEEP_TIME);

	if(sigpending(&pendingMask) == -1)
		fprintf(stderr, "sigpending\n");

	printf("%s : pending signals ars : \n", argv[0]);
	printSigSet(stdout, "\t\t",  &pendingMask);

	sigemptyset(&emptyMask);
	if(sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
		fprintf(stderr, "sigprocmask\n");

	while(!gotSigint)
		continue;

	for(n = 1; n < NSIG; n++)
		if(sigCnt[n] != 0)
			printf("%s: signal %d caught %d time%s \n", argv[0], n, sigCnt[n], (sigCnt[n    ] == 1) ? "" : "s");

	exit(EXIT_SUCCESS);

	return 0;
}

