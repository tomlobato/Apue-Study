
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

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
    int i = 2, fd;
//    char p[] = "/tmp/x";
    
    while (i++ < 10) {
//        printf("%d\n", i);
//        p = _itoa(i);
        fd = open(_itoa(i), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
        if (fd == -1) {
            printf("err ");
        }
//        printf("%d ", fd);
    }
    return 0;
}

