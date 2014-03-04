
// http://www.cs.odu.edu/~cs471w/code/final-src/chap3/Simulator/dup.c

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
	char file_name[] = "redirected_file.txt";
	int fd1, fd2;

	printf("dup():\n");

	fd1 = dup(STDOUT_FILENO);
	printf("fd1 = %d STDOUT_FILENO = %d\n",fd1, STDOUT_FILENO);

	write(STDOUT_FILENO,"Hello\n",strlen("Hello\n"));

	write(fd1,"Hello\n",strlen("Hello\n"));

	printf("dup2():\n Refer to file %s for output.\n",file_name);

	if ( (fd2 = creat(file_name, S_IRUSR | S_IWUSR)) < 0)
		perror("Unable to create file");

	dup2(fd2, STDOUT_FILENO);
	printf("fd2 = %d STDOUT_FILENO = %d\n",fd2, STDOUT_FILENO);

	write(STDOUT_FILENO,"Hello\n",strlen("Hello\n"));
	write(fd2,"Hello\n",strlen("Hello\n"));

	return 0;
}
