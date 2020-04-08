#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
    // 创建命名管道
    umask(0);
    int ret = mkfifo("./test.fifo", 0664);
    if(ret < 0 && errno != EEXIST){
        perror("mkfifo error");
        return -1;
    }

    // 操作管道
    int fd = open("./test.fifo", O_RDONLY);
    if(fd < 0 ){
        perror("open fifo error");
        return -1;
    }
    printf("open fifo success\n");

    while(1){
        char buf[1024] = {0};
        int ret = read(fd, buf, 1023);
        if(ret < 0){
            perror("read error");
            return -1;
        }
        else if(ret == 0){
            perror("all write closed");
            return -1;
        }
        printf("read buf:[%s]\n", buf);
    }
    close(fd);

    return 0;
}
