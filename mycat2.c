#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define	BUFFSIZE	4

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
		printf("\n%d\n", n);
		if (write(STDOUT_FILENO, buf, n) != n) {
			printf("write error");
			exit(1);
		}
	}

	if (n < 0) {
		printf("read error");
		exit(1);
	}

	exit(0);
}
