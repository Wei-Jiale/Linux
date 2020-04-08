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
    int fd = open("./test.fifo", O_WRONLY);
    if(fd < 0 ){
        perror("open fifo error");
        return -1;
    }
    printf("open fifo success\n");
    int cur = 0;
    while(1){
        char buf[1024] = {0};
        sprintf(buf, "写端写入数据 [%d]", cur++);
        write(fd, buf, strlen(buf));
        printf("写入数据成功\n");
        sleep(1);
    }
    close(fd);

    return 0;
}
