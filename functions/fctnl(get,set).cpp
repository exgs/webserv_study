#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

void printAccessMode(int flags){

        switch(flags & O_ACCMODE){
        case O_RDONLY:
                        printf("read only\n");
                        break;

        case O_WRONLY:
                        printf("write only\n");
                        break;
        case O_RDWR:
                        printf("read write\n");
                        break;
        }

        printf("append %s \n", (flags & O_APPEND) ? "O":"X");
        printf("nonblocking %s \n", (flags & O_NONBLOCK) ? "O":"X");
        printf("\n");
}

int main(){
        int fd = open("test.txt", O_RDONLY|O_CREAT, 0666);

        int flags = fcntl(fd, F_GETFL,0);
        printAccessMode(flags);

        flags |= O_APPEND;

        fcntl(fd, F_SETFL, flags);

        flags = fcntl(fd, F_GETFL, 0);
        printAccessMode(flags);

}
