#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	printf("IN: %d\nOUT: %d\nERR: %d\n\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);

	// open file 
	// http://www.cs.bu.edu/teaching/c/file-io/intro/

	FILE *ifp, *ofp;
	char *mode = "r";
	char outputFilename[] = "out.list";

	ifp = fopen("in.list", mode);

	if (ifp == NULL) {
	  fprintf(stderr, "Can't open input file in.list!\n");
	  exit(1);
	}
	printf("File IN: %p\n\n", ifp);
	int readlen;
	readlen = read(3, buf, BUFFSIZE);
	printf("--%d--\n", readlen);
	int c = 0;
	char pr;
	while (c < readlen){
		pr = buf[c++];
		if (pr == 10) pr = 'N';
		printf("= %c\n", pr); //*(buf+readlen-1));
	}

	ofp = fopen(outputFilename, "w");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n",
	          outputFilename);
	  exit(1);
	}
	printf("File OUT: %p\n\n", ofp);

	char username[9];  /* One extra for nul char. */
	int score;

	while (fscanf(ifp, "%s %d", username, &score) != EOF) {
	  fprintf(ofp, "%s %d\n", username, score+10);
	}

	// END open file

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
		printf("\n--%d--\n", n);
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
