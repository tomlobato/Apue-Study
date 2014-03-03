
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

void show_offset(int fd){
    off_t os = lseek(fd, 0, SEEK_CUR);
    if (os == -1){
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    } else {
        printf("os: %lld\n", os);
    }
}

void writen(int fd, char * buf, int size){
    if (write(fd, buf, size) != size){
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }
}
int main(void)
{
    int fd;
    char buf[] = "abcdefghij";
    
    if (chdir("/Users/tom/prog/books/apue/apue-estudy/stage")) {
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }
    
    fd = open("hole.dat", O_RDWR | O_CREAT, S_IRWXU);
    
    writen(fd, buf, 10);
    show_offset(fd);
    
    writen(fd, buf, 5);
    show_offset(fd);

    off_t os = lseek(fd, pow(10, 6), SEEK_SET);
    if (os == -1){
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }
    show_offset(fd);

    writen(fd, buf, 1);
    show_offset(fd);

    close(fd);
    exit(0);
}

