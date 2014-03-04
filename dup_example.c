
// http://www.cs.odu.edu/~cs471w/code/final-src/chap3/Simulator/dup.c

/**
 * This program provides an example of the dup() and dup2() system calls.
 * For those that do not understand the dup2() system call, they should
 * read and run this program before beginning with the Process Ring simulator.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
	char file_name[] = "redirected_file.txt";
	int fd1, fd2;

	// first demonstrate dup() 
	printf("dup():\n");

	/**
	 * We are dup'ing standard output such that the two
	 * file descriptors fd1 and STDOUT_FILENO both refer
	 * to the same file (in this case, standard output.)
	 */
	fd1 = dup(STDOUT_FILENO);
	printf("fd1 = %d STDOUT_FILENO = %d\n",fd1, STDOUT_FILENO);

	// now write to stdout
	write(STDOUT_FILENO,"Hello\n",strlen("Hello\n"));

	// now write to the duped file handle
	write(fd1,"Hello\n",strlen("Hello\n"));
	
	// now demonstrate dup2()
	printf("dup2():\n Refer to file %s for output.\n",file_name);

	// first create a file we will write to
	if ( (fd2 = creat(file_name, S_IRUSR | S_IWUSR)) < 0)
		perror("Unable to create file");

	/**
	 * We are setting STDOUT_FILENO so that it now refers to fd2
	 * Subsequent writes to STDOUT_FILENO will write to the file
	 * pointed to by fd2. (Ordinary writes to standard output will
	 * no longer output to the screen but to the file pointed to
	 * by fd2.)
	 */
	dup2(fd2, STDOUT_FILENO);
	printf("fd2 = %d STDOUT_FILENO = %d\n",fd2, STDOUT_FILENO);

	write(STDOUT_FILENO,"Hello\n",strlen("Hello\n"));
	write(fd2,"Hello\n",strlen("Hello\n"));

	return 0;
}