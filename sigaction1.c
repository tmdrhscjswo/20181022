/* sigaction1.c */

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "sigaction1.h"

void sig_int(int signo);
void sig_usr(int signo);

int main(void)
{
	int i = 0;
	// structures for sigaction
	struct sigaction intsig, usrsig;
	// let them know what we are going to do by putting info. in the structure members
	intsig.sa_handler = sig_int; // handler function for sig_int
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;
	usrsig.sa_handler = sig_usr; // handler function for sig_usr
	sigemptyset(&usrsig.sa_mask);
	usrsig.sa_flags = 0;
	// handler registration
	// interested in SIGINT, SIGUSR1 & 2
	if (sigaction(SIGINT, &intsig, 0) == -1)
	{
		perror("signal(SIGINT) error");
		return -1;
	}

	if (sigaction(SIGUSR1, &usrsig, 0) == -1)
	{
		perror("signal(SIGUSR1) error");
		return -1;
	}

	if (sigaction(SIGUSR2, &usrsig, 0) == -1)
	{
		perror("signal(SIGUSR2) error");
		return -1;
	}
}

