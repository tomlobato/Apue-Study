
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>
//#include <fcntl.h>
#include <unistd.h>
//#include <limits.h>

int main(void)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");
    
    exit(0);
}
