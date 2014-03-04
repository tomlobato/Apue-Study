
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

char * _strrev(char * str, int size){
    char tmp;
    int c = size / 2;
    
    size--;
    
    while (--c >= 0) {
        tmp = *(str + c);
        *(str + c) = *(str + (size - c));
        *(str + (size - c)) = tmp;
    }
    
    return str;
}

// max: 1.8446744e19 - 1 (ull)
char * _itoa(unsigned long long int i){
    char *str = (char*) malloc(21);
    int c = 0;
    
    while (i > 9) {
        c++;
        *str++ = '0' + (i - (i/10) * 10);
        i /= 10;
    }
    c++;
    *str++ = '0' + i;
    *str = 0;
    str -= c;
    
    return _strrev(str, c);
}

int main(int argc, const char * argv[])
{
    if (chdir("/Users/tom/prog/books/apue/apue-estudy/stage")) {
        printf("errno: %d; errstr: %s\n", errno, strerror(errno));
        exit (errno);
    }

//    char cwd[1024];
//    if (getcwd(cwd, sizeof(cwd)) != NULL)
//        fprintf(stdout, "cwd %s\n", cwd);
//    else
//        perror("getcwd() error");

    
    int i = 3, fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    
    while (i <= 10000) {
        fd = open(_itoa(i), O_RDWR | O_CREAT, mode);
        if (fd == -1) {
            if (errno == EMFILE){
                printf("max open files: %d\n", i-1);
            } else {
                printf("errno: %d; errstr: %s; fd: %d\n", errno, strerror(errno), i);
            }
            break;
        }
        i++;
    }
    return 0;
}





