#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void clock_tick(int signo) {
	printf("\r%ld", time(NULL));
	alarm(5);
}

int main(void) {

	setvbuf(stdout, NULL, _IONBF, BUFSIZ);

	printf("\e[2J\e[H");

	if(signal(SIGALRM, clock_tick) == SIG_ERR)
		perror("cannot catch SIGALRM");

	printf("before\n");
	clock_tick(-1);
	printf("after\n");

	for(;;)
		pause();

	return(0);
}



