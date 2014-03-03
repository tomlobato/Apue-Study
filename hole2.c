
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

void errsys(char * str){
    printf("errno: %d; errstr: %s\n; error: %s", errno, strerror(errno), str);
    exit(1);
}

int main(void) {
	int fd;

	if (chdir("/Users/tom/prog/books/apue/apue-estudy/stage")) {
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }

    fd = open("file.hole", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0){
		printf("1\n");
		errsys("creat error");
	}

	printf("fd: %d\n", fd);

	if (write(fd, buf1, 10) != 10){
		printf("2\n");
		errsys("buf1 write error");
	}

	if (lseek(fd, 16384, SEEK_SET) == -1){
		printf("3\n");
		errsys("lseek error");
	}

	if (write(fd, buf2, 10) != 10){
		printf("4\n");
		errsys("buf2 write error");
	}

	exit(0); 
}