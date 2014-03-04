
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int
main(void)
{
	printf("process ID %ld, process group ID %ld\n", (long)getpid(), (long)getpgid(getpid()));
	exit(0);
}
