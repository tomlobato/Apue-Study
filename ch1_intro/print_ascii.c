
#include "stdio.h"
#include "stdlib.h"

int main(void) {
	for(int i=32; i<=126; i++){
		printf("%d\t%c\n", i, i);
	}
	exit(0);
}
