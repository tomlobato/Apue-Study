#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(void)
{
	execlp("ls", "ls", "/", (char *)0);
	// printf("%ld\n", sysconf(_SC_ARG_MAX)/1024);
	exit(0);
}
