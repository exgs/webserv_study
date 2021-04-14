#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>


int main(){
        char buf[128] = {0,};
        int fd = 0;
        int flags = fcntl(fd, F_GETFL,0);

        flags |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flags);

        read(fd, buf, sizeof(buf));
        printf("buf : %s \n", buf);
}
