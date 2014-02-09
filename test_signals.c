#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <signal.h>
#include "sys/wait.h"

int main() 
{
	int pid;
	int status;
	int tf = 10000;

	for(int sig = 1; sig < 32; sig++) 
	{
		// printf("--- sig %d\n", sig);

		if ((pid = fork()) < 0) 
		{
			printf("fork error.\n");
			exit(1);

		} else if (pid == 0) /* child */
		{ 
			// printf("mypid %d\n", getpid());
			// usleep(2*tf);
			printf("sig %d didnt killed me\n", sig);
			exit(0);
		}
		
		// parent
		// usleep(1*tf);
		if ((kill(pid, sig) == -1)){
			perror("kill error");
			exit(1);
		}

		// usleep(3*tf);
	}
}