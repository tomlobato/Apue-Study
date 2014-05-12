
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>
//#include <fcntl.h>
//#include <unistd.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
	int			i;
	struct stat	buf;
	char		*ptr;
    
	for (i = 1; i < argc; i++) {
		printf("-----\n%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			printf("lstat error");
			continue;
		}
		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);

		printf("st_mode: %hu\n", buf.st_mode);
		printf("st_ino: %llu\n", buf.st_ino);
		printf("st_nlink: %hu\n", buf.st_nlink);
		printf("st_uid: %u\n", buf.st_uid);
		printf("st_gid: %u\n", buf.st_gid);
		printf("st_size: %llu\n", buf.st_size);
	}
	exit(0);
}
