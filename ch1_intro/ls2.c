#include "stdio.h"
#include "stdlib.h"
#include <dirent.h>

/*
	DIR *dp;
	struct dirent *dirp;

	dp = opendir()

	while ((dirp = readdir(dp)) != NULL)
		dirp->d_name
*/

int
main(int argc, char *argv[])
{
	DIR				*dp;
	struct dirent	*dirp;

	if (argc != 2){
		printf("usage: ls directory_name\n");
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL){
		printf("can't open %s\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
