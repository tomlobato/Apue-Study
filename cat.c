
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
// #include <math.h>

#define BUFFSIZE 4000

void err_sys(char * str){
    printf("errno: %d; errstr: %s\n; error: %s", errno, strerror(errno), str);
    exit(1);
}

int main(void) {
	int     n;
	char    buf[BUFFSIZE];
	
	while ((n = read(0, buf, BUFFSIZE)) > 0)
		if (write(1, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");
	
	exit(0); 
}