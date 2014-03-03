
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, const char * argv[])
{
    char fname[1024];
    int i;

    if (chdir("/Users/tom/prog/books/apue/apue-estudy/stage")) {
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }
    
    printf("%d\n", NAME_MAX);

    for (i = 0; i < 256; i++) fname[i] = 'a' + i % 26;
    fname[i] = 0;
    
    printf("%s\n", fname);
    
    int fd = open(fname, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
    if(fd == -1){
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }

    return 0;
}

